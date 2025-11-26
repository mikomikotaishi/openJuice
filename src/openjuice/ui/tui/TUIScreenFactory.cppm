/**
 * @file TUIScreenFactory.cppm
 * @module openjuice.ui.tui.TUIScreenFactory
 * @brief Implementation of the TUIScreenFactory class.
 *
 * This file contains the implementation of the TUIScreenFactory class, which is used to create TUIScreen objects.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TUIScreenFactory;

import std;
import stdx;

import openjuice.engine.game.Game;
import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.util.Logging;
import openjuice.ui.tui.Screens;
import openjuice.ui.tui.TUIScreen;

using std::mem::SharedPointer;

namespace mem = std::mem;
namespace sys = std::sys;

using openjuice::engine::game::Game;

using namespace openjuice::engine::util::logging;
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
        Logger::getInstance().log(LogLevel::DEBUG, "Creating TUIScreen of type {}", type);
        #endif

        switch (type) {
            case ScreenType::LOADING:
                return mem::make_shared<LoadingScreen>(game, callback);
            case ScreenType::TITLE:
                return mem::make_shared<TitleScreen>(game, callback);
            case ScreenType::MAIN_MENU:
                return mem::make_shared<MainMenuScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_LOBBY_SELECT:
                return mem::make_shared<SingleplayerLobbySelectScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_CUSTOM:
                return mem::make_shared<SingleplayerCustomScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_CAMPAIGN_SELECT:
                return mem::make_shared<SingleplayerCampaignSelectScreen>(game, callback);
            case ScreenType::MULTIPLAYER_LOBBY_SELECT:
                return mem::make_shared<MultiplayerLobbySelectScreen>(game, callback);
            case ScreenType::MULTIPLAYER_CUSTOM:
                return mem::make_shared<MultiplayerCustomScreen>(game, callback);
            case ScreenType::SINGLEPLAYER_GAME_LOBBY:
                return mem::make_shared<SingleplayerGameLobbyScreen>(game, callback);
            case ScreenType::MULTIPLAYER_GAME_LOBBY:
                return mem::make_shared<MultiplayerGameLobbyScreen>(game, callback);
            case ScreenType::CHARACTER_SELECT:
                return mem::make_shared<CharacterSelectScreen>(game, callback);
            case ScreenType::CARD_SELECT:
                return mem::make_shared<CardSelectScreen>(game, callback);
            case ScreenType::GAMEPLAY:
                return mem::make_shared<GameplayScreen>(game, callback);
            case ScreenType::GAME_RESULTS:
                return mem::make_shared<GameResultsScreen>(game, callback);
            case ScreenType::SHOP:
                return mem::make_shared<ShopScreen>(game, callback);
            case ScreenType::PROFILE:
                return mem::make_shared<ProfileScreen>(game, callback);
            case ScreenType::OJDEX:
                return mem::make_shared<OJDexScreen>(game, callback);
            case ScreenType::GUIDE:
                return mem::make_shared<GuideScreen>(game, callback);
            case ScreenType::CONFIG:
                return mem::make_shared<ConfigScreen>(game, callback);
            case ScreenType::CREDITS:
                return mem::make_shared<CreditsScreen>(game, callback);
            case ScreenType::PAUSE:
                return mem::make_shared<PauseScreen>(game, callback);
            default:
                sys::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();
