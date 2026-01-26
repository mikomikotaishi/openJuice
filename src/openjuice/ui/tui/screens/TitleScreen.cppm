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

import std;
import stdx;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.ui.tui.TUIScreen;

import ftxui;

using std::collections::Vector;
using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;
using openjuice::engine::managers::ProfileManager;
using openjuice::engine::managers::TextManager;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TUIScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class TitleScreen
 * @brief Title screen implementation
 *
 * @extends TUIScreen
 */
export class TitleScreen final: public TUIScreen {
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("TitleScreen"); ///< The logger instance.

    Component menu; ///< The menu UI component
    Vector<String> menuOptions = {
        getTextManager().getMenuScreenText("MAINMENU_NEWGAME")
            .value_or("New game"), // New game
        getTextManager().getMenuScreenText("MAINMENU_LOADGAME")
            .value_or("Continue"), // Continue
        getTextManager().getMenuScreenText("MAINMENU_CONFIGURATION")
            .value_or("Config"), // Config
        getTextManager().getMenuScreenText("MAINMENU_EXIT")
            .value_or("Exit") // Exit game
    }; ///< The list of menu options

    i32 selectedOption = 0; ///< The current option selected
    bool exitSelected = false; ///< Whether the entire application should exit
    bool initialised = false; ///< Whether the screen has been initialised

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialised) {
            return;
        }

        menu = Menu(&menuOptions, &selectedOption);

        Component componentWithEvents = CatchEvent(menu, [this](Event event) -> bool {
            if ((event.is_mouse() && event.mouse().button == Mouse::Left) || (event == Event::Return)) {
                switch (selectedOption) {
                    case 0: // New Game
                        if (Expected<void, ProfileManager::Error> result = ProfileManager::getInstance().resetProfile(); !result) {
                            LOGGER->error("Failed to reset profile for new game: {}", result.error());
                        }
                        screenSwitchCallback(ScreenType::MAIN_MENU);
                        return true;
                    case 1: // Continue
                        if (Expected<void, ProfileManager::Error> result = ProfileManager::getInstance().loadProfile(); !result) {
                            LOGGER->error("Failed to load profile for continue: {}", result.error());
                        }
                        screenSwitchCallback(ScreenType::MAIN_MENU);
                        return true;
                    case 2: // Configuration
                        screenSwitchCallback(ScreenType::CONFIG);
                        return true;
                    case 3: // Exit
                        exitSelected = true;
                        screenSwitchCallback(ScreenType::EXIT);
                        return true;
                    default:
                        std::sys::unreachable();
                }
            }
            return false;
        });

        component = Renderer(componentWithEvents, [this]() -> Element {
            return vbox({
                text("openJuice") | bold | center,
                separator(),
                menu->Render() | center,
                separator(),
                text("Version 0.0.1") | center,
            }) | border | flex;
        }) | bgcolor(Color::Orange1);;

        initialised = true;
    }

    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the TitleScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    TitleScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TUIScreen(std::util::move(game), std::util::move(callback)) {
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
     *
     * @return True if exit was selected
     */
    [[nodiscard]]
    bool shouldExit() const noexcept override final {
        return exitSelected;
    }
};

END_MODULE_NAMESPACE();
