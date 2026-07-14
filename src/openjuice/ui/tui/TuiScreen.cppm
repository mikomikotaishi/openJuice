/**
 * @file TuiScreen.cppm
 * @module openjuice.ui.tui.TuiScreen
 * @brief Base class for all TUI screens
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TuiScreen;

export import :ScreenType;
export import :ScreenHost;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;

import ftxui;

using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::services::LocalizationService;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TuiScreen
 * @brief Abstract base class for all TUI screens
 */
export class TuiScreen {
protected:
    SharedPointer<Game> game; ///< A shared pointer to the game.
    Component component; ///< An abstract component
    ScreenHost& host; ///< The interface running this screen. Outlives it, so held by reference.
    SharedPointer<LocalizationService> localization; ///< The injected localization service.

    /**
     * @brief Get the LocalizationService instance safely.
     * @return Reference to the LocalizationService.
     */
    [[nodiscard]]
    const LocalizationService& getLocalizationService() const noexcept {
        return *localization;
    }

    /**
     * @brief Get a menu screen label, kept to a single line.
     * @param key The localization key to look up
     * @param fallback Text to use when the key is missing
     * @return The label on one line
     *
     * A few labels carry a line break sized for the original game's square buttons. FTXUI's menu
     * prefixes only the first line of an entry, so keeping the break would leave continuation lines
     * unaligned under the selection marker. Prose from the same file keeps its breaks: it is not
     * fetched through here.
     */
    [[nodiscard]]
    String menuLabel(StringView key, StringView fallback) const noexcept {
        String label = getLocalizationService()
            .getMenuScreenText(key)
            .value_or(String(fallback));

        for (char& ch: label) {
            if (ch == '\n') {
                ch = ' ';
            }
        }

        return label;
    }

    /**
     * @brief Switch to a different screen.
     * @param type The screen to switch to
     */
    void switchScreen(ScreenType type) const noexcept {
        host.switchScreen(type);
    }

    /**
     * @brief Report a failure to the user in a dialog they must acknowledge.
     * @param message The message to show
     *
     * Use this instead of logging a failure that came from a service: the service already logged
     * the technical cause, and only the screen knows the user is waiting on the outcome.
     */
    void showError(StringView message) const noexcept {
        host.showError(message);
    }

    /**
     * @brief Creates the screen component
     */
    virtual void createComponent() noexcept = 0;

    /**
     * @brief Constructor for the TuiScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    TuiScreen(SharedPointer<Game> game, ScreenHost& host, SharedPointer<LocalizationService> localization):
        game{game}, host{host}, localization{localization} {}

    virtual ~TuiScreen() = default;
public:
    /**
     * @brief Get the FTXUI component for this screen
     * @return The component
     */
    virtual Component getComponent() const noexcept {
        return component;
    }

    /**
     * @brief Called when the screen becomes active
     */
    virtual void onActivate() noexcept = 0;

    /**
     * @brief Called when the screen becomes inactive
     */
    virtual void onDeactivate() noexcept = 0;

    /**
     * @brief Update screen logic
     */
    virtual void update() noexcept = 0;

    /**
     * @brief Check if the screen requested exit
     * @return True if exit was requested, else false
     */
    [[nodiscard]]
    virtual bool shouldExit() const noexcept {
        return false;
    }
};

END_MODULE_NAMESPACE();
