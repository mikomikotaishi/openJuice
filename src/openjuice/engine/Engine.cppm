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

import openjuice.chat;
import openjuice.engine.board;
import openjuice.engine.game;
import openjuice.engine.localization;
import openjuice.engine.net;
import openjuice.engine.save;
import openjuice.engine.settings;
import openjuice.ui;

using stdx::debug::StackTrace;
using stdx::inject::Inject;
using stdx::inject::Named;
using stdx::inject::Singleton;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::meta::reflect::Class;
using stdx::sync::Atomic;
using stdx::sync::ConditionVariable;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::sync::UniqueLock;
using stdx::thread::Thread;
using stdx::thread::StopToken;
using stdx::util::logging::Logger;

using openjuice::chat::ChatConnectionFactory;
using openjuice::engine::board::BoardLibrary;
using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::engine::net::DiscordService;
using openjuice::engine::net::NetworkingService;
using openjuice::engine::save::ProfileManager;
using openjuice::engine::settings::SettingsService;
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
export class [[=Singleton]] Engine {
private:
    SharedPointer<Logger> logger; ///< The logger instance.
    SharedPointer<Logger> uiLogger; ///< The logger instance for the user interface.
    SharedPointer<SettingsService> settings; ///< The persisted configuration/settings service.
    SharedPointer<LocalizationService> localization; ///< The localization service.
    SharedPointer<ProfileManager> profile; ///< The profile manager.
    SharedPointer<DiscordService> discord; ///< The manager for Discord integration.
    SharedPointer<NetworkingService> networking; ///< The central online connectivity service.
    SharedPointer<BoardLibrary> boardLibrary; ///< The board library.

    ConditionVariable gameUpdate; ///< Condition variable for signaling game thread
    Mutex stateMutex; ///< Mutex for thread-safe access to game state
    Thread gameThread; ///< Thread for running game logic
    Thread uiThread; ///< Thread for running UI logic
    SharedPointer<Game> game; ///< The main game instance containing game state
    Atomic<bool> gamePaused = false; ///< Flag indicating if the game is paused
    Atomic<UserInterface*> activeUi = nullptr; ///< The running UI, observed by the game thread to surface failures. Owned by runUiLoop.
    
    /**
     * @brief Runs the actual game loop (all computational parts of the game)
     * @param token Token for cooperative cancellation
     *
     * This method executes in its own thread and handles all game state updates.
     * It uses condition variables for pause/resume functionality and minimizes
     * lock duration to ensure UI responsiveness.
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

            try {
                {
                    ScopedLock<Mutex> lock(stateMutex);
                    game->update();
                }

                discord->runCallbacks();
            } catch (const Exception& e) {
                reportGameFailure(e.what(), Ops::fmt("{}", StackTrace::current()));
                break;
            } catch (...) {
                reportGameFailure("An unknown error occurred.", Ops::fmt("{}", StackTrace::current()));
                break;
            }

            Thread::sleep_for(settings->getDeltaTime());
        }
    }

    /**
     * @brief Forward a game-thread failure to the running UI, if there is one.
     * @param message The user-facing message
     * @param trace A formatted stack trace captured at the failure site
     *
     * The UI is owned by runUiLoop and may not exist yet (or may be tearing down), so the pointer
     * is read atomically and only used when present. reportError is itself thread-safe. When there
     * is no UI, the failure is at least logged so it is not lost.
     */
    void reportGameFailure(StringView message, StringView trace) noexcept {
        logger->error("Game thread failure: {}!\nStack trace:\n{}", message, trace);

        if (UserInterface* ui = activeUi.load(); ui != nullptr) {
            ui->reportError(message, trace);
        }
    }

    /**
     * @brief Runs the UI loop (separate from game calculations)
     * @param token Token for cooperative cancellation
     *
     * This method executes in its own thread and handles all UI rendering and
     * event processing. It creates the appropriate UI based on the selected
     * launch mode and synchronizes with the game thread for state access.
     */
    void runUiLoop(StopToken token) {
        UniquePointer<UserInterface> ui = Pointers::unique<UserInterface>(
            game,
            uiLogger,
            localization,
            profile,
            networking
        );

        ui->init();
        activeUi.store(ui.get());
        ui->render();
        activeUi.store(nullptr);

        gameThread.request_stop();
        gameUpdate.notify_all();
    }

public:
    /**
     * @brief Constructs a new Engine object
     * @param logger The injected logger.
     * @param uiLogger The injected logger for the UI.
     * @param settings The injected settings service.
     * @param localization The injected localization service.
     * @param profile The injected profile manager.
     * @param discord The injected Discord service.
     * @param discord The injected board library.
     * @param game The injected game.
     */
    [[=Inject]]
    explicit Engine(
        [[=Named(*Class<Engine>().name())]] SharedPointer<Logger> logger,
        [[=Named(*Class<UserInterface>().name())]] SharedPointer<Logger> uiLogger,
        SharedPointer<SettingsService> settings,
        SharedPointer<LocalizationService> localization,
        SharedPointer<ProfileManager> profile,
        SharedPointer<DiscordService> discord,
        SharedPointer<NetworkingService> networking,
        SharedPointer<BoardLibrary> boardLibrary,
        SharedPointer<Game> game
    ):
        logger{Ops::move(logger)},
        uiLogger{Ops::move(uiLogger)},
        settings{Ops::move(settings)},
        localization{Ops::move(localization)},
        profile{Ops::move(profile)},
        discord{Ops::move(discord)},
        networking{Ops::move(networking)},
        boardLibrary{Ops::move(boardLibrary)},
        game{Ops::move(game)} {
        #ifndef NDEBUG
        this->logger->debug("Created Engine!");
        #endif
    }

    /**
     * @brief Destroy the Engine object
     */
    ~Engine() {
        #ifndef NDEBUG
        logger->debug("Destroying Engine...");
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
     * @throws RuntimeException
     *
     * Launches both game and UI threads and waits for them to complete.
     * The UI thread drives the application lifecycle; when it exits,
     * this method ensures the game thread is also terminated properly.
     */
    [[=Throws<RuntimeException>]]
    void init() {
        #ifndef NDEBUG
        logger->debug("Initializing Engine...");
        #endif

        if (discord->init()) {
            logger->info("Discord integration successfully initialized!");
            discord->setMenuActivity();
        } else {
            logger->warn("Discord integration unsuccessful!");
        }

        if (networking->init()) {
            logger->info("Networking service successfully initialized!");
        } else {
            logger->warn("Networking service initialization unsuccessful!");
        }

        game->init();
        gameThread = Thread([this](StopToken token) -> void {
            runGameLoop(token);
        });
        uiThread = Thread([this](StopToken token) -> void {
            runUiLoop(token);
        });
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
