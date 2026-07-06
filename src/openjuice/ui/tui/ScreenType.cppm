/**
 * @file ScreenType.cppm
 * @module openjuice.ui.tui.TuiScreen:ScreenType
 * @brief Enum of screen types used by the TUI
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TuiScreen:ScreenType;

import stdx;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @enum ScreenType
 * @brief All possible screen types that the game screen can be in
 */
export enum class ScreenType: u8 {
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

END_MODULE_NAMESPACE();

using openjuice::ui::tui::ScreenType;

template <>
struct Formatter<ScreenType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(const ScreenType& st, FormatContext& ctx) {
        StringView name;
        switch (st) {
            case ScreenType::EXIT:
                name = "Exit";
                break;
            case ScreenType::LOADING:
                name = "Loading";
                break;
            case ScreenType::TITLE:
                name = "Title";
                break;
            case ScreenType::MAIN_MENU:
                name = "Main Menu";
                break;
            case ScreenType::SINGLEPLAYER_LOBBY_SELECT:
                name = "Singleplayer Lobby Selection";
                break;
            case ScreenType::SINGLEPLAYER_CUSTOM:
                name = "Singleplayer Custom";
                break;
            case ScreenType::SINGLEPLAYER_CAMPAIGN_SELECT:
                name = "Singleplayer Campaign Selection";
                break;
            case ScreenType::MULTIPLAYER_LOBBY_SELECT:
                name = "Multiplayer Lobby Selection";
                break;
            case ScreenType::MULTIPLAYER_CUSTOM:
                name = "Multiplayer Custom";
                break;
            case ScreenType::SINGLEPLAYER_GAME_LOBBY:
                name = "Singleplayer Game Lobby";
                break;
            case ScreenType::MULTIPLAYER_GAME_LOBBY:
                name = "Multiplayer Game Lobby";
                break;
            case ScreenType::CHARACTER_SELECT:
                name = "Character Selection";
                break;
            case ScreenType::CARD_SELECT:
                name = "Card Selection";
                break;
            case ScreenType::GAMEPLAY:
                name = "Gameplay";
                break;
            case ScreenType::GAME_RESULTS:
                name = "Game Results";
                break;
            case ScreenType::SHOP:
                name = "Shop";
                break;
            case ScreenType::PROFILE:
                name = "Profile";
                break;
            case ScreenType::OJDEX:
                name = "OJDex";
                break;
            case ScreenType::GUIDE:
                name = "Guide";
                break;
            case ScreenType::WIKI:
                name = "Wiki";
                break;
            case ScreenType::CONFIG:
                name = "Configuration";
                break;
            case ScreenType::CREDITS:
                name = "Credits";
                break;
            case ScreenType::PAUSE:
                name = "Pause";
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(ScreenType);
