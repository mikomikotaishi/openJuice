/**
 * @file OnlineLobbySelectScreen.cppm
 * @module openjuice.ui.screens:OnlineLobbySelectScreen
 * @brief Definition of the OnlineLobbySelectScreen class.
 *
 * This is the lobby selection screen for multiplayer, with the
 * 'Normal', 'Co-op', and 'Bounty Hunt' options.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.screens:OnlineLobbySelectScreen;

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
 * @class OnlineLobbySelectScreen
 * @brief Multiplayer lobby selection screen implementation
 * @extends Screen
 */
export class OnlineLobbySelectScreen final: public Screen {
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
     * @brief Constructor for the OnlineLobbySelectScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     * @param networking Shared pointer to the networking service
     */
    OnlineLobbySelectScreen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization, SharedPointer<NetworkingService> networking):
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
