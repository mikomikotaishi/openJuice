/**
 * @file DiscordService.cppm
 * @module openjuice.engine.net:DiscordService
 * @brief Implementation of the DiscordService class.
 *
 * This file contains the implementation of the DiscordService class, which manages interactions with Discord for the application.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.net:DiscordService;

import stdx;

import discordpp;

using stdx::inject::Singleton;
using stdx::inject::Inject;
using stdx::inject::Named;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::meta::reflect::Class;
using stdx::sync::Atomic;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::util::logging::Logger;

using discordpp::Activity;
using discordpp::ActivityAssets;
using discordpp::ActivityTimestamps;
using discordpp::ActivityTypes;
using discordpp::Client;
using discordpp::ClientResult;

BEGIN_MODULE_NAMESPACE(openjuice::engine::net);

/**
 * @class DiscordService
 * @brief Service class to manage Discord Rich Presence integration for the engine.
 * 
 * Owned by Engine, handles all Discord Partner SDK interactions.
 */
export class [[=Singleton]] DiscordService final {
public:
    static constexpr u64 APPLICATION_ID = 1374097529788039318; ///< Application ID
    static constexpr StringView APPLICATION_NAME = "openJuice"; ///< The name of the application on Discord
    static constexpr StringView LARGE_IMAGE_KEY = ""; ///< The large image key on Discord
    static constexpr StringView SMALL_IMAGE_KEY = ""; ///< The small image key on Discord

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
    SharedPointer<Logger> logger; ///< The logger instance.

    mutable Mutex discordMutex; ///< Mutex for thread-safe operations on Discord
    String currentActivity; ///< Current activity
    UniquePointer<Client> client; ///< Discord SDK client
    u64 sessionStartTime; ///< Session start timestamp
    ActivityType currentActivityType; ///< Current activity type
    Atomic<bool> connected = false; ///< Whether the client has an authorized connection to Discord.
    bool initialized = false; ///< Whether init() has created the client. Presence updates require only this.

    /**
     * @brief Create base activity with common properties
     * @return Activity object with base configuration
     */
    Activity createBaseActivity() const {
        Activity activity;
        activity.SetType(ActivityTypes::Playing);

        if (!LARGE_IMAGE_KEY.empty() || !SMALL_IMAGE_KEY.empty()) {
            ActivityAssets assets;

            if (!LARGE_IMAGE_KEY.empty()) {
                assets.SetLargeImage(String(LARGE_IMAGE_KEY));
                assets.SetLargeText(String(APPLICATION_NAME));
            }

            if (!SMALL_IMAGE_KEY.empty()) {
                assets.SetSmallImage(String(SMALL_IMAGE_KEY));
            }

            activity.SetAssets(assets);
        }

        ActivityTimestamps timestamps;
        timestamps.SetStart(sessionStartTime);
        activity.SetTimestamps(timestamps);

        return activity;
    }

    /**
     * @brief Push an activity to Discord.
     * @param activity The activity to publish
     * @param description What the activity represents, for the log
     *
     * Called with discordMutex held. The completion runs later, out of runCallbacks(), by which
     * point the lock is long released: it only logs, so it takes no lock of its own.
     */
    void updateActivity(const Activity& activity, StringView description) {
        if (client == nullptr) {
            logger->warn("Discord client not initialized, skipping activity update: {}.", description);
            return;
        }

        // The description is copied rather than captured as a view: the completion is asynchronous
        // and outlives whatever the caller passed in.
        client->UpdateRichPresence(activity, [this, description = String(description)](const ClientResult& result) -> void {
            if (result.Successful()) {
                #ifndef NDEBUG
                logger->debug("Discord activity updated: {}.", description);
                #endif
            } else {
                logger->warn("Failed to update Discord activity: {}.", description);
            }
        });
    }

    /**
     * @brief Build and publish an activity, recording it as the current one.
     * @param type The kind of activity being set
     * @param state The line Discord shows as the state
     * @param details The line Discord shows above the state
     */
    void setActivity(ActivityType type, StringView state, StringView details) {
        ScopedLock<Mutex> lock(discordMutex);

        Activity activity = createBaseActivity();
        activity.SetState(String(state));
        activity.SetDetails(String(details));

        updateActivity(activity, state);

        currentActivity = String(state);
        currentActivityType = type;
    }
public:
    /**
     * @brief Constructor of the DiscordService
     * @param logger The injected logger.
     */
    [[=Inject]]
    explicit DiscordService([[=Named(*Class<DiscordService>().name())]] SharedPointer<Logger> logger):
        logger{Ops::move(logger)},
        sessionStartTime{static_cast<u64>(System::current_time_millis())},
        currentActivityType{ActivityType::IN_MENU} {}

    /**
     * @brief Destructor of the DiscordService
     *
     * Clears the presence explicitly: without this Discord keeps displaying the last activity
     * until it notices the process is gone.
     */
    ~DiscordService() {
        ScopedLock<Mutex> lock(discordMutex);

        if (client == nullptr) {
            return;
        }

        client->ClearRichPresence();
        discordpp::RunCallbacks(); // Flush the clear before the client is torn down.
    }
        
    /**
     * @brief Initialize Discord integration
     * @return True if successful
     *
     * Deliberately does not call Client::Connect. Rich presence is written straight to the local
     * Discord client while unconnected, and the SDK clears the presence if the client connects, so
     * connecting would defeat the only feature in use. A connection is only needed for the social
     * features (lobbies, invites, voice), which would also need an OAuth flow.
     */
    [[nodiscard]]
    bool init() {
        ScopedLock<Mutex> lock(discordMutex);

        if (initialized) {
            logger->warn("Discord integration already initialized; ignoring repeat call.");
            return true;
        }

        try {
            client = Pointers::unique<Client>();
            client->SetApplicationId(APPLICATION_ID);
            client->SetStatusChangedCallback([this](Client::Status status, Client::Error error, i32 details) -> void {
                switch (status) {
                    case Client::Status::Ready:
                        connected = true;
                        logger->info("Discord integration ready.");
                        break;
                    case Client::Status::Connected:
                        connected = true;
                        logger->info("Discord connected.");
                        break;
                    case Client::Status::Disconnected:
                        connected = false;
                        logger->info("Discord disconnected.");
                        break;
                    case Client::Status::Connecting:
                        logger->info("Discord connecting...");
                        break;
                    case Client::Status::Reconnecting:
                        connected = false;
                        logger->info("Discord reconnecting...");
                        break;
                    case Client::Status::Disconnecting:
                        logger->info("Discord disconnecting...");
                        break;
                    case Client::Status::HttpWait:
                        logger->info("Discord waiting on a HTTP retry...");
                        break;
                }

                if (error != Client::Error::None) {
                    logger->error("Discord client error {} (detail {})!", static_cast<i32>(error), details);
                }
            });

            initialized = true;

            logger->info("Discord integration initialized!");
        } catch (const Exception& e) {
            client.reset();
            logger->error("Failed to initialize Discord: {}!", e.what());
            return false;
        }
        return true;
    }

    /**
     * @brief Dispatch any callbacks the Discord SDK has pending.
     *
     * The SDK is entirely callback-driven and does no work of its own, so this has to be called
     * regularly or nothing ever completes. Takes no lock: it dispatches this class's own callbacks,
     * which would deadlock on a lock already held here.
     */
    void runCallbacks() noexcept {
        if (!initialized) {
            return;
        }

        discordpp::RunCallbacks();
    }

    /**
     * @brief Set menu activity on Discord activity
     */
    void setMenuActivity() {
        setActivity(ActivityType::IN_MENU, "In Menu", "Browsing options");
    }

    /**
     * @brief Set in-game activity on Discord activity
     * @param details What the player is doing, shown above the state
     */
    void setGameActivity(StringView details = "In a match") {
        setActivity(ActivityType::IN_GAME, "In Game", details);
    }

    /**
     * @brief Set paused activity on Discord activity
     */
    void setPausedActivity() {
        setActivity(ActivityType::PAUSED, "Paused", "Taking a break");
    }

    /**
     * @brief Whether init() has successfully created the client.
     * @return True if the service can publish presence
     */
    [[nodiscard]]
    bool isInitialized() const noexcept {
        ScopedLock<Mutex> lock(discordMutex);
        return initialized;
    }

    /**
     * @brief Whether the client holds an authorized connection to Discord.
     * @return True if connected
     *
     * Presence does not depend on this, and stays false while only presence is in use.
     */
    [[nodiscard]]
    bool isConnected() const noexcept {
        return connected;
    }

    /**
     * @brief Get the activity currently published.
     * @return The current activity type
     */
    [[nodiscard]]
    ActivityType getCurrentActivityType() const noexcept {
        ScopedLock<Mutex> lock(discordMutex);
        return currentActivityType;
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::net::DiscordService;

namespace stdx::fmt {
    template <>
    struct Formatter<DiscordService::ActivityType> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(DiscordService::ActivityType type, FormatContext& ctx) {
            StringView name;
            switch (type) {
                case DiscordService::ActivityType::IN_MENU:
                    name = "In Menu";
                    break;
                case DiscordService::ActivityType::IN_GAME:
                    name = "In Game";
                    break;
                case DiscordService::ActivityType::PAUSED:
                    name = "Paused";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(DiscordService::ActivityType);
