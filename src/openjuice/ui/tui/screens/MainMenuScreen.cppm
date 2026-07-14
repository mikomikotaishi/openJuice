/**
 * @file MainMenuScreen.cppm
 * @module openjuice.ui.tui.screens:MainMenuScreen
 * @brief Definition of the MainMenuScreen class.
 *
 * This file contains the definition of the MainMenuScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.screens:MainMenuScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;
import openjuice.engine.util;
import openjuice.ui.tui.TuiScreen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace sys = stdx::sys;
namespace util = stdx::util;

using openjuice::engine::game::Game;
using openjuice::engine::services::LocalizationService;
using openjuice::engine::util::UrlOpenError;
using openjuice::ui::tui::ScreenType;
using openjuice::ui::tui::TuiScreen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui::screens);

/**
 * @class MainMenuScreen
 * @brief Main menu screen implementation
 * @extends TuiScreen
 */
export class MainMenuScreen final: public TuiScreen {
private:
    SharedPointer<Logger> logger; ///< The logger instance.

    Component menu; ///< The menu UI component
    Vector<String> menuOptions = {
        menuLabel("PLAYMENU_FREEBATTLE", "Free battle"), // Multiplayer
        menuLabel("PLAYMENU_CAMPAIGN", "Campaign"), // Campaign
        menuLabel("PLAYMENU_SHOP", "Shop"), // Shop
        menuLabel("PLAYMENU_PROFILE", "Profile"), // Profile
        menuLabel("PLAYMENU_CODEX", "OJDex"), // OJDex
        menuLabel("PLAYMENU_MANUAL", "Manual"), // Guide
        menuLabel("PLAYMENU_WIKI", "Wiki"), // Wiki
        menuLabel("MENU_BUTTON_GAME_CONFIG", "Config"), // Config
        "Credits", // Credits
        menuLabel("PLAYMENU_EXIT", "Exit") // Exit to title
    }; ///< The list of menu options

    i32 selectedOption = 0; ///< The current option selected
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Opens the Orange Juice wiki in the user's browser.
     *
     * openUrl is a free function with no logger of its own, so the failure is reported here.
     */
    void openWiki() const noexcept {
        Expected<void, UrlOpenError> result = engine::util::openUrl(LocalizationService::ORANGE_JUICE_WIKI_URL);
        if (result) {
            return;
        }

        switch (result.error()) {
            case UrlOpenError::UNSUPPORTED_PLATFORM:
                logger->error("Cannot open the wiki: opening URLs is unsupported on this platform");
                break;
            case UrlOpenError::SYSTEM_CALL_FAILED:
                logger->error("Cannot open the wiki: the browser launch command failed");
                break;
            case UrlOpenError::INVALID_URL:
                logger->error("Cannot open the wiki: invalid URL '{}'", LocalizationService::ORANGE_JUICE_WIKI_URL);
                break;
        }
    }

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialized) {
            return;
        }

        menu = Menu(&menuOptions, &selectedOption);

        Component componentWithEvents = CatchEvent(menu, [this](Event event) -> bool {
            if (event.is_mouse() && event.mouse().button == Mouse::Left && event.mouse().motion == Mouse::Pressed) {
                switch (selectedOption) {
                    case 0: // Multiplayer
                        switchScreen(ScreenType::MULTIPLAYER_LOBBY_SELECT);
                        return true;
                    case 1: // Singleplayer
                        switchScreen(ScreenType::SINGLEPLAYER_LOBBY_SELECT);
                        return true;
                    case 2: // Shop
                        switchScreen(ScreenType::SHOP);
                        return true;
                    case 3: // Profile
                        switchScreen(ScreenType::PROFILE);
                        return true;
                    case 4: // OJDex
                        switchScreen(ScreenType::OJDEX);
                        return true;
                    case 5: // Guide
                        switchScreen(ScreenType::GUIDE);
                        return true;
                    case 6: // Wiki
                        openWiki();
                        return true;
                    case 7: // Config
                        switchScreen(ScreenType::CONFIG);
                        return true;
                    case 8: // Credits
                        switchScreen(ScreenType::CREDITS);
                        return true;
                    case 9: // Exit to title
                        switchScreen(ScreenType::TITLE);
                        return true;
                    default:
                        Ops::unreachable();
                }
            } else if (event == Event::Return) {
                switch (selectedOption) {
                    case 0: // Multiplayer
                        switchScreen(ScreenType::MULTIPLAYER_LOBBY_SELECT);
                        return true;
                    case 1: // Singleplayer
                        switchScreen(ScreenType::SINGLEPLAYER_LOBBY_SELECT);
                        return true;
                    case 2: // Shop
                        switchScreen(ScreenType::SHOP);
                        return true;
                    case 3: // Profile
                        switchScreen(ScreenType::PROFILE);
                        return true;
                    case 4: // OJDex
                        switchScreen(ScreenType::OJDEX);
                        return true;
                    case 5: // Guide
                        switchScreen(ScreenType::GUIDE);
                        return true;
                    case 6: // Wiki
                        openWiki();
                        return true;
                    case 7: // Config
                        switchScreen(ScreenType::CONFIG);
                        return true;
                    case 8: // Credits
                        switchScreen(ScreenType::CREDITS);
                        return true;
                    case 9: // Exit to title
                        switchScreen(ScreenType::TITLE);
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
                hbox({
                    text(" "),
                    menu->Render() | flex,
                    text(" ")
                }),
            }) | border | flex;
        }) | bgcolor(Color::Orange1);;

        initialized = true;
    }
public:
    /**
     * @brief Constructor for the MainMenuScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     * @param loggerFactory Shared logger factory used to create this screen's logger
     */
    MainMenuScreen(SharedPointer<Game> game, ScreenHost& host, SharedPointer<LocalizationService> localization, SharedPointer<LoggerFactory> loggerFactory):
        TuiScreen(game, host, localization),
        logger{loggerFactory->of("MainMenuScreen")} {
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
