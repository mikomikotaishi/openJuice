/**
 * @file TextUserInterface.cppm
 * @module openjuice.ui.tui.TextUserInterface
 * @brief Text user interface implementation
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TextUserInterface;

import std;
import stdx;

import openjuice.engine.game.Game;
import openjuice.engine.managers.TextManager;
import openjuice.ui.UserInterface;
import openjuice.ui.tui.Screens;
import openjuice.ui.tui.TUIScreen;
import openjuice.ui.tui.TUIScreenFactory;
import openjuice.ui.tui.TUIUtils;

import ftxui;

using std::mem::SharedPointer;
using std::sync::Mutex;
using std::sync::ScopedLock;
using std::sys::Signal;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fmt = std::fmt;
namespace mem = std::mem;
namespace sys = std::sys;

using namespace std::collections;

using openjuice::engine::game::Game;
using openjuice::engine::managers::TextManager;

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
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("TextUserInterface"); ///< The logger instance.

    TreeMap<ScreenType, SharedPointer<TUIScreen>> screens; ///< Map storing all initialised screens

    ScreenInteractive screen = ScreenInteractive::Fullscreen(); ///< Main screen
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
     * @return SharedPointer<TUIScreen> to the requested screen
     */
    [[nodiscard]]
    SharedPointer<TUIScreen> getScreen(ScreenType type) noexcept {
        auto switchCallback = [this](ScreenType newType) -> void {
            switchScreen(newType);
        };

        if (!screens.contains(type)) {
            screens[type] = TUIScreenFactory::create(type, game, switchCallback);
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
        LOGGER->debug("TextUserInterface: switching to screen type {}", type);
        #endif

        if (type == ScreenType::EXIT) {
            #ifndef NDEBUG
            LOGGER->debug("Exiting TUI");
            #endif

            requestExit();
            screen.ExitLoopClosure()();
            return;
        }

        try {
            if (screens.contains(currentScreen) && currentScreen != type) {
                #ifndef NDEBUG
                LOGGER->debug("TextUserInterface: deactivating current screen {}", currentScreen);
                #endif

                screens[currentScreen]->onDeactivate();
            }

            currentScreen = type;

            #ifndef NDEBUG
            LOGGER->debug("TextUserInterface: getting new screen {}", currentScreen);
            #endif

            SharedPointer<TUIScreen> handlingScreen = getScreen(type);
            handlingScreen->onActivate();

            #ifndef NDEBUG
            LOGGER->debug("TextUserInterface: screen switch complete");
            #endif

            activeComponent = handlingScreen->getComponent();
            
            #ifndef NDEBUG
            if (!activeComponent) {
                LOGGER->error("TextUserInterface: activeComponent is null after switching to screen {}", type);
            }
            #endif
            
            if (isLoopRunning) {
                screen.PostEvent(Event::Custom);
            }
        } catch (const Exception& e) {
            LOGGER->error("Error switching screens: {}", e.what());
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
     * @brief Constructor that initialises the base UserInterface
     *
     * @param state Shared pointer to game instance
     * @param mutex Reference to state mutex for synchronisation
     */
    TextUserInterface(SharedPointer<Game> game, Mutex& mutex):
        UserInterface(game, mutex) {
        screen.ForceHandleCtrlC(false);
    }

    /**
     * @brief
     */
    void init() override {
        containerComponent = Renderer([this]([[maybe_unused]] bool focused) -> Element {
            Element mainContent = activeComponent ? activeComponent->Render() : text("Loading...");
            
            if (showExitDialog) {
                Element dialog = vbox({
                    text(
                        TextManager::getInstance()
                            .getMenuScreenText("PLAYMENU_EXIT")
                            .transform([](StringView sv) -> String { return String(sv); })
                            .value_or("Exit")
                    ) | bold | center,
                    separator(),
                    text(
                        TextManager::getInstance()
                            .getCommentText("COM_GAME_QUITCONFIRM")
                            .transform([](StringView sv) -> String { return String(sv); })
                            .value_or("Are you sure you want to exit the program?")
                    ) | center,
                    separator(),
                    hbox({
                        text(
                            fmt::format(
                                "{} {} ",
                                exitDialogSelection 
                                    ? ">" 
                                    : " ",
                                TextManager::getInstance()
                                    .getMenuScreenText("MENU_BUTTON_YES")
                                    .value_or("Yes")
                            )
                        ) | (exitDialogSelection ? inverted : nothing),
                        text(" "),
                        text(
                            fmt::format(
                                "{} {} ",
                                exitDialogSelection 
                                    ? " " 
                                    : ">",
                                TextManager::getInstance()
                                    .getMenuScreenText("MENU_BUTTON_NO")
                                    .transform([](StringView sv) -> String { return String(sv); })
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
