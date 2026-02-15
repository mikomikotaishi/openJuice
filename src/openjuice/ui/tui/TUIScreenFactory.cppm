/**
 * @file TUIScreenFactory.cppm
 * @module openjuice.ui.tui:TUIScreenFactory
 * @brief Implementation of the TUIScreenFactory class.
 *
 * This file contains the implementation of the TUIScreenFactory class, which is used to create TUIScreen objects.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui:TUIScreenFactory;

import stdx;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.ui.tui.TUIScreen;
import openjuice.ui.tui.screens;

using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;

using namespace openjuice::ui::tui::screens;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TUIScreenFactory
 * @brief Factory class for creating TUIScreen objects.
 *
 * The TUIScreenFactory class is a singleton factory class that creates TUIScreen objects based on the given ScreenType.
 */
export class TUIScreenFactory final {
private:
    UTILITY_CLASS(TUIScreenFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("TUIScreenFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a TUIScreen object with the given type and game pointer and callback.
     * 
     * @param type The type of the TUIScreen to create
     * @param game A shared pointer to the game
     * @param callback The function callback used by the type
     * @return SharedPointer<TUIScreen> Shared pointer to the created TUIScreen object 
     */
    [[nodiscard]]
    static SharedPointer<TUIScreen> create(ScreenType type, SharedPointer<Game> game, Function<void(ScreenType)> callback) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating TUIScreen of type {}", type);
        #endif

        switch (type) {
            case ScreenType::LOADING:
                return stdx::mem::make_shared<LoadingScreen>(game, callback);
            case ScreenType::TITLE:
                return stdx::mem::make_shared<TitleScreen>(game, callback);
            case ScreenType::MAIN_MENU:
                return stdx::mem::make_shared<MainMenuScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_LOBBY_SELECT:
                return stdx::mem::make_shared<SingleplayerLobbySelectScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_CUSTOM:
                return stdx::mem::make_shared<SingleplayerCustomScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_CAMPAIGN_SELECT:
                return stdx::mem::make_shared<SingleplayerCampaignSelectScreen>(game, callback);
            case ScreenType::MULTIPLAYER_LOBBY_SELECT:
                return stdx::mem::make_shared<MultiplayerLobbySelectScreen>(game, callback);
            case ScreenType::MULTIPLAYER_CUSTOM:
                return stdx::mem::make_shared<MultiplayerCustomScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_GAME_LOBBY:
                return stdx::mem::make_shared<SingleplayerGameLobbyScreen>(game, callback);
            case ScreenType::MULTIPLAYER_GAME_LOBBY:
                return stdx::mem::make_shared<MultiplayerGameLobbyScreen>(game, callback);
            case ScreenType::CHARACTER_SELECT:
                return stdx::mem::make_shared<CharacterSelectScreen>(game, callback);
            case ScreenType::CARD_SELECT:
                return stdx::mem::make_shared<CardSelectScreen>(game, callback);
            case ScreenType::GAMEPLAY:
                return stdx::mem::make_shared<GameplayScreen>(game, callback);
            case ScreenType::GAME_RESULTS:
                return stdx::mem::make_shared<GameResultsScreen>(game, callback);
            case ScreenType::SHOP:
                return stdx::mem::make_shared<ShopScreen>(game, callback);
            case ScreenType::PROFILE:
                return stdx::mem::make_shared<ProfileScreen>(game, callback);
            case ScreenType::OJDEX:
                return stdx::mem::make_shared<OJDexScreen>(game, callback);
            case ScreenType::GUIDE:
                return stdx::mem::make_shared<GuideScreen>(game, callback);
            case ScreenType::CONFIG:
                return stdx::mem::make_shared<ConfigScreen>(game, callback);
            case ScreenType::CREDITS:
                return stdx::mem::make_shared<CreditsScreen>(game, callback);
            case ScreenType::PAUSE:
                return stdx::mem::make_shared<PauseScreen>(game, callback);
            default:
                stdx::sys::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();
