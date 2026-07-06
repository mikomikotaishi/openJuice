/**
 * @file Engine.cppm
 * @module openjuice.engine:Engine
 * @brief Engine implementation with threaded UI and game logic
 * 
 * This file contains the implementation of the game engine which manages
 * the main game loop and UI rendering in separate threads. It handles
 * thread synchronization, state management, and the lifecycle of the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine:Engine;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;
import openjuice.ui;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::sync::Atomic;
using stdx::sync::ConditionVariable;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::sync::UniqueLock;
using stdx::thread::Thread;
using stdx::thread::StopToken;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;
using openjuice::engine::game::ecs::Registry;
using openjuice::engine::services::ConfigurationService;
using openjuice::engine::services::DiscordService;
using openjuice::engine::services::LocalizationService;
using openjuice::engine::services::ProfileManager;
using openjuice::ui::cli::CommandLineInterface;
using openjuice::ui::tui::TextUserInterface;
using openjuice::ui::UserInterface;

BEGIN_MODULE_NAMESPACE(openjuice::engine);

/**
 * @class Engine
 * @brief Main game engine class that manages game state and threading
 * 
 * The Engine class handles the core game loop, user interface, and thread
 * synchronization. It uses separate threads for game logic and UI rendering
 * to ensure responsive gameplay even during computation-heavy operations.
 */
export class Engine {
public:
    /**
     * @enum LaunchMode
     * @brief Launch modes for the game engine
     * 
     * Specifies which user interface should be used when running the game.
     */
    enum class LaunchMode: u8 {
        CLI, ///< Command Line Interface mode
        TUI, ///< Text User Interface mode
    };
private:
    SharedPointer<LoggerFactory> loggerFactory; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The logger instance.
    SharedPointer<ConfigurationService> config; ///< The persisted configuration/settings service.
    SharedPointer<LocalizationService> localization; ///< The localization service.
    SharedPointer<ProfileManager> profile; ///< The profile manager.

    ConditionVariable gameUpdate; ///< Condition variable for signaling game thread
    Mutex stateMutex; ///< Mutex for thread-safe access to game state
    Thread gameThread; ///< Thread for running game logic
    Thread uiThread; ///< Thread for running UI logic
    SharedPointer<Game> game; ///< The main game instance containing game state
    UniquePointer<DiscordService> discord; ///< The manager for Discord integration.
    LaunchMode launchMode; ///< The selected user interface mode
    Atomic<bool> gamePaused = false; ///< Flag indicating if the game is paused
    
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
                gameUpdate.wait(lock, [this, &token] -> bool { 
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
            
            System::Thread::sleep_for(config->getDeltaTime());
        }
    }

    [[nodiscard]]
    UniquePointer<UserInterface> uiOf(LaunchMode mode) {
        switch (mode) {
            case LaunchMode::CLI:
                return Pointers::unique<CommandLineInterface>(game, stateMutex, config);
            case LaunchMode::TUI:
                return Pointers::unique<TextUserInterface>(game, stateMutex, loggerFactory, localization, profile);
        }
        Ops::unreachable();
    }
    
    /**
     * @brief Runs the UI loop (separate from game calculations)
     * 
     * This method executes in its own thread and handles all UI rendering and
     * event processing. It creates the appropriate UI based on the selected
     * launch mode and synchronizes with the game thread for state access.
     * 
     * @param token Token for cooperative cancellation
     */
    void runUiLoop(StopToken token) {
        UniquePointer<UserInterface> ui = uiOf(launchMode);
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
                    
                    System::Thread::sleep_for(config->getDeltaTime());
                }
                break;
        }
    }

public:
    /**
     * @brief Constructs a new Engine object
     *
     * @param mode The launch mode determining which UI to initialize
     * @param loggerFactory The injected logger factory
     */
    Engine(LaunchMode mode, SharedPointer<LoggerFactory> loggerFactory):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("Engine")},
        config{Pointers::shared<ConfigurationService>(loggerFactory)},
        localization{Pointers::shared<LocalizationService>(loggerFactory, config)},
        profile{Pointers::shared<ProfileManager>(loggerFactory)},
        game{Pointers::shared<Game>(loggerFactory, config)},
        discord{Pointers::unique<DiscordService>(loggerFactory)},
        launchMode{mode} {
        #ifndef NDEBUG
        logger->debug("Creating Engine object");
        #endif
    }

    /**
     * @brief Destroy the Engine object
     * 
     * Thread automatically joins in its destructor, so explicit join calls are not needed.
     */
    ~Engine() {
        #ifndef NDEBUG
        logger->debug("Destroying Engine object");
        #endif

        stop();

        #ifndef NDEBUG
        logger->debug("Engine shutdown complete!");
        #endif
    }

    /**
     * @brief Get the Game object
     * @return A shared pointer handle to the game
     */
    [[nodiscard]]
    SharedPointer<Game> getGame() const noexcept {
        return game;
    }
    
    /**
     * @brief Initializes and starts the engine
     * 
     * Launches both game and UI threads and waits for them to complete.
     * The UI thread drives the application lifecycle; when it exits,
     * this method ensures the game thread is also terminated properly.
     *
     * @throws RuntimeException
     */
    void init() throws (RuntimeException) {
        #ifndef NDEBUG
        logger->debug("Initializing Engine");
        #endif

        if (discord->init()) {
            logger->info("Discord integration successfully initialized!");
            discord->setMenuActivity();
        } else {
            logger->warn("Discord integration unsuccessful!");
        }
        if (Expected<void, Registry::Error> r = game->init(); !r) {
            throw RuntimeException(stdx::fmt::format("Game failed to initialize: {}", r.error()));
        }
        gameThread = Thread([this](StopToken token) -> void {
            runGameLoop(token);
        });
        uiThread = Thread([this](StopToken token) -> void {
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
        logger->debug("Stopping Engine");
        #endif
        
        gameThread.request_stop();
        uiThread.request_stop();
        gameUpdate.notify_all();
    }
};

END_MODULE_NAMESPACE();
