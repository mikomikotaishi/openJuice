/**
 * @file OnlineLobbyCreationScreen.cppm
 * @module openjuice.ui.screens:OnlineLobbyCreationScreen
 * @brief Definition of the OnlineLobbyCreationScreen class.
 *
 * This is the online lobby creation screen, after the 'Create' button
 * is selected on the OnlineLobbySelectScreen.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.screens:OnlineLobbyCreationScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.localization;
import openjuice.engine.net;
import openjuice.ui.Screen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::engine::net::NetworkingService;
using openjuice::ui::Screen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::screens);

/**
 * @class OnlineLobbyCreationScreen
 * @brief Multiplayer custom game screen implementation
 * @extends Screen
 */
export class OnlineLobbyCreationScreen final: public Screen {
private:
    SharedPointer<NetworkingService> networking; ///< The injected networking service.

    [[maybe_unused]]
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
public:
    /**
     * @brief Constructor for the OnlineLobbyCreationScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     * @param networking Shared pointer to the networking service
     */
    OnlineLobbyCreationScreen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization, SharedPointer<NetworkingService> networking):
        Screen(game, host, localization), networking{networking} {
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
