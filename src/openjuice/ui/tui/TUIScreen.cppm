/**
 * @file TUIScreen.cppm
 * @module openjuice.ui.tui.TUIScreen
 * @brief Base class for all TUI screens
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TUIScreen;

export import :ScreenType;

import std;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.engine.util;

import ftxui;

using std::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::managers::TextManager;
using openjuice::engine::util::IFinalOnly;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TUIScreen
 * @brief Abstract base class for all TUI screens
 *
 * @implements IFinalOnly
 */
export class TUIScreen: public IFinalOnly {
protected:
    SharedPointer<Game> game; ///< A shared pointer to the game.
    Component component; ///< An abstract component
    Function<void(ScreenType)> screenSwitchCallback; ///< An callback for screen switching

    /**
     * @brief Get the TextManager instance safely.
     * 
     * @return Reference to the TextManager singleton.
     */
    [[nodiscard]]
    static const TextManager& getTextManager() noexcept {
        return TextManager::getInstance();
    }

    /**
     * @brief Creates the screen component
     */
    virtual void createComponent() noexcept = 0;

    /**
     * @brief Constructor for the TUIScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    TUIScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        game{game}, screenSwitchCallback{callback} {}

    virtual ~TUIScreen() = default;
public:
    /**
     * @brief Get the FTXUI component for this screen
     *
     * @return The component
     */
    virtual Component getComponent() const noexcept {
        return component;
    }

    /**
     * @brief Called when the screen becomes active
     */
    virtual void onActivate() noexcept = 0;

    /**
     * @brief Called when the screen becomes inactive
     */
    virtual void onDeactivate() noexcept = 0;

    /**
     * @brief Update screen logic
     */
    virtual void update() noexcept = 0;

    /**
     * @brief Check if the screen requested exit
     *
     * @return True if exit was requested, else false
     */
    [[nodiscard]]
    virtual bool shouldExit() const noexcept {
        return false;
    }
};

END_MODULE_NAMESPACE();
