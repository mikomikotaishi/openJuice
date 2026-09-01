/**
 * @file Screen.cppm
 * @module openjuice.ui.Screen
 * @brief Base class for all TUI screens
 */

module;

#include "Macros.hpp"

export module openjuice.ui.Screen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.localization;

import ftxui;

using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;

using ftxui::Component;

BEGIN_MODULE_NAMESPACE(openjuice::ui);

/**
 * @class Screen
 * @brief Abstract base class for all TUI screens
 */
export class Screen {
public:
    /**
     * @enum Of
     * @brief All possible screen types that the game screen can be in
     */
    enum class Of: u8 {
        EXIT, ///< Exit (not a screen)
        LOADING, ///< Loading screen
        TITLE, ///< Title screen
        MAIN_MENU, ///< Game main menu screen
        SINGLEPLAYER_LOBBY_SELECT, ///< Game lobby selection screen (singleplayer)
        SINGLEPLAYER_CUSTOM, ///< Singleplayer custom mode screen
        SINGLEPLAYER_CAMPAIGN_SELECT, ///< Singleplayer campaign selection screen
        MULTIPLAYER_LOBBY_SELECT, ///< Game lobby selection screen (multiplayer)
        MULTIPLAYER_CUSTOM, ///< Multiplayer customisation screen
        SINGLEPLAYER_GAME_LOBBY, ///< Game lobby screen (singleplayer)
        MULTIPLAYER_GAME_LOBBY, ///< Game lobby screen (multiplayer)
        CHARACTER_SELECT, ///< Character selection screen
        CARD_SELECT, ///< Card selection screen
        GAMEPLAY, ///< Actual game
        GAME_RESULTS, ///< Game results screen
        SHOP, ///< Shop screen
        PROFILE, ///< Profile screen
        OJDEX, ///< OJDex menu screen
        GUIDE, ///< Guide/tutorial menu screen
        WIKI, ///< Wiki (not a screen)
        CONFIG, ///< Config/settings menu screen
        CREDITS, ///< Credits menu screen
        PAUSE, ///< Game paused screen
    };

    /**
     * @class Host
     * @brief The interface a screen uses to talk back to the interface running it.
     *
     * Screens do not own navigation or the terminal, so anything that outlives a single screen is
     * requested through this interface rather than performed directly. It is implemented by the
     * interface that owns the screens (UserInterface), and deliberately not an engine service:
     * every capability here is tied to a running TUI, which the engine has no notion of.
     */
    class Host {
        public:
            virtual ~Host() = default;

            /**
             * @brief Request a switch to a different screen.
             * @param type The screen to switch to
             */
            virtual void switchScreen(Of type) noexcept = 0;

            /**
             * @brief Report a failure to the user in a dialog they must acknowledge.
             * @param message The message to show
             *
             * For failures the user needs to know about, as opposed to the technical cause, which the
             * service that failed is responsible for logging.
             */
            virtual void showError(StringView message) noexcept = 0;
        };
protected:
    SharedPointer<Game> game; ///< A shared pointer to the game.
    Component component; ///< An abstract component
    Host& host; ///< The interface running this screen. Outlives it, so held by reference.
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
    void switchScreen(Of type) const noexcept {
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
     * @brief Constructor for the Screen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     */
    Screen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization):
        game{game}, host{host}, localization{localization} {}

    virtual ~Screen() = default;
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

using openjuice::ui::Screen;

namespace stdx::fmt {
    template <>
    struct Formatter<Screen::Of> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(const Screen::Of& st, FormatContext& ctx) {
            StringView name;
            switch (st) {
                case Screen::Of::EXIT:
                    name = "Exit";
                    break;
                case Screen::Of::LOADING:
                    name = "Loading";
                    break;
                case Screen::Of::TITLE:
                    name = "Title";
                    break;
                case Screen::Of::MAIN_MENU:
                    name = "Main Menu";
                    break;
                case Screen::Of::SINGLEPLAYER_LOBBY_SELECT:
                    name = "Singleplayer Lobby Selection";
                    break;
                case Screen::Of::SINGLEPLAYER_CUSTOM:
                    name = "Singleplayer Custom";
                    break;
                case Screen::Of::SINGLEPLAYER_CAMPAIGN_SELECT:
                    name = "Singleplayer Campaign Selection";
                    break;
                case Screen::Of::MULTIPLAYER_LOBBY_SELECT:
                    name = "Multiplayer Lobby Selection";
                    break;
                case Screen::Of::MULTIPLAYER_CUSTOM:
                    name = "Multiplayer Custom";
                    break;
                case Screen::Of::SINGLEPLAYER_GAME_LOBBY:
                    name = "Singleplayer Game Lobby";
                    break;
                case Screen::Of::MULTIPLAYER_GAME_LOBBY:
                    name = "Multiplayer Game Lobby";
                    break;
                case Screen::Of::CHARACTER_SELECT:
                    name = "Character Selection";
                    break;
                case Screen::Of::CARD_SELECT:
                    name = "Card Selection";
                    break;
                case Screen::Of::GAMEPLAY:
                    name = "Gameplay";
                    break;
                case Screen::Of::GAME_RESULTS:
                    name = "Game Results";
                    break;
                case Screen::Of::SHOP:
                    name = "Shop";
                    break;
                case Screen::Of::PROFILE:
                    name = "Profile";
                    break;
                case Screen::Of::OJDEX:
                    name = "OJDex";
                    break;
                case Screen::Of::GUIDE:
                    name = "Guide";
                    break;
                case Screen::Of::WIKI:
                    name = "Wiki";
                    break;
                case Screen::Of::CONFIG:
                    name = "Configuration";
                    break;
                case Screen::Of::CREDITS:
                    name = "Credits";
                    break;
                case Screen::Of::PAUSE:
                    name = "Pause";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(Screen::Of);
