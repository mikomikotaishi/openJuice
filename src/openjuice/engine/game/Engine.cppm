/**
 * @file Engine.cppm
 * @module openjuice.engine.game.Engine
 * @brief Engine implementation with threaded UI and game logic
 * 
 * This file contains the implementation of the game engine which manages
 * the main game loop and UI rendering in separate threads. It handles
 * thread synchronisation, state management, and the lifecycle of the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.Engine;

import std;
import stdx;

import openjuice.engine.discord.DiscordManager;
import openjuice.engine.game.Game;
import openjuice.engine.game.ecs.Registry;
import openjuice.engine.managers.GlobalSettings;
import openjuice.ui.UserInterface;
import openjuice.ui.cli.CommandLineInterface;
import openjuice.ui.tui.TextUserInterface;

using std::concurrent::JoiningThread;
using std::concurrent::StopToken;
using std::mem::SharedPointer;
using std::mem::UniquePointer;
using std::sync::AtomicBoolean;
using std::sync::ConditionVariable;
using std::sync::Mutex;
using std::sync::ScopedLock;
using std::sync::UniqueLock;
using std::time::Duration;
using std::time::SystemClock;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::discord::DiscordManager;
using openjuice::engine::game::ecs::RegistryError;
using openjuice::engine::managers::GlobalSettings;
using openjuice::ui::cli::CommandLineInterface;
using openjuice::ui::tui::TextUserInterface;
using openjuice::ui::UserInterface;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game);

/**
 * @enum LaunchMode
 * @brief Launch modes for the game engine
 * 
 * Specifies which user interface should be used when running the game.
 */
export enum class LaunchMode: u8 {
    CLI, ///< Command Line Interface mode
    TUI  ///< Text User Interface mode
};

/**
 * @class Engine
 * @brief Main game engine class that manages game state and threading
 * 
 * The Engine class handles the core game loop, user interface, and thread
 * synchronisation. It uses separate threads for game logic and UI rendering
 * to ensure responsive gameplay even during computation-heavy operations.
 */
export class Engine {
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("Engine"); ///< The logger instance.

    ConditionVariable gameUpdate; ///< Condition variable for signaling game thread
    Mutex stateMutex; ///< Mutex for thread-safe access to game state
    JoiningThread gameThread; ///< Thread for running game logic
    JoiningThread uiThread; ///< Thread for running UI logic
    SharedPointer<Game> game; ///< The main game instance containing game state
    UniquePointer<DiscordManager> discordManager; ///< The manager for Discord integration.
    LaunchMode launchMode; ///< The selected user interface mode
    AtomicBoolean gamePaused = false; ///< Flag indicating if the game is paused
    
    /**
     * @brief Runs the actual game loop (all computational parts of the game)
     * 
     * This method executes in its own thread and handles all game state updates.
     * It uses condition variables for pause/resume functionality and minimizes
     * lock duration to ensure UI responsiveness.
     * 
     * @param token Token for cooperative cancellation
     */
    void runGameLoop(StopToken token) {
        while (!token.stop_requested()) {
            {
                UniqueLock<Mutex> lock(stateMutex);
                gameUpdate.wait(lock, [this, &token]() -> bool { 
                    return !gamePaused.load() || token.stop_requested(); 
                });
                
                if (token.stop_requested()) {
                    break;
                }
            }
            
            {
                ScopedLock<Mutex> lock(stateMutex);
                game->update(); 
            }
            
            std::concurrent::this_thread::sleep_for(Duration<f32>(GlobalSettings::getInstance().getDeltaTime()));
        }
    }
    
    /**
     * @brief Runs the UI loop (separate from game calculations)
     * 
     * This method executes in its own thread and handles all UI rendering and
     * event processing. It creates the appropriate UI based on the selected
     * launch mode and synchronises with the game thread for state access.
     * 
     * @param token Token for cooperative cancellation
     */
    void runUiLoop(StopToken token) {
        UniquePointer<UserInterface> ui;
        switch (launchMode) {
            case LaunchMode::CLI:
                ui = std::mem::make_unique<CommandLineInterface>(game, stateMutex);
                break;
            case LaunchMode::TUI:
                ui = std::mem::make_unique<TextUserInterface>(game, stateMutex);
                break;
            default:
                std::sys::unreachable();
        }
        
        ui->init();
        
        switch (launchMode) {
            case LaunchMode::TUI:
                ui->render();
                
                gameThread.request_stop();
                gameUpdate.notify_all();
                break;
            case LaunchMode::CLI:
                while (!token.stop_requested()) {
                    ui->processEvents();
                    
                    if (ui->shouldExit()) {
                        gameThread.request_stop();
                        gameUpdate.notify_all();
                        break;
                    }
                    
                    {
                        ScopedLock<Mutex> lock(stateMutex);
                        ui->render();
                    }
                    
                    std::concurrent::this_thread::sleep_for(Duration<f32>(GlobalSettings::getInstance().getDeltaTime()));
                }
                break;
            default:
                std::sys::unreachable();
        }
    }

public:
    /**
     * @brief Constructs a new Engine object
     * 
     * @param mode The launch mode determining which UI to initialise
     */
    explicit Engine(LaunchMode mode): 
        game{std::mem::make_shared<Game>()},
        discordManager{std::mem::make_unique<DiscordManager>()},
        launchMode{mode} {

        #ifndef NDEBUG
        LOGGER->debug("Creating Engine object");
        #endif
    }

    /**
     * @brief Destroy the Engine object
     * 
     * JoiningThread automatically joins in its destructor, so explicit join calls are not needed.
     */
    ~Engine() {
        #ifndef NDEBUG
        LOGGER->debug("Destroying Engine object");
        #endif

        stop();

        #ifndef NDEBUG
        LOGGER->debug("Engine shutdown complete!");
        #endif
    }

    GETTER(SharedPointer<Game>, Game, game);
    
    /**
     * @brief Initialises and starts the engine
     * 
     * Launches both game and UI threads and waits for them to complete.
     * The UI thread drives the application lifecycle; when it exits,
     * this method ensures the game thread is also terminated properly.
     *
     * @throws RuntimeException
     */
    void init() throws (RuntimeException) {
        #ifndef NDEBUG
        LOGGER->debug("Initialising Engine");
        #endif

        if (discordManager->initialise()) {
            LOGGER->info("Discord integration successfully initialised!");
            discordManager->setMenuActivity();
        } else {
            LOGGER->warn("Discord integration unsuccessful!");
        }

        if (Expected<void, RegistryError> r = game->init(); !r) {
            throw RuntimeException(std::fmt::format("Game failed to initialise: {}", r.error()));
        }
        
        gameThread = JoiningThread([this](StopToken token) -> void {
            runGameLoop(token);
        });
        uiThread = JoiningThread([this](StopToken token) -> void {
            runUiLoop(token);
        });
        
        // Wait for UI thread to complete, which drives the application lifecycle
        uiThread.join();
        
        gameThread.request_stop();
        gameUpdate.notify_all();
    }
    
    /**
     * @brief Pauses the game logic thread
     * 
     * Sets the paused flag to true, which causes the game thread to wait
     * on the condition variable until resumed.
     */
    void pause() noexcept {
        gamePaused.store(true);
    }
    
    /**
     * @brief Resumes the game logic thread if paused
     * 
     * Clears the paused flag and notifies the game thread to continue execution.
     */
    void resume() {
        gamePaused.store(false);
        gameUpdate.notify_all();
    }
    
    /**
     * @brief Signals all threads to stop and exit cleanly
     * 
     * Requests both threads to stop via their stop tokens and notifies
     * any waiting threads to check their exit conditions.
     */
    void stop() {
        #ifndef NDEBUG
        LOGGER->debug("Stopping Engine");
        #endif
        
        gameThread.request_stop();
        uiThread.request_stop();
        gameUpdate.notify_all();
    }
};

END_MODULE_NAMESPACE();
