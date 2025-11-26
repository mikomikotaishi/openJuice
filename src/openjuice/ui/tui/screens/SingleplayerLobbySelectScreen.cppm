/**
 * @file SingleplayerLobbySelectScreen.cppm
 * @brief Definition of the SingleplayerLobbySelectScreen class.
 *
 * This file contains the definition of the SingleplayerLobbySelectScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.Screens:SingleplayerLobbySelectScreen;

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
 * @class SingleplayerLobbySelectScreen
 * @brief Singleplayer lobby select screen implementation
 *
 * @extends TUIScreen
 */
export class SingleplayerLobbySelectScreen final: public TUIScreen {
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
     * @brief Constructor for the SingleplayerLobbySelectScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    SingleplayerLobbySelectScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
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
