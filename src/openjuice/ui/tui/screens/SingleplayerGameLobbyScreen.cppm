/**
 * @file SingleplayerGameLobbyScreen.cppm
 * @module openjuice.ui.tui.screens:SingleplayerGameLobbyScreen
 * @brief Definition of the SingleplayerGameLobbyScreen class.
 *
 * This file contains the definition of the SingleplayerGameLobbyScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:SingleplayerGameLobbyScreen;

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
 * @class SingleplayerGameLobbyScreen
 * @brief Singleplayer game lobby screen implementation
 * @extends TuiScreen
 */
export class SingleplayerGameLobbyScreen final: public TuiScreen {
private:
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
public:
    /**
     * @brief Constructor for the SingleplayerGameLobbyScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    SingleplayerGameLobbyScreen(SharedPointer<Game> game, ScreenHost& host, SharedPointer<LocalizationService> localization):
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
