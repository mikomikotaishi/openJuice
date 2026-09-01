/**
 * @file ScreenFactory.cppm
 * @module openjuice.ui.tui:ScreenFactory
 * @brief Implementation of the ScreenFactory class.
 *
 * This file contains the implementation of the ScreenFactory class, which is used to create Screen objects.
 */

module;

#include "Macros.hpp"

export module openjuice.ui:ScreenFactory;

import stdx;

import openjuice.engine.game;
import openjuice.engine.localization;
import openjuice.engine.save;
import openjuice.ui.Screen;
import openjuice.ui.screens;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::engine::save::ProfileManager;

using namespace openjuice::ui::screens;

BEGIN_MODULE_NAMESPACE(openjuice::ui);

/**
 * @class ScreenFactory
 * @brief Factory class for creating Screen objects.
 *
 * The ScreenFactory class creates Screen objects based on the given Screen::Of, forwarding
 * its injected dependencies into each screen it constructs.
 */
export class ScreenFactory final {
private:
    SharedPointer<LoggerFactory> loggerFactory; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The logger instance.
    SharedPointer<LocalizationService> localization; ///< The injected localization service.
    SharedPointer<ProfileManager> profile; ///< The injected profile manager.
public:
    /**
     * @brief Construct the factory with its injected dependencies.
     * @param loggerFactory The shared logger factory used to create this factory's logger
     * and each screen's logger.
     * @param localization The shared localization service forwarded into every screen.
     * @param profile The shared profile manager forwarded into screens that need it.
     */
    ScreenFactory(SharedPointer<LoggerFactory> loggerFactory, SharedPointer<LocalizationService> localization, SharedPointer<ProfileManager> profile):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("ScreenFactory")},
        localization{localization},
        profile{profile} {}

    /**
     * @brief Create a Screen object with the given type, game pointer and host.
     * @param type The type of the Screen to create
     * @param game A shared pointer to the game
     * @param host The interface that will run the created screen
     * @return SharedPointer<Screen> Shared pointer to the created Screen object 
     */
    [[nodiscard]]
    SharedPointer<Screen> create(Screen::Of type, SharedPointer<Game> game, Screen::Host& host) noexcept {
        #ifndef NDEBUG
        logger->debug("Creating Screen of type {}...", type);
        #endif

        switch (type) {
            case Screen::Of::LOADING:
                return Pointers::shared<LoadingScreen>(game, host, localization);
            case Screen::Of::TITLE:
                return Pointers::shared<TitleScreen>(game, host, localization, profile);
            case Screen::Of::MAIN_MENU:
                return Pointers::shared<MainMenuScreen>(game, host, localization, loggerFactory);
            case Screen::Of::SINGLEPLAYER_LOBBY_SELECT:
                return Pointers::shared<SingleplayerLobbySelectScreen>(game, host, localization);
            case Screen::Of::SINGLEPLAYER_CUSTOM:
                return Pointers::shared<SingleplayerCustomScreen>(game, host, localization);
            case Screen::Of::SINGLEPLAYER_CAMPAIGN_SELECT:
                return Pointers::shared<SingleplayerCampaignSelectScreen>(game, host, localization);
            case Screen::Of::MULTIPLAYER_LOBBY_SELECT:
                return Pointers::shared<MultiplayerLobbySelectScreen>(game, host, localization);
            case Screen::Of::MULTIPLAYER_CUSTOM:
                return Pointers::shared<MultiplayerCustomScreen>(game, host, localization);
            case Screen::Of::SINGLEPLAYER_GAME_LOBBY:
                return Pointers::shared<SingleplayerGameLobbyScreen>(game, host, localization);
            case Screen::Of::MULTIPLAYER_GAME_LOBBY:
                return Pointers::shared<MultiplayerGameLobbyScreen>(game, host, localization);
            case Screen::Of::CHARACTER_SELECT:
                return Pointers::shared<CharacterSelectScreen>(game, host, localization);
            case Screen::Of::CARD_SELECT:
                return Pointers::shared<CardSelectScreen>(game, host, localization);
            case Screen::Of::GAMEPLAY:
                return Pointers::shared<GameplayScreen>(game, host, localization);
            case Screen::Of::GAME_RESULTS:
                return Pointers::shared<GameResultsScreen>(game, host, localization);
            case Screen::Of::SHOP:
                return Pointers::shared<ShopScreen>(game, host, localization);
            case Screen::Of::PROFILE:
                return Pointers::shared<ProfileScreen>(game, host, localization);
            case Screen::Of::OJDEX:
                return Pointers::shared<OJDexScreen>(game, host, localization);
            case Screen::Of::GUIDE:
                return Pointers::shared<GuideScreen>(game, host, localization);
            case Screen::Of::CONFIG:
                return Pointers::shared<ConfigScreen>(game, host, localization);
            case Screen::Of::CREDITS:
                return Pointers::shared<CreditsScreen>(game, host, localization);
            case Screen::Of::PAUSE:
                return Pointers::shared<PauseScreen>(game, host, localization);
            case Screen::Of::EXIT:
            case Screen::Of::WIKI:
                logger->error("Attempted to create a Screen of type {} which is not a valid screen type.", type);
                return nullptr;
        }
        Ops::unreachable();
    }
};

END_MODULE_NAMESPACE();
