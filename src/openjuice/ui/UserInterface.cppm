/**
 * @file UserInterface.cppm
 * @module openjuice.ui.UserInterface
 * @brief Abstract interface for UI implementations
 */

module;

#include "Macros.hpp"

export module openjuice.ui.UserInterface;

import std;

import openjuice.engine.game.Game;

using std::mem::SharedPointer;
using std::sync::AtomicBoolean;
using std::sync::Mutex;

namespace util = std::util;

using openjuice::engine::game::Game;

BEGIN_MODULE_NAMESPACE(openjuice::ui);

/**
 * @class UserInterface
 * @brief Abstract base class for all user interfaces
 */
export class UserInterface {
protected:
    SharedPointer<Game> game;
    Mutex& stateMutex;
    AtomicBoolean exitRequested = false;
public:
    /**
     * @brief Construct a new User Interface object
     *
     * @param game Shared pointer to the game instance
     * @param mutex Reference to mutex for thread-safe access
     */
    UserInterface(SharedPointer<Game> game, Mutex& mutex):
        game{util::move(game)}, stateMutex{mutex} {}

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
