/**
 * @file DiscordManager.cppm
 * @module openjuice.engine.managers:DiscordManager
 * @brief Implementation of the DiscordManager class.
 *
 * This file contains the implementation of the DiscordManager class, which manages interactions with Discord for the application.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.managers:DiscordManager;

import stdx;

import openjuice.engine.util;

import discordpp;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::util::Constants;

using discordpp::Activity;
using discordpp::ActivityAssets;
using discordpp::ActivityTimestamps;
using discordpp::Client;
using discordpp::ClientResult;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @class DiscordManager
 * @brief Manages Discord Rich Presence integration for the engine.
 * 
 * Owned by Engine, handles all Discord Partner SDK interactions.
 */
export class DiscordManager {
public:
    static constexpr u64 APPLICATION_ID = Constants::DISCORD_APPLICATION_ID; ///< Application ID
    static constexpr StringView APPLICATION_NAME = Constants::DISCORD_APPLICATION_NAME; ///< The name of the application on Discord
    static constexpr StringView LARGE_IMAGE_KEY = Constants::DISCORD_LARGE_IMAGE_KEY; ///< The large image key on Discord
    static constexpr StringView SMALL_IMAGE_KEY = Constants::DISCORD_SMALL_IMAGE_KEY; ///< The small image key on Discord

    /**
     * @enum ActivityType
     * @brief Enumeration for discord activity types.
     * 
     * The ActivityType enumeration defines the activity types that can be displayed in Discord.
     */
    enum class ActivityType: u8 {
        IN_MENU, ///< Status is on menu
        IN_GAME, ///< Status is in game
        PAUSED, ///< Status is paused
    };
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("DiscordManager"); ///< The logger instance.

    mutable Mutex discordMutex; ///< Mutex for thread-safe operations on Discord
    String currentActivity; ///< Current activity
    UniquePointer<Client> client; ///< Discord SDK client
    u64 sessionStartTime; ///< Session start timestamp
    ActivityType currentActivityType; ///< Current activity type
    bool isConnected = false; ///< Connection status
    bool isInitialised = false; ///< Initialisation status

    /**
     * @brief Create base activity with common properties
     * 
     * @return Activity object with base configuration
     */
    Activity createBaseActivity() const {
        Activity activity;
        ActivityAssets assets;

        assets.SetLargeImage(String(LARGE_IMAGE_KEY));
        assets.SetSmallImage(String(SMALL_IMAGE_KEY));
        assets.SetLargeText(String(APPLICATION_NAME));
        activity.SetAssets(assets);

        ActivityTimestamps timestamps;
        timestamps.SetStart(sessionStartTime);
        activity.SetTimestamps(timestamps);

        return activity;
    }

    void updateActivity(const Activity& activity, StringView description) {
        if (!isConnected || !client) {
            LOGGER->warn("Discord not connected, skipping activity update: {}", description);
            return;
        }

        client->UpdateRichPresence(activity, [description](const ClientResult& result) -> void {
            if (result.Successful()) {
                #ifndef NDEBUG
                LOGGER->info("Discord activity updated: {}", description);
                #endif
            } else {
                #ifndef NDEBUG
                LOGGER->info("Failed to update Discord activity: {}", description);
                #endif
            }
        });
    }
public:
    /**
     * @brief Constructor of the DiscordManager
     */
    DiscordManager():
        sessionStartTime{static_cast<u64>(System::current_time_millis())},
        currentActivityType{ActivityType::IN_MENU} {}

    /**
     * @brief Destructor of the DiscordManager
     */
    ~DiscordManager() {

    }
        
    /**
     * @brief Initialise Discord integration
     *
     * @return True if successful
     */
    [[nodiscard]]
    bool initialise() {
        ScopedLock<Mutex> lock(discordMutex);

        try {
            client = Pointers::unique<Client>();
            client->SetApplicationId(APPLICATION_ID);
            client->SetStatusChangedCallback([this](Client::Status status, Client::Error error, i32 details) -> void {
                switch (status) {
                    case Client::Status::Ready:
                        isConnected = true;
                        LOGGER->info("Discord integration ready.");
                        break;
                    case Client::Status::Disconnected:
                        isConnected = false;
                        LOGGER->info("Discord disconnected.");
                        break;
                    default:
                        LOGGER->warn("Unknown Discord connectivity status!");
                }

                if (error != Client::Error::None) {
                    LOGGER->error("Discord client error: {}", static_cast<i32>(error));
                }
            });

            isInitialised = true;

            LOGGER->info("Discord integration initialised!");
        } catch (const Exception& e) {
            LOGGER->error("Failed to initialise Discord: {}", e.what());
            return false;
        }
        return true;
    }

    /**
     * @brief Set menu activity on Discord activity
     */
    void setMenuActivity() {
        ScopedLock<Mutex> lock(discordMutex);
        if (!isConnected || !client) {
            return;
        }

        Activity activity;
        activity.SetState("In Menu");
        activity.SetDetails("Browsing options");

        ActivityTimestamps timestamps{};
        activity.SetTimestamps(timestamps);

        client->UpdateRichPresence(activity, [](const ClientResult& result) -> void {
            if (result.Successful()) {
                // do something...
            } else {
                // do something else...
            }
        });

        currentActivity = "In Menu";
        currentActivityType = ActivityType::IN_MENU;
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::managers::DiscordManager;

template <>
struct Formatter<DiscordManager::ActivityType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(DiscordManager::ActivityType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case DiscordManager::ActivityType::IN_MENU:
                name = "In Menu";
                break;
            case DiscordManager::ActivityType::IN_GAME:
                name = "In Game";
                break;
            case DiscordManager::ActivityType::PAUSED:
                name = "Paused";
                break;
            default:
                System::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(DiscordManager::ActivityType);
