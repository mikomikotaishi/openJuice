/**
 * @file CreditsScreen.cppm
 * @module openjuice.ui.tui.screens:CreditsScreen
 * @brief Definition of the CreditsScreen class.
 *
 * This file contains the definition of the CreditsScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:CreditsScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.ui.tui.TuiScreen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::managers::ProfileManager;
using openjuice::engine::managers::TextManager;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TuiScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class CreditsScreen
 * @brief Credits screen implementation
 *
 * @extends TuiScreen
 */
export class CreditsScreen final: public TuiScreen {
private:
    bool initialised = false; ///< Whether the screen has been initialised

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
public:
    /**
     * @brief Constructor for the CreditsScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    CreditsScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TuiScreen(Ops::move(game), Ops::move(callback)) {
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
