/**
 * @file PauseScreen.cppm
 * @module openjuice.ui.tui.screens:PauseScreen
 * @brief Definition of the PauseScreen class.
 *
 * This file contains the definition of the PauseScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:PauseScreen;

import std;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.ui.tui.TUIScreen;

import ftxui;

using std::collections::Vector;
using std::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::managers::ProfileManager;
using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TUIScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class PauseScreen
 * @brief Pause screen implementation
 *
 * @extends TUIScreen
 */
export class PauseScreen final: public TUIScreen {
private:
    bool initialised = false; ///< Whether the screen has been initialised

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }

    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the PauseScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    PauseScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TUIScreen(std::util::move(game), std::util::move(callback)) {
        createComponent();
    }

    /**
     * @brief Called when screen becomes active
     */
    void onActivate() noexcept override final {

    }

    /**
     * @brief Called when screen becomes inactive
     */
    void onDeactivate() noexcept override final {

    }

    /**
     * @brief Update screen
     */
    void update() noexcept override final {

    }
};

END_MODULE_NAMESPACE();
