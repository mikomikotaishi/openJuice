/**
 * @file TitleScreen.cppm
 * @module openjuice.ui.tui.screens:TitleScreen
 * @brief Definition of the TitleScreen class.
 *
 * This file contains the definition of the TitleScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:TitleScreen;

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
 * @class TitleScreen
 * @brief Title screen implementation
 * @extends TuiScreen
 */
export class TitleScreen final: public TuiScreen {
private:
    SharedPointer<ProfileManager> profile; ///< The injected profile manager.

    Component menu; ///< The menu UI component
    Vector<String> menuOptions = {
        menuLabel("MAINMENU_NEWGAME", "New game"), // New game
        menuLabel("MAINMENU_LOADGAME", "Continue"), // Continue
        menuLabel("MAINMENU_CONFIGURATION", "Config"), // Config
        menuLabel("MAINMENU_EXIT", "Exit") // Exit game
    }; ///< The list of menu options

    i32 selectedOption = 0; ///< The current option selected
    bool exitSelected = false; ///< Whether the entire application should exit
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialized) {
            return;
        }

        menu = Menu(&menuOptions, &selectedOption);

        Component componentWithEvents = CatchEvent(menu, [this](Event event) -> bool {
            if ((event.is_mouse() && event.mouse().button == Mouse::Left) || (event == Event::Return)) {
                switch (selectedOption) {
                    case 0: // New Game
                        if (Expected<void, ProfileManager::Error> result = profile->resetProfile(); !result) {
                            showError(Ops::fmt("Could not start a new game.\n\n{}", result.error()));
                            return true;
                        }
                        switchScreen(ScreenType::MAIN_MENU);
                        return true;
                    case 1: // Continue
                        if (Expected<void, ProfileManager::Error> result = profile->loadProfile(); !result) {
                            showError(Ops::fmt("Could not load your profile.\n\n{}", result.error()));
                            return true;
                        }
                        switchScreen(ScreenType::MAIN_MENU);
                        return true;
                    case 2: // Configuration
                        switchScreen(ScreenType::CONFIG);
                        return true;
                    case 3: // Exit
                        exitSelected = true;
                        switchScreen(ScreenType::EXIT);
                        return true;
                    default:
                        Ops::unreachable();
                }
            }
            return false;
        });

        component = Renderer(componentWithEvents, [this] -> Element {
            return vbox({
                text("openJuice") | bold | center,
                separator(),
                menu->Render() | center,
                separator(),
                text("Version 0.0.1") | center,
            }) | border | flex;
        }) | bgcolor(Color::Orange1);;

        initialized = true;
    }
public:
    /**
     * @brief Constructor for the TitleScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     * @param profile Shared pointer to the profile manager
     */
    TitleScreen(SharedPointer<Game> game, ScreenHost& host, SharedPointer<LocalizationService> localization, SharedPointer<ProfileManager> profile):
        TuiScreen(game, host, localization),
        profile{profile} {
        createComponent();
    }

    /**
     * @brief Called when screen becomes active
     */
    void onActivate() noexcept override final {
        exitSelected = false;
        selectedOption = 0;
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

    /**
     * @brief Check if the user requested to exit
     * @return True if exit was selected
     */
    [[nodiscard]]
    bool shouldExit() const noexcept override final {
        return exitSelected;
    }
};

END_MODULE_NAMESPACE();
