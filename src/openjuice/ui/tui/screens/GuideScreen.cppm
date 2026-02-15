/**
 * @file GuideScreen.cppm
 * @module openjuice.ui.tui.screens:GuideScreen
 * @brief Definition of the GuideScreen class.
 *
 * This file contains the definition of the GuideScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:GuideScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.ui.tui.TUIScreen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::managers::ProfileManager;
using openjuice::engine::managers::TextManager;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TUIScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class GuideScreen
 * @brief Guide/tutorial screen implementation
 *
 * @extends TUIScreen
 */
export class GuideScreen final: public TUIScreen {
private:
    bool initialised = false; ///< Whether the screen has been initialised

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {

    }
    
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the GuideScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    GuideScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TUIScreen(stdx::util::move(game), stdx::util::move(callback)) {
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
