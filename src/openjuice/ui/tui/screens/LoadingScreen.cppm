/**
 * @file LoadingScreen.cppm
 * @brief Definition of the LoadingScreen class.
 *
 * This file contains the definition of the LoadingScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.Screens:LoadingScreen;

import std;

import openjuice.engine.game.Game;
import openjuice.engine.managers.ProfileManager;
import openjuice.engine.managers.TextManager;
import openjuice.ui.tui.TUIScreen;

import ftxui;

using std::collections::Vector;
using std::mem::SharedPointer;

namespace util = std::util;

using openjuice::engine::game::Game;
using openjuice::engine::managers::ProfileManager;
using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TUIScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class LoadingScreen
 * @brief Loading screen implementation
 *
 * @extends TUIScreen
 */
export class LoadingScreen final: public TUIScreen {
private:
    bool initialised = false; ///< Whether the screen has been initialised

    /**
     * @brief Creates the screen component
     */
    void createComponent() final {

    }

    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the LoadingScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    LoadingScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TUIScreen(util::move(game), util::move(callback)) {
        createComponent();
    }

    /**
     * @brief Called when screen becomes active
     */
    void onActivate() final {

    }

    /**
     * @brief Called when screen becomes inactive
     */
    void onDeactivate() final {

    }

    /**
     * @brief Update screen
     */
    void update() final {

    }
};

END_MODULE_NAMESPACE();
