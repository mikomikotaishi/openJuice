/**
 * @file UserInterface.cppm
 * @module openjuice.ui.UserInterface
 * @brief Abstract interface for UI implementations
 */

module;

#include "Macros.hpp"

export module openjuice.ui.UserInterface;

import stdx;

import openjuice.engine.game;

using stdx::mem::SharedPointer;
using stdx::sync::Atomic;
using stdx::sync::Mutex;

using openjuice::engine::game::Game;

BEGIN_MODULE_NAMESPACE(openjuice::ui);

/**
 * @class UserInterface
 * @brief Abstract base class for all user interfaces
 */
export class [[nodiscard]] UserInterface {
protected:
    SharedPointer<Game> game;
    Mutex& stateMutex;
    Atomic<bool> exitRequested = false;
public:
    /**
     * @brief Construct a new User Interface object
     *
     * @param game Shared pointer to the game instance
     * @param mutex Reference to mutex for thread-safe access
     */
    UserInterface(SharedPointer<Game> game, Mutex& mutex):
        game{Ops::move(game)}, stateMutex{mutex} {}

    virtual ~UserInterface() = default;

    virtual void init() = 0;
    virtual void processEvents() = 0;
    virtual void render() = 0;

    [[nodiscard]]
    bool shouldExit() const noexcept {
        return exitRequested.load();
    }

    void requestExit() noexcept {
        exitRequested.store(true);
    }
};

END_MODULE_NAMESPACE();
