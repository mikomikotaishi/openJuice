/**
 * @file TuiScreenFactory.cppm
 * @module openjuice.ui.tui:TuiScreenFactory
 * @brief Implementation of the TuiScreenFactory class.
 *
 * This file contains the implementation of the TuiScreenFactory class, which is used to create TuiScreen objects.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui:TuiScreenFactory;

import stdx;

import openjuice.engine.game;
import openjuice.engine.managers;
import openjuice.ui.tui.TuiScreen;
import openjuice.ui.tui.screens;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;

using namespace openjuice::ui::tui::screens;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TuiScreenFactory
 * @brief Factory class for creating TuiScreen objects.
 *
 * The TuiScreenFactory class is a singleton factory class that creates TuiScreen objects based on the given ScreenType.
 */
export class TuiScreenFactory final {
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("TuiScreenFactory"); ///< The logger instance.
public:
    TuiScreenFactory() = delete("TuiScreenFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a TuiScreen object with the given type and game pointer and callback.
     * 
     * @param type The type of the TuiScreen to create
     * @param game A shared pointer to the game
     * @param callback The function callback used by the type
     * @return SharedPointer<TuiScreen> Shared pointer to the created TuiScreen object 
     */
    [[nodiscard]]
    static SharedPointer<TuiScreen> create(ScreenType type, SharedPointer<Game> game, Function<void(ScreenType)> callback) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating TuiScreen of type {}", type);
        #endif

        switch (type) {
            case ScreenType::LOADING:
                return Pointers::shared<LoadingScreen>(game, callback);
            case ScreenType::TITLE:
                return Pointers::shared<TitleScreen>(game, callback);
            case ScreenType::MAIN_MENU:
                return Pointers::shared<MainMenuScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_LOBBY_SELECT:
                return Pointers::shared<SingleplayerLobbySelectScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_CUSTOM:
                return Pointers::shared<SingleplayerCustomScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_CAMPAIGN_SELECT:
                return Pointers::shared<SingleplayerCampaignSelectScreen>(game, callback);
            case ScreenType::MULTIPLAYER_LOBBY_SELECT:
                return Pointers::shared<MultiplayerLobbySelectScreen>(game, callback);
            case ScreenType::MULTIPLAYER_CUSTOM:
                return Pointers::shared<MultiplayerCustomScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_GAME_LOBBY:
                return Pointers::shared<SingleplayerGameLobbyScreen>(game, callback);
            case ScreenType::MULTIPLAYER_GAME_LOBBY:
                return Pointers::shared<MultiplayerGameLobbyScreen>(game, callback);
            case ScreenType::CHARACTER_SELECT:
                return Pointers::shared<CharacterSelectScreen>(game, callback);
            case ScreenType::CARD_SELECT:
                return Pointers::shared<CardSelectScreen>(game, callback);
            case ScreenType::GAMEPLAY:
                return Pointers::shared<GameplayScreen>(game, callback);
            case ScreenType::GAME_RESULTS:
                return Pointers::shared<GameResultsScreen>(game, callback);
            case ScreenType::SHOP:
                return Pointers::shared<ShopScreen>(game, callback);
            case ScreenType::PROFILE:
                return Pointers::shared<ProfileScreen>(game, callback);
            case ScreenType::OJDEX:
                return Pointers::shared<OJDexScreen>(game, callback);
            case ScreenType::GUIDE:
                return Pointers::shared<GuideScreen>(game, callback);
            case ScreenType::CONFIG:
                return Pointers::shared<ConfigScreen>(game, callback);
            case ScreenType::CREDITS:
                return Pointers::shared<CreditsScreen>(game, callback);
            case ScreenType::PAUSE:
                return Pointers::shared<PauseScreen>(game, callback);
            default:
                Ops::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();
