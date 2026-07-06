/**
 * @file TextUserInterface.cppm
 * @module openjuice.ui.tui:TextUserInterface
 * @brief Text user interface implementation
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui:TextUserInterface;

import stdx;
import :TuiScreenFactory;

import openjuice.engine.game;
import openjuice.engine.services;
import openjuice.ui.UserInterface;
import openjuice.ui.tui.TuiScreen;
import openjuice.ui.tui.screens;

import ftxui;

using stdx::collections::TreeMap;
using stdx::mem::SharedPointer;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;
using openjuice::engine::services::LocalizationService;
using openjuice::engine::services::ProfileManager;

using namespace openjuice::ui::tui::screens;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TextUserInterface
 * @brief
 *
 * @extends UserInterface
 */
export class TextUserInterface: public UserInterface {
private:
    SharedPointer<LoggerFactory> loggerFactory; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The logger instance.
    SharedPointer<LocalizationService> localization; ///< The injected localization service.
    SharedPointer<ProfileManager> profile; ///< The injected profile manager.
    TuiScreenFactory screenFactory; ///< Factory that constructs screens with injected dependencies.

    TreeMap<ScreenType, SharedPointer<TuiScreen>> screens; ///< Map storing all initialized screens

    App screen = App::Fullscreen(); ///< Main screen
    ScreenType currentScreen = ScreenType::TITLE; ///< The current active screen type
    Component activeComponent; ///< Active FTXUI component
    Component containerComponent; ///< Container component that wraps the active component
    bool showExitDialog = false; ///< Flag to show exit confirmation dialog
    bool exitDialogSelection = false; ///< Selected option in exit dialog
    bool isLoopRunning = false; ///< Flag to track if screen.Loop() is running

    /**
     * @brief Get or create screen if it doesn't exist
     *
     * @param type Screen type to get
     * @return SharedPointer<TuiScreen> to the requested screen
     */
    [[nodiscard]]
    SharedPointer<TuiScreen> getScreen(ScreenType type) noexcept {
        auto switchCallback = [this](ScreenType newType) -> void {
            switchScreen(newType);
        };

        if (!screens.contains(type)) {
            screens[type] = screenFactory.create(type, game, switchCallback);
        }

        return screens[type];
    }

    /**
     * @brief Switch to a different screen
     *
     * @param type The screen to switch to
     */
    void switchScreen(ScreenType type) noexcept {
        #ifndef NDEBUG
        logger->debug("TextUserInterface: switching to screen type {}", type);
        #endif

        if (type == ScreenType::EXIT) {
            #ifndef NDEBUG
            logger->debug("Exiting TUI");
            #endif

            requestExit();
            screen.ExitLoopClosure()();
            return;
        }

        try {
            if (screens.contains(currentScreen) && currentScreen != type) {
                #ifndef NDEBUG
                logger->debug("TextUserInterface: deactivating current screen {}", currentScreen);
                #endif

                screens[currentScreen]->onDeactivate();
            }

            currentScreen = type;

            #ifndef NDEBUG
            logger->debug("TextUserInterface: getting new screen {}", currentScreen);
            #endif

            SharedPointer<TuiScreen> handlingScreen = getScreen(type);
            handlingScreen->onActivate();

            #ifndef NDEBUG
            logger->debug("TextUserInterface: screen switch complete");
            #endif

            activeComponent = handlingScreen->getComponent();
            
            #ifndef NDEBUG
            if (!activeComponent) {
                logger->error("TextUserInterface: activeComponent is null after switching to screen {}", type);
            }
            #endif
            
            if (isLoopRunning) {
                screen.PostEvent(Event::Custom);
            }
        } catch (const Exception& e) {
            logger->error("Error switching screens: {}", e.what());
        }
    }

    /**
     * @brief
     *
     * @return true if there is input, false otherwise
     */
    [[nodiscard]]
    bool hasInput() {
        return false;
    }

    /**
     * @brief
     *
     * @return String
     */
    [[nodiscard]]
    String readInput() {
        return "";
    }

    /**
     * @brief
     *
     * @param cmd
     */
    void processCommand(StringView cmd) {
        return;
    }
public:
    /**
     * @brief Constructor that initializes the base UserInterface
     *
     * @param game Shared pointer to game instance
     * @param mutex Reference to state mutex for synchronization
     * @param loggerFactory Shared logger factory for creating loggers and screens
     * @param localization Shared localization service forwarded into screens
     * @param profile Shared profile manager forwarded into screens
     */
    TextUserInterface(SharedPointer<Game> game, Mutex& mutex, SharedPointer<LoggerFactory> loggerFactory, SharedPointer<LocalizationService> localization, SharedPointer<ProfileManager> profile):
        UserInterface(game, mutex),
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("TextUserInterface")},
        localization{localization},
        profile{profile},
        screenFactory{loggerFactory, localization, profile} {
        screen.ForceHandleCtrlC(false);
    }

    /**
     * @brief
     */
    void init() override {
        containerComponent = Renderer([this](bool _) -> Element {
            Element mainContent = activeComponent ? activeComponent->Render() : text("Loading...");
            
            if (showExitDialog) {
                Element dialog = vbox({
                    text(
                        localization->getMenuScreenText("PLAYMENU_EXIT")
                            .value_or("Exit")
                    ) | bold | center,
                    separator(),
                    text(
                        localization->getCommentText("COM_GAME_QUITCONFIRM")
                            .value_or("Are you sure you want to exit the program?")
                    ) | center,
                    separator(),
                    hbox({
                        text(
                            stdx::fmt::format(
                                "{} {} ",
                                exitDialogSelection 
                                    ? ">" 
                                    : " ",
                                localization->getMenuScreenText("MENU_BUTTON_YES")
                                    .value_or("Yes")
                            )
                        ) | (exitDialogSelection ? inverted : nothing),
                        text(" "),
                        text(
                            stdx::fmt::format(
                                "{} {} ",
                                exitDialogSelection 
                                    ? " " 
                                    : ">",
                                localization->getMenuScreenText("MENU_BUTTON_NO")
                                    .value_or("No")
                            )
                        ) | (exitDialogSelection ? nothing : inverted),
                    }) | center,
                }) | border | center | bgcolor(Color::White);
                
                return dbox({
                    mainContent | dim,
                    dialog,
                });
            }
            
            return mainContent;
        });
        
        containerComponent = CatchEvent(containerComponent, [this](Event event) -> bool {
            if (showExitDialog) {
                if (
                    event == Event::ArrowLeft ||
                    event == Event::Character('h') ||
                    event == Event::ArrowRight ||
                    event == Event::Character('l') ||
                    event == Event::Tab
                ) {
                    exitDialogSelection = !exitDialogSelection;
                    return true;
                } else if (event == Event::Return || event == Event::Character(' ')) {
                    if (exitDialogSelection) {
                        switchScreen(ScreenType::EXIT);
                    } else {
                        showExitDialog = false;
                        exitDialogSelection = false;
                    }
                    return true;
                } else if (event == Event::Escape) {
                    showExitDialog = false;
                    exitDialogSelection = false;
                    return true;
                } else if (event == Event::CtrlC) {
                    return true;
                }
                return true;
            }
            
            if (event == Event::CtrlC) {
                showExitDialog = true;
                exitDialogSelection = false;
                return true;
            }
            
            return activeComponent ? activeComponent->OnEvent(event) : false;
        });
        
        switchScreen(ScreenType::TITLE);
    }

    /**
     * @brief
     */
    void processEvents() noexcept override {
        if (hasInput()) {
            String command = readInput();

            if (command == "exit") {
                requestExit();
            } else {
                ScopedLock<Mutex> lock(stateMutex);
                processCommand(command);
            }
        }
    }

    /**
     * @brief
     */
    void render() noexcept override {
        if (containerComponent) {
            isLoopRunning = true;
            screen.Loop(containerComponent);
            isLoopRunning = false;
        }
    }
};

END_MODULE_NAMESPACE();
