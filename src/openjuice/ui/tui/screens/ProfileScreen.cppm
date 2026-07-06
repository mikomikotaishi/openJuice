/**
 * @file ProfileScreen.cppm
 * @module openjuice.ui.tui.screens:ProfileScreen
 * @brief Definition of the ProfileScreen class.
 *
 * This file contains the definition of the ProfileScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:ProfileScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;
import openjuice.ui.tui.TuiScreen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::services::ProfileManager;
using openjuice::engine::services::LocalizationService;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TuiScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class ProfileScreen
 * @brief Profile screen implementation
 *
 * @extends TuiScreen
 */
export class ProfileScreen final: public TuiScreen {
private:
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
public:
    /**
     * @brief Constructor for the ProfileScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    ProfileScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback, SharedPointer<LocalizationService> localization):
        TuiScreen(game, callback, localization) {
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
