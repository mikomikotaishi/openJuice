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
import openjuice.engine.services;
import openjuice.ui.tui.TuiScreen;
import openjuice.ui.tui.screens;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::game::Game;
using openjuice::engine::services::LocalizationService;
using openjuice::engine::services::ProfileManager;

using namespace openjuice::ui::tui::screens;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TuiScreenFactory
 * @brief Factory class for creating TuiScreen objects.
 *
 * The TuiScreenFactory class creates TuiScreen objects based on the given ScreenType, forwarding
 * its injected dependencies into each screen it constructs.
 */
export class TuiScreenFactory final {
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
    TuiScreenFactory(SharedPointer<LoggerFactory> loggerFactory, SharedPointer<LocalizationService> localization, SharedPointer<ProfileManager> profile):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("TuiScreenFactory")},
        localization{localization},
        profile{profile} {}

    /**
     * @brief Create a TuiScreen object with the given type, game pointer and host.
     * @param type The type of the TuiScreen to create
     * @param game A shared pointer to the game
     * @param host The interface that will run the created screen
     * @return SharedPointer<TuiScreen> Shared pointer to the created TuiScreen object 
     */
    [[nodiscard]]
    SharedPointer<TuiScreen> create(ScreenType type, SharedPointer<Game> game, ScreenHost& host) noexcept {
        #ifndef NDEBUG
        logger->debug("Creating TuiScreen of type {}", type);
        #endif

        switch (type) {
            case ScreenType::LOADING:
                return Pointers::shared<LoadingScreen>(game, host, localization);
            case ScreenType::TITLE:
                return Pointers::shared<TitleScreen>(game, host, localization, profile);
            case ScreenType::MAIN_MENU:
                return Pointers::shared<MainMenuScreen>(game, host, localization, loggerFactory);
            case ScreenType::SINGLEPLAYER_LOBBY_SELECT:
                return Pointers::shared<SingleplayerLobbySelectScreen>(game, host, localization);
            case ScreenType::SINGLEPLAYER_CUSTOM:
                return Pointers::shared<SingleplayerCustomScreen>(game, host, localization);
            case ScreenType::SINGLEPLAYER_CAMPAIGN_SELECT:
                return Pointers::shared<SingleplayerCampaignSelectScreen>(game, host, localization);
            case ScreenType::MULTIPLAYER_LOBBY_SELECT:
                return Pointers::shared<MultiplayerLobbySelectScreen>(game, host, localization);
            case ScreenType::MULTIPLAYER_CUSTOM:
                return Pointers::shared<MultiplayerCustomScreen>(game, host, localization);
            case ScreenType::SINGLEPLAYER_GAME_LOBBY:
                return Pointers::shared<SingleplayerGameLobbyScreen>(game, host, localization);
            case ScreenType::MULTIPLAYER_GAME_LOBBY:
                return Pointers::shared<MultiplayerGameLobbyScreen>(game, host, localization);
            case ScreenType::CHARACTER_SELECT:
                return Pointers::shared<CharacterSelectScreen>(game, host, localization);
            case ScreenType::CARD_SELECT:
                return Pointers::shared<CardSelectScreen>(game, host, localization);
            case ScreenType::GAMEPLAY:
                return Pointers::shared<GameplayScreen>(game, host, localization);
            case ScreenType::GAME_RESULTS:
                return Pointers::shared<GameResultsScreen>(game, host, localization);
            case ScreenType::SHOP:
                return Pointers::shared<ShopScreen>(game, host, localization);
            case ScreenType::PROFILE:
                return Pointers::shared<ProfileScreen>(game, host, localization);
            case ScreenType::OJDEX:
                return Pointers::shared<OJDexScreen>(game, host, localization);
            case ScreenType::GUIDE:
                return Pointers::shared<GuideScreen>(game, host, localization);
            case ScreenType::CONFIG:
                return Pointers::shared<ConfigScreen>(game, host, localization);
            case ScreenType::CREDITS:
                return Pointers::shared<CreditsScreen>(game, host, localization);
            case ScreenType::PAUSE:
                return Pointers::shared<PauseScreen>(game, host, localization);
            case ScreenType::EXIT:
            case ScreenType::WIKI:
                logger->error("Attempted to create a TuiScreen of type {} which is not a valid screen type.", type);
                return nullptr;
        }
        Ops::unreachable();
    }
};

END_MODULE_NAMESPACE();
