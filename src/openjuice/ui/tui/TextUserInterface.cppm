/**
 * @file TextUserInterface.cppm
 * @module openjuice.ui.tui:TextUserInterface
 * @brief Text user interface implementation
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui:TextUserInterface;

import :TuiScreenFactory;

import stdx;

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
 * @brief Text-based user interface implementation using FTXUI
 * @extends UserInterface
 */
export class TextUserInterface: public UserInterface, public ScreenHost {
private:
    /**
     * @struct Dialog
     * @brief An overlay shown above the active screen, which swallows input until dismissed.
     */
    struct Dialog {
        String title; ///< Heading shown at the top of the dialog.
        String message; ///< Body text.
        String acceptLabel; ///< Label of the accepting button.
        String dismissLabel = ""; ///< Label of the dismissing button, empty when there is only one button.
        Function<void()> onAccept = nullptr; ///< Runs when the dialog is accepted. May be empty.
        bool accepting = false; ///< True while the accepting button is highlighted.

        /**
         * @brief Whether the dialog offers a choice rather than a single acknowledgement.
         * @return True if there are two buttons
         */
        [[nodiscard]]
        bool isChoice() const noexcept {
            return !dismissLabel.empty();
        }
    };

    SharedPointer<Logger> logger; ///< The logger instance.
    SharedPointer<LocalizationService> localization; ///< The injected localization service.
    SharedPointer<ProfileManager> profile; ///< The injected profile manager.
    TuiScreenFactory screenFactory; ///< Factory that constructs screens with injected dependencies.

    TreeMap<ScreenType, SharedPointer<TuiScreen>> screens; ///< Map storing all initialized screens

    App screen = App::Fullscreen(); ///< Main screen
    ScreenType currentScreen = ScreenType::TITLE; ///< The current active screen type
    Component activeComponent; ///< Active FTXUI component
    Component containerComponent; ///< Container component that wraps the active component
    Optional<Dialog> dialog; ///< The dialog currently overlaying the active screen, if any.
    bool isLoopRunning = false; ///< Flag to track if screen.Loop() is running

    /**
     * @brief Get or create screen if it doesn't exist
     * @param type Screen type to get
     * @return SharedPointer<TuiScreen> to the requested screen
     */
    [[nodiscard]]
    SharedPointer<TuiScreen> getScreen(ScreenType type) noexcept {
        if (!screens.contains(type)) {
            screens[type] = screenFactory.create(type, game, *this);
        }

        return screens[type];
    }

    /**
     * @brief Build the element for a dialog overlay.
     * @param active The dialog to draw
     * @return The dialog element
     */
    [[nodiscard]]
    Element renderDialog(const Dialog& active) const noexcept {
        Elements buttons;
        buttons.push_back(
            text(Ops::fmt("{} {} ", active.accepting ? ">" : " ", active.acceptLabel))
                | (active.accepting ? inverted : nothing)
        );

        if (active.isChoice()) {
            buttons.push_back(text(" "));
            buttons.push_back(
                text(Ops::fmt("{} {} ", active.accepting ? " " : ">", active.dismissLabel))
                    | (active.accepting ? nothing : inverted)
            );
        }

        return vbox({
            text(active.title) | bold | center,
            separator(),
            paragraphAlignCenter(active.message),
            separator(),
            hbox(buttons) | center,
        }) | border | center | bgcolor(Color::White);
    }

    /**
     * @brief Route an event to the open dialog, swallowing everything the screen must not see.
     * @param event The event to handle
     * @return Always true, since an open dialog is modal
     */
    bool handleDialogEvent(Event event) noexcept {
        if (
            dialog->isChoice() && (
                event == Event::ArrowLeft ||
                event == Event::Character('h') ||
                event == Event::ArrowRight ||
                event == Event::Character('l') ||
                event == Event::Tab
            )
        ) {
            dialog->accepting = !dialog->accepting;
            return true;
        }

        if (event == Event::Return || event == Event::Character(' ')) {
            if (dialog->accepting) {
                acceptDialog();
            } else {
                dialog.reset();
            }
            return true;
        }

        if (event == Event::Escape) {
            dialog.reset();
            return true;
        }

        return true;
    }

    /**
     * @brief Close the open dialog and run whatever it was confirming.
     *
     * The action is moved out before the dialog is cleared, so it stays valid if it opens another.
     */
    void acceptDialog() noexcept {
        Function<void()> action = Ops::move(dialog->onAccept);
        dialog.reset();

        if (action) {
            action();
        }
    }

    /**
     * @brief Raise the exit confirmation dialog.
     */
    void confirmExit() noexcept {
        dialog = Dialog {
            .title = localization->getMenuScreenText("PLAYMENU_EXIT")
                .value_or("Exit"),
            .message = localization->getCommentText("COM_GAME_QUITCONFIRM")
                .value_or("Are you sure you want to exit the program?"),
            .acceptLabel = localization->getMenuScreenText("MENU_BUTTON_YES")
                .value_or("Yes"),
            .dismissLabel = localization->getMenuScreenText("MENU_BUTTON_NO")
                .value_or("No"),
            .onAccept = [this] -> void {
                switchScreen(ScreenType::EXIT);
            },
        };
    }

    /**
     * @brief
     * @return true if there is input, false otherwise
     */
    [[nodiscard]]
    bool hasInput() {
        return false;
    }

    /**
     * @brief
     * @return String
     */
    [[nodiscard]]
    String readInput() {
        return "";
    }

    /**
     * @brief
     * @param cmd
     */
    void processCommand(StringView cmd) {
        return;
    }
public:
    /**
     * @brief Switch to a different screen
     * @param type The screen to switch to
     */
    void switchScreen(ScreenType type) noexcept override final {
        #ifndef NDEBUG
        logger->debug("Switching to screen type {}", type);
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
                logger->debug("Deactivating current screen {}", currentScreen);
                #endif

                screens[currentScreen]->onDeactivate();
            }

            currentScreen = type;

            SharedPointer<TuiScreen> handlingScreen = getScreen(type);
            handlingScreen->onActivate();

            #ifndef NDEBUG
            logger->debug("Screen switch complete");
            #endif

            activeComponent = handlingScreen->getComponent();

            if (!activeComponent) {
                logger->error("activeComponent is null after switching to screen {}", type);
            }

            if (isLoopRunning) {
                screen.PostEvent(Event::Custom);
            }
        } catch (const Exception& e) {
            logger->error("Error switching screens: {}", e.what());
        }
    }

    /**
     * @brief Report a failure to the user in a dialog they must acknowledge.
     *
     * The service that failed is responsible for logging the technical cause, so nothing is
     * logged here.
     *
     * @param message The message to show
     */
    void showError(StringView message) noexcept override final {
        dialog = Dialog {
            // The game ships this string as ERROR_CAPTION in error.txt, which LocalizationService
            // has no getter for yet.
            .title = "Error",
            .message = String(message),
            .acceptLabel = localization->getMenuScreenText("MENU_BUTTON_OK")
                .value_or("OK"),
            .accepting = true,
        };

        if (isLoopRunning) {
            screen.PostEvent(Event::Custom);
        }
    }

    /**
     * @brief Constructor that initializes the base UserInterface
     * @param game Shared pointer to game instance
     * @param mutex Reference to state mutex for synchronization
     * @param loggerFactory Shared logger factory for creating loggers and screens
     * @param localization Shared localization service forwarded into screens
     * @param profile Shared profile manager forwarded into screens
     */
    TextUserInterface(SharedPointer<Game> game, Mutex& mutex, SharedPointer<LoggerFactory> loggerFactory, SharedPointer<LocalizationService> localization, SharedPointer<ProfileManager> profile):
        UserInterface(game, mutex),
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

            if (!dialog) {
                return mainContent;
            }

            return dbox({
                mainContent | dim,
                renderDialog(*dialog),
            });
        });

        containerComponent = CatchEvent(containerComponent, [this](Event event) -> bool {
            if (dialog) {
                return handleDialogEvent(event);
            }

            if (event == Event::CtrlC) {
                confirmExit();
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
