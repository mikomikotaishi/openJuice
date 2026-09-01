/**
 * @file PauseScreen.cppm
 * @module openjuice.ui.screens:PauseScreen
 * @brief Definition of the PauseScreen class.
 *
 * This file contains the definition of the PauseScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.screens:PauseScreen;

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
 * @class PauseScreen
 * @brief Pause screen implementation
 * @extends Screen
 */
export class PauseScreen final: public Screen {
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
     * @brief Constructor for the PauseScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    PauseScreen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization):
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
