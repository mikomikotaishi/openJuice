/**
 * @file AppConfiguration.cppm
 * @module openjuice.engine:AppConfiguration
 * @brief The configuration class
 * 
 * This file contains the configuration class which acts as the
 * centralized module for dependency injection.
 */

module;

#include "Macros.hpp"

export module openjuice:AppConfiguration;

import stdx;

import openjuice.engine;
import openjuice.ui;

using stdx::inject::Binder;
using stdx::inject::Configuration;
using stdx::inject::Named;
using stdx::mem::SharedPointer;
using stdx::meta::reflect::Class;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::Engine;
using openjuice::engine::board::BoardLibrary;
using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::engine::net::DiscordService;
using openjuice::engine::save::ProfileManager;
using openjuice::engine::settings::SettingsService;
using openjuice::ui::UserInterface;

BEGIN_MODULE_NAMESPACE(openjuice);

/**
 * @class AppConfiguration
 * @brief The configuration class, acting as the centralized module for dependency injection.
 * @extends Configuration
 */
export class AppConfiguration final: public Configuration {
private:
    SharedPointer<LoggerFactory> logging; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The injected logger for the configuration class.
public:
    /**
     * @brief Constructs a new AppConfiguration object
     * @param logging The injected logging factory.
     * @param logger The injected logger.
     */
    AppConfiguration(SharedPointer<LoggerFactory> logging, SharedPointer<Logger> logger):
        logging{Ops::move(logging)},
        logger{Ops::move(logger)} {
        #ifndef NDEBUG
        this->logger->debug("Created AppConfiguration!");
        #endif
    }

    /**
     * @brief Registers the dependencies for the injector.
     * @param binder The binder (mappings between abstraction and implementation).
     */
    void configure(Binder& binder) override {
        #ifndef NDEBUG
        logger->debug("Registering injector dependencies...");
        #endif

        binder.bind<SharedPointer<LoggerFactory>>().to_instance(logging);

        auto bindLoggerFor = [&binder, this]<typename T> -> void {
            binder.bind<SharedPointer<Logger>>()
                .annotated_with(Named(*Class<T>().name()))
                .to_provider([this] -> SharedPointer<Logger> { return logging->of<T>(); });
        };

        bindLoggerFor.template operator()<SettingsService>();
        bindLoggerFor.template operator()<LocalizationService>();
        bindLoggerFor.template operator()<ProfileManager>();
        bindLoggerFor.template operator()<BoardLibrary>();
        bindLoggerFor.template operator()<DiscordService>();
        bindLoggerFor.template operator()<Game>();
        bindLoggerFor.template operator()<Engine>();
        bindLoggerFor.template operator()<UserInterface>();

        binder.add_binding<SettingsService>()
            .add_binding<LocalizationService>()
            .add_binding<ProfileManager>()
            .add_binding<BoardLibrary>()
            .add_binding<DiscordService>()
            .add_binding<Game>()
            .add_binding<Engine>();

        #ifndef NDEBUG
        logger->debug("Injector dependency registration complete!");
        #endif
    }
};

END_MODULE_NAMESPACE();
