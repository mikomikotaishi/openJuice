/**
 * @file MainMenuScreen.cppm
 * @brief Definition of the MainMenuScreen class.
 *
 * This file contains the definition of the MainMenuScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.Screens:MainMenuScreen;

import std;

import openjuice.engine.game.Game;
import openjuice.engine.managers.ProfileManager;
import openjuice.engine.managers.TextManager;
import openjuice.engine.util.Misc;
import openjuice.ui.tui.TUIScreen;

import ftxui;

using std::collections::Vector;
using std::mem::SharedPointer;

namespace sys = std::sys;
namespace util = std::util;

using openjuice::engine::game::Game;
using openjuice::engine::managers::ProfileManager;
using openjuice::engine::managers::TextManager;
using openjuice::engine::util::misc::UrlOpenError;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TUIScreen;

namespace misc = openjuice::engine::util::misc;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class MainMenuScreen
 * @brief Main menu screen implementation
 *
 * @extends TUIScreen
 */
export class MainMenuScreen final: public TUIScreen {
private:
    bool initialised = false; ///< Whether the screen has been initialised
    i32 selectedOption = 0; ///< The current option selected
    Vector<String> menuOptions = {
        getTextManager().getMenuScreenText("PLAYMENU_FREEBATTLE")
            .value_or("Free battle"), // Multiplayer
        getTextManager().getMenuScreenText("PLAYMENU_CAMPAIGN")
            .value_or("Campaign"), // Campaign
        getTextManager().getMenuScreenText("PLAYMENU_SHOP")
            .value_or("Shop"), // Shop
        getTextManager().getMenuScreenText("PLAYMENU_PROFILE")
            .value_or("Profile"), // Profile
        getTextManager().getMenuScreenText("PLAYMENU_CODEX")
            .value_or("OJDex"), // OJDex
        getTextManager().getMenuScreenText("PLAYMENU_MANUAL")
            .value_or("Manual"), // Guide
        getTextManager().getMenuScreenText("PLAYMENU_WIKI")
            .value_or("Wiki"), // Wiki
        getTextManager().getMenuScreenText("MENU_BUTTON_GAME_CONFIG")
            .value_or("Config"), // Config
        "Credits", // Credits
        getTextManager().getMenuScreenText("PLAYMENU_EXIT")
            .value_or("Exit") // Exit to title
    }; ///< The list of menu options

    Component menu; ///< The menu UI component

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialised) {
            return;
        }

        menu = Menu(&menuOptions, &selectedOption);

        Component componentWithEvents = CatchEvent(menu, [this](Event event) -> bool {
            if (event.is_mouse() && event.mouse().button == Mouse::Left && event.mouse().motion == Mouse::Pressed) {
                switch (selectedOption) {
                    case 0: // Multiplayer
                        screenSwitchCallback(ScreenType::MULTIPLAYER_LOBBY_SELECT);
                        return true;
                    case 1: // Singleplayer
                        screenSwitchCallback(ScreenType::SINGLEPLAYER_LOBBY_SELECT);
                        return true;
                    case 2: // Shop
                        screenSwitchCallback(ScreenType::SHOP);
                        return true;
                    case 3: // Profile
                        screenSwitchCallback(ScreenType::PROFILE);
                        return true;
                    case 4: // OJDex
                        screenSwitchCallback(ScreenType::OJDEX);
                        return true;
                    case 5: // Guide
                        screenSwitchCallback(ScreenType::GUIDE);
                        return true;
                    case 6: // Wiki
                        if (Expected<void, UrlOpenError> result = misc::openUrl(TextManager::ORANGE_JUICE_WIKI_URL); !result) {
                            switch (result.error()) {
                                case UrlOpenError::UNSUPPORTED_PLATFORM:
                                    break;
                                case UrlOpenError::SYSTEM_CALL_FAILED:
                                    break;
                                case UrlOpenError::INVALID_URL:
                                    break;
                                default:
                                    sys::unreachable();
                            }
                        }
                        return true;
                    case 7: // Config
                        screenSwitchCallback(ScreenType::CONFIG);
                        return true;
                    case 8: // Credits
                        screenSwitchCallback(ScreenType::CREDITS);
                        return true;
                    case 9: // Exit to title
                        screenSwitchCallback(ScreenType::TITLE);
                        return true;
                    default:
                        sys::unreachable();
                }
            } else if (event == Event::Return) {
                switch (selectedOption) {
                    case 0: // Multiplayer
                        screenSwitchCallback(ScreenType::MULTIPLAYER_LOBBY_SELECT);
                        return true;
                    case 1: // Singleplayer
                        screenSwitchCallback(ScreenType::SINGLEPLAYER_LOBBY_SELECT);
                        return true;
                    case 2: // Shop
                        screenSwitchCallback(ScreenType::SHOP);
                        return true;
                    case 3: // Profile
                        screenSwitchCallback(ScreenType::PROFILE);
                        return true;
                    case 4: // OJDex
                        screenSwitchCallback(ScreenType::OJDEX);
                        return true;
                    case 5: // Guide
                        screenSwitchCallback(ScreenType::GUIDE);
                        return true;
                    case 6: // Wiki
                        if (Expected<void, UrlOpenError> result = misc::openUrl(TextManager::ORANGE_JUICE_WIKI_URL); !result) {
                            switch (result.error()) {
                                case UrlOpenError::UNSUPPORTED_PLATFORM:
                                    break;
                                case UrlOpenError::SYSTEM_CALL_FAILED:
                                    break;
                                case UrlOpenError::INVALID_URL:
                                    break;
                                default:
                                    sys::unreachable();
                            }
                        }
                        return true;
                    case 7: // Config
                        screenSwitchCallback(ScreenType::CONFIG);
                        return true;
                    case 8: // Credits
                        screenSwitchCallback(ScreenType::CREDITS);
                        return true;
                    case 9: // Exit to title
                        screenSwitchCallback(ScreenType::TITLE);
                        return true;
                    default:
                        sys::unreachable();
                }
            }
            return false;
        });

        component = Renderer(componentWithEvents, [this]() -> Element {
            return vbox({
                text("openJuice") | bold | center,
                separator(),
                hbox({
                    text(" "),
                    menu->Render() | flex,
                    text(" ")
                }),
            }) | border | flex;
        }) | bgcolor(Color::Orange1);;

        initialised = true;
    }

    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the MainMenuScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    MainMenuScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TUIScreen(util::move(game), util::move(callback)) {
        createComponent();
    }

    /**
     * @brief Called when screen becomes active
     */
    void onActivate() noexcept override final {
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
};

END_MODULE_NAMESPACE();
