/**
 * @file GameplayScreen.cppm
 * @module openjuice.ui.tui.screens:GameplayScreen
 * @brief Definition of the GameplayScreen class.
 *
 * This file contains the definition of the GameplayScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:GameplayScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;
import openjuice.ui.tui.TuiScreen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::services::LocalizationService;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TuiScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class GameplayScreen
 * @brief Gameplay screen implementation
 * @extends TuiScreen
 */
export class GameplayScreen final: public TuiScreen {
private:
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
public:
    /**
     * @brief Constructor for the GameplayScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    GameplayScreen(SharedPointer<Game> game, ScreenHost& host, SharedPointer<LocalizationService> localization):
        TuiScreen(game, host, localization) {
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
