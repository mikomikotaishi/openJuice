/**
 * @file MultiplayerLobbySelectScreen.cppm
 * @module openjuice.ui.screens:MultiplayerLobbySelectScreen
 * @brief Definition of the MultiplayerLobbySelectScreen class.
 *
 * This file contains the definition of the MultiplayerLobbySelectScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.screens:MultiplayerLobbySelectScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.localization;
import openjuice.ui.Screen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::ui::Screen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::screens);

/**
 * @class MultiplayerLobbySelectScreen
 * @brief Multiplayer lobby selection screen implementation
 * @extends Screen
 */
export class MultiplayerLobbySelectScreen final: public Screen {
private:
    [[maybe_unused]]
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
public:
    /**
     * @brief Constructor for the MultiplayerLobbySelectScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    MultiplayerLobbySelectScreen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization):
        Screen(game, host, localization) {
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
