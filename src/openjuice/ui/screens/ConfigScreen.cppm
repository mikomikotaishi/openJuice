/**
 * @file ConfigScreen.cppm
 * @module openjuice.ui.screens:ConfigScreen
 * @brief Definition of the ConfigScreen class.
 *
 * This file contains the definition of the ConfigScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.screens:ConfigScreen;

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
 * @class ConfigScreen
 * @brief Config/settings screen implementation
 * @extends Screen
 */
export class ConfigScreen final: public Screen {
private:
    Component tabContainer; ///< Container for tab content
    Component tabToggle; ///< Tab toggle component
    Component okButton; ///< Save button component
    Component backButton; ///< Back button component
    Vector<String> tabNames = {
        getLocalizationService()
            .getConfigText("CONFIG_LABEL_SYSTEM")
            .value_or("System"),
        getLocalizationService()
            .getConfigText("CONFIG_LABEL_SCREEN")
            .value_or("Screen"),
        getLocalizationService()
            .getConfigText("CONFIG_LABEL_SOUND")
            .value_or("Sound"),
        getLocalizationService()
            .getConfigText("CONFIG_LABEL_VOICE")
            .value_or("Voice")
    }; ///< The list of tab names

    i32 selectedTab = 0; ///< The currently selected tab
    bool initialized = false; ///< Whether the screen has been initialized

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialized) {
            return;
        }

        tabToggle = Toggle(&tabNames, &selectedTab);

        okButton = Button(
            getLocalizationService()
                .getMenuScreenText("MENU_BUTTON_OK")
                .value_or("OK"),
            [this] -> void {
                // TODO: Implement saving logic

                switchScreen(Screen::Of::MAIN_MENU);
            }
        );

        backButton = Button(
            getLocalizationService()
                .getMenuScreenText("MENU_BUTTON_BACK")
                .value_or("Back"),
            [this] -> void {
                switchScreen(Screen::Of::MAIN_MENU);
            }
        );

        tabContainer = Container::Tab(
            {
                Renderer([this] -> Element {
                    return vbox({
                        text(
                            getLocalizationService()
                                .getConfigText("CONFIG_LABEL_SYSTEM")
                                .value_or("System")
                        ) | bold | center,
                        separator(),
                        text("System settings will be added here") | center | dim,
                    }) | border | flex;
                }),
                Renderer([this] -> Element {
                    return vbox({
                        text(
                            getLocalizationService()
                                .getConfigText("CONFIG_LABEL_SCREEN")
                                .value_or("Screen")
                        ) | bold | center,
                        separator(),
                        text("Screen settings will be added here") | center | dim,
                    }) | border | flex;
                }),
                Renderer([this] -> Element {
                    return vbox({
                        text(
                            getLocalizationService()
                                .getConfigText("CONFIG_LABEL_SOUND")
                                .value_or("Sound")
                        ) | bold | center,
                        separator(),
                        text("Sound settings will be added here") | center | dim,
                    }) | border | flex;
                }),
                Renderer([this] -> Element {
                    return vbox({
                        text(
                            getLocalizationService()
                                .getConfigText("CONFIG_LABEL_VOICE")
                                .value_or("Voice")
                        ) | bold | center,
                        separator(),
                        text("Voice settings will be added here") | center | dim,
                    }) | border | flex;
                }),
            },
            &selectedTab
        );

        Component mainContainer = Container::Vertical({
            tabToggle,
            tabContainer,
            okButton,
            backButton,
        });

        Component componentWithEvents = CatchEvent(mainContainer, [this](Event event) -> bool {
            if (event == Event::Escape || (event == Event::Character('q'))) {
                switchScreen(Screen::Of::MAIN_MENU);
                return true;
            }
            return false;
        });

        component = Renderer(componentWithEvents, [this] -> Element {
            return vbox({
                hbox({
                    text(
                        getLocalizationService()
                            .getMenuScreenText("MENU_BUTTON_GAME_CONFIG")
                            .value_or("Config")
                    ) | bold | center | flex,
                    separator(),
                    okButton->Render(),
                    text(" "),
                    backButton->Render(),
                }),
                separator(),
                hbox({
                    text(" "),
                    tabToggle->Render() | center,
                    text(" ")
                }),
                separator(),
                tabContainer->Render() | flex,
            }) | border | flex;
        });

        initialized = true;
    }
public:
    /**
     * @brief Constructor for the ConfigScreen class
     *
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    ConfigScreen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization):
        Screen(game, host, localization) {
        createComponent();
    }

    /**
     * @brief Called when screen becomes active
     */
    void onActivate() noexcept override final {
        selectedTab = 0;
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
