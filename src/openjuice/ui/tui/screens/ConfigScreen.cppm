/**
 * @file ConfigScreen.cppm
 * @brief Definition of the ConfigScreen class.
 *
 * This file contains the definition of the ConfigScreen class.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.Screens:ConfigScreen;

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
 * @class ConfigScreen
 * @brief Config/settings screen implementation
 *
 * @extends TUIScreen
 */
export class ConfigScreen final: public TUIScreen {
private:
    bool initialised = false; ///< Whether the screen has been initialised
    i32 selectedTab = 0; ///< The currently selected tab
    Vector<String> tabNames = {
        getTextManager().getConfigText("CONFIG_LABEL_SYSTEM")
            .transform([](StringView sv) -> String { return String(sv); })
            .value_or("System"),
        getTextManager().getConfigText("CONFIG_LABEL_SCREEN")
            .transform([](StringView sv) -> String { return String(sv); })
            .value_or("Screen"),
        getTextManager().getConfigText("CONFIG_LABEL_SOUND")
            .transform([](StringView sv) -> String { return String(sv); })
            .value_or("Sound"),
        getTextManager().getConfigText("CONFIG_LABEL_VOICE")
            .transform([](StringView sv) -> String { return String(sv); })
            .value_or("Voice")
    }; ///< The list of tab names

    Component tabContainer; ///< Container for tab content
    Component tabToggle; ///< Tab toggle component
    Component okButton; ///< Save button component
    Component backButton; ///< Back button component

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialised) {
            return;
        }

        tabToggle = Toggle(&tabNames, &selectedTab);

        okButton = Button(
            getTextManager().getMenuScreenText("MENU_BUTTON_OK")
                .transform([](StringView sv) -> String { return String(sv); })
                .value_or("OK"),
            [this]() -> void {
                // TODO: Implement saving logic

                screenSwitchCallback(ScreenType::MAIN_MENU);
            }
        );

        backButton = Button(
            getTextManager().getMenuScreenText("MENU_BUTTON_BACK")
                .transform([](StringView sv) -> String { return String(sv); })
                .value_or("Back"),
            [this]() -> void {
                screenSwitchCallback(ScreenType::MAIN_MENU);
            }
        );

        tabContainer = Container::Tab(
            {
                Renderer([this]() -> Element {
                    return vbox({
                        text(
                            getTextManager().getConfigText("CONFIG_LABEL_SYSTEM")
                                .transform([](StringView sv) -> String { return String(sv); })
                                .value_or("System")
                        ) | bold | center,
                        separator(),
                        text("System settings will be added here") | center | dim,
                    }) | border | flex;
                }),
                Renderer([this]() -> Element {
                    return vbox({
                        text(
                            getTextManager().getConfigText("CONFIG_LABEL_SCREEN")
                                .transform([](StringView sv) -> String { return String(sv); })
                                .value_or("Screen")
                        ) | bold | center,
                        separator(),
                        text("Screen settings will be added here") | center | dim,
                    }) | border | flex;
                }),
                Renderer([this]() -> Element {
                    return vbox({
                        text(
                            getTextManager().getConfigText("CONFIG_LABEL_SOUND")
                                .transform([](StringView sv) -> String { return String(sv); })
                                .value_or("Sound")
                        ) | bold | center,
                        separator(),
                        text("Sound settings will be added here") | center | dim,
                    }) | border | flex;
                }),
                Renderer([this]() -> Element {
                    return vbox({
                        text(
                            getTextManager().getConfigText("CONFIG_LABEL_VOICE")
                                .transform([](StringView sv) -> String { return String(sv); })
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
                screenSwitchCallback(ScreenType::MAIN_MENU);
                return true;
            }
            return false;
        });

        component = Renderer(componentWithEvents, [this]() -> Element {
            return vbox({
                hbox({
                    text(
                        getTextManager().getMenuScreenText("MENU_BUTTON_GAME_CONFIG")
                            .transform([](StringView sv) -> String { return String(sv); })
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

        initialised = true;
    }

    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the ConfigScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     */
    ConfigScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback):
        TUIScreen(util::move(game), util::move(callback)) {
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
