/**
 * @file UserInterface.cppm
 * @module openjuice.ui.tui:UserInterface
 * @brief Text user interface implementation
 */

module;

#include "Macros.hpp"

export module openjuice.ui:UserInterface;

import :ScreenFactory;

import stdx;

import openjuice.engine.game;
import openjuice.engine.localization;
import openjuice.engine.net;
import openjuice.engine.save;
import openjuice.ui.Screen;
import openjuice.ui.screens;

import ftxui;

using stdx::collections::TreeMap;
using stdx::collections::Vector;
using stdx::mem::SharedPointer;
using stdx::sync::Atomic;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::util::logging::Logger;

using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::engine::net::NetworkingService;
using openjuice::engine::save::ProfileManager;

using namespace openjuice::ui::screens;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui);

/**
 * @class UserInterface
 * @brief Text-based user interface implementation using FTXUI
 * @extends UserInterface
 */
export class UserInterface: public Screen::Host {
private:
    /**
     * @struct PendingError
     * @brief A failure captured off the UI thread, waiting to be shown as a dialog.
     */
    struct PendingError {
        String message; ///< The user-facing message.
        String detail; ///< Technical detail such as a stack trace. May be empty.
    };

    /**
     * @struct Dialog
     * @brief An overlay shown above the active screen, which swallows input until dismissed.
     */
    struct Dialog {
        String title; ///< Heading shown at the top of the dialog.
        String message; ///< Body text.
        String detail = ""; ///< Technical detail (e.g. a stack trace), shown in a scrollable region. Empty when absent.
        String acceptLabel; ///< Label of the accepting button.
        String dismissLabel = ""; ///< Label of the dismissing button, empty when there is only one button.
        Function<void()> onAccept = nullptr; ///< Runs when the dialog is accepted. May be empty.
        bool accepting = false; ///< True while the accepting button is highlighted.

        /**
         * @brief Whether the dialog carries technical detail to display.
         * @return True if there is a detail body
         */
        [[nodiscard]]
        bool hasDetail() const noexcept {
            return !detail.empty();
        }

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
    SharedPointer<NetworkingService> networking; ///< The injected networking service.
    ScreenFactory screenFactory; ///< Factory that constructs screens with injected dependencies.

    TreeMap<Screen::Of, SharedPointer<Screen>> screens; ///< Map storing all initialized screens

    SharedPointer<Game> game;
    Atomic<bool> exitRequested = false;
    App screen = App::Fullscreen(); ///< Main screen
    Screen::Of currentScreen = Screen::Of::TITLE; ///< The current active screen type
    Component activeComponent; ///< Active FTXUI component
    Component containerComponent; ///< Container component that wraps the active component
    Optional<Dialog> dialog; ///< The dialog currently overlaying the active screen, if any.
    bool isLoopRunning = false; ///< Flag to track if screen.Loop() is running

    Mutex errorMutex; ///< Guards pendingError, which is written from other threads.
    Optional<PendingError> pendingError; ///< A failure awaiting display on the UI thread.

    /**
     * @brief Move the most recent cross-thread failure into a dialog, on the UI thread.
     *
     * Called from the UI thread only. Building the Dialog here (rather than in reportError) keeps
     * all mutation of `dialog` on the thread that renders it, so no lock is needed around it.
     */
    void drainPendingError() noexcept {
        Optional<PendingError> error;
        {
            ScopedLock<Mutex> lock(errorMutex);
            error.swap(pendingError);
        }

        if (error.has_value()) {
            showError(error->message, error->detail);
        }
    }

    /**
     * @brief Get or create screen if it doesn't exist
     * @param type Screen type to get
     * @return SharedPointer<Screen> to the requested screen
     */
    [[nodiscard]]
    SharedPointer<Screen> getScreen(Screen::Of type) noexcept {
        if (!screens.contains(type)) {
            screens[type] = screenFactory.create(type, game, *this);
        }

        return screens[type];
    }

    /**
     * @brief Break a block of text into individual lines.
     * @param text The text to split, using '\n' as the separator
     * @return One entry per line, with newline characters removed
     *
     * FTXUI's text() renders a single line, so a multi-line stack trace must be split into
     * separate elements before it can be laid out (and scrolled) in a vbox.
     */
    [[nodiscard]]
    static Vector<String> splitLines(const String& text) noexcept {
        Vector<String> lines;
        String current;

        for (char ch: text) {
            if (ch == '\n') {
                lines.push_back(Ops::move(current));
                current.clear();
            } else if (ch != '\r') {
                current.push_back(ch);
            }
        }

        lines.push_back(Ops::move(current));
        return lines;
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

        Elements body;
        body.push_back(text(active.title) | bold | center);
        body.push_back(separator());
        body.push_back(paragraphAlignCenter(active.message));

        if (active.hasDetail()) {
            Elements traceLines;
            for (String& line: splitLines(active.detail)) {
                traceLines.push_back(text(Ops::move(line)));
            }

            body.push_back(separator());
            body.push_back(
                vbox(Ops::move(traceLines))
                    | vscroll_indicator | yframe
                    | size(HEIGHT, LESS_THAN, 12)
                    | size(WIDTH, LESS_THAN, 100)
            );
        }

        body.push_back(separator());
        body.push_back(hbox(buttons) | center);

        return vbox(Ops::move(body)) | border | center | bgcolor(Color::White);
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

        if (action != nullptr) {
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
                switchScreen(Screen::Of::EXIT);
            },
        };
    }
public:
    [[nodiscard]]
    bool shouldExit() const noexcept {
        return exitRequested.load();
    }

    void requestExit() noexcept {
        exitRequested.store(true);
    }

    /**
     * @brief Switch to a different screen
     * @param type The screen to switch to
     */
    void switchScreen(Screen::Of type) noexcept override final {
        #ifndef NDEBUG
        logger->debug("Switching to screen type {}...", type);
        #endif

        if (type == Screen::Of::EXIT) {
            #ifndef NDEBUG
            logger->debug("Exiting TUI...");
            #endif

            requestExit();
            screen.ExitLoopClosure()();
            return;
        }

        try {
            if (screens.contains(currentScreen) && currentScreen != type) {
                #ifndef NDEBUG
                logger->debug("Deactivating current screen {}...", currentScreen);
                #endif

                screens[currentScreen]->onDeactivate();
            }

            currentScreen = type;

            SharedPointer<Screen> handlingScreen = getScreen(type);
            handlingScreen->onActivate();

            #ifndef NDEBUG
            logger->debug("Screen switch complete!");
            #endif

            activeComponent = handlingScreen->getComponent();

            if (activeComponent == nullptr) {
                logger->error("activeComponent is null after switching to screen {}!", type);
            }

            if (isLoopRunning) {
                screen.PostEvent(Event::Custom);
            }
        } catch (const Exception& e) {
            logger->error("Error switching screens: {}!", e.what());
        }
    }

    /**
     * @brief Report a failure to the user in a dialog they must acknowledge.
     * @param message The message to show
     *
     * The service that failed is responsible for logging the technical cause, so nothing is
     * logged here.
     */
    void showError(StringView message) noexcept override final {
        showError(message, "");
    }

    /**
     * @brief Report a failure to the user, along with technical detail they can scroll through.
     * @param message The message to show
     * @param detail Technical detail such as a stack trace, shown in a scrollable region
     *
     * Must be called on the UI thread, since it touches the dialog the renderer reads. Code on
     * another thread must use reportError() instead.
     */
    void showError(StringView message, StringView detail) noexcept {
        dialog = Dialog {
            .title = localization->getErrorText("ERROR_CAPTION")
                .value_or("Error"),
            .message = String(message),
            .detail = String(detail),
            .acceptLabel = localization->getMenuScreenText("MENU_BUTTON_OK")
                .value_or("OK"),
            .accepting = true,
        };

        if (isLoopRunning) {
            screen.PostEvent(Event::Custom);
        }
    }

    /**
     * @brief Surface a failure raised on another thread, safely.
     * @param message The message to show
     * @param detail Technical detail such as a stack trace
     *
     * Safe to call from any thread. The failure is stashed under a lock and the UI loop is woken;
     * the dialog itself is built on the UI thread the next time it drains the mailbox. Only the
     * most recent failure is kept, since the user acknowledges one dialog at a time.
     */
    void reportError(StringView message, StringView detail) noexcept {
        {
            ScopedLock<Mutex> lock(errorMutex);
            pendingError = PendingError {
                .message = String(message),
                .detail = String(detail),
            };
        }

        if (isLoopRunning) {
            screen.PostEvent(Event::Custom);
        }
    }

    /**
     * @brief Constructor that initializes the base UserInterface
     * @param game Shared pointer to game instance
     * @param logger The logger for the user interface.
     * @param localization Shared localization service forwarded into screens
     * @param profile Shared profile manager forwarded into screens
     * @param networking Shared networking service forwarded into the online screens
     */
    UserInterface(SharedPointer<Game> game, SharedPointer<Logger> logger, SharedPointer<LocalizationService> localization, SharedPointer<ProfileManager> profile, SharedPointer<NetworkingService> networking):
        logger{Ops::move(logger)},
        localization{localization},
        profile{profile},
        networking{networking},
        screenFactory{this->logger, localization, profile, networking},
        game{Ops::move(game)} {
        screen.ForceHandleCtrlC(false);
    }

    /**
     * @brief
     */
    void init() {
        containerComponent = Renderer([this](bool _) -> Element {
            drainPendingError();

            Element mainContent = activeComponent 
                ? activeComponent->Render()
                : text(localization->getMenuScreenText("PLAYMENU_LOADING_TEXT").value_or("Loading..."));

            if (!dialog.has_value()) {
                return mainContent;
            }

            return dbox({
                mainContent | dim,
                renderDialog(*dialog),
            });
        });

        containerComponent = CatchEvent(containerComponent, [this](Event event) -> bool {
            if (dialog.has_value()) {
                return handleDialogEvent(event);
            }

            if (event == Event::CtrlC) {
                confirmExit();
                return true;
            }

            return activeComponent ? activeComponent->OnEvent(event) : false;
        });

        switchScreen(Screen::Of::TITLE);
    }

    /**
     * @brief
     */
    void render() noexcept {
        if (containerComponent != nullptr) {
            isLoopRunning = true;
            screen.Loop(containerComponent);
            isLoopRunning = false;
        }
    }
};

END_MODULE_NAMESPACE();
