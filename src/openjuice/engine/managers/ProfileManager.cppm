/**
 * @file ProfileManager.cppm
 * @module openjuice.engine.managers:ProfileManager
 * @brief Implementation of the ProfileManager class.
 *
 * This file contains the implementation of the ProfileManager class, which manages the current profile for the application.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.managers:ProfileManager;

import std;
import stdx;

import openjuice.engine.util;

import tomlpp;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::fs::FileSystemException;
using std::fs::Path;
using std::io::IOException;
using std::io::IOS;
using std::io::IOState;
using std::io::OutputFileStream;
using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::util::Constants;

using tomlpp::NodeView;
using tomlpp::TomlNode;
using tomlpp::TomlParseException;
using tomlpp::TomlTable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @class ProfileManager
 * @brief Class to manage global settings.
 *
 * The ProfileManager class is a singleton class that manages profile information for the application.
 */
export class ProfileManager {
public:
    static constexpr StringView USERDATA_DIR = Constants::USERDATA_DIR; ///< The user data directory path.
    static constexpr StringView PATH_SAVEFILE = Constants::PATH_SAVEFILE; ///< The save file path.

    /**
     * @class ProfileData
     * @brief Record to store profile data across the game.
     */
    class ProfileData final {
    private:
        String playerName = ""; ///< The player name
        u64 totalPlayTime = 0; ///< The total amount of time played in the save slot, in seconds
    public:
        PROPERTY(String, PlayerName, playerName);
        PROPERTY(u64, TotalPlayTime, totalPlayTime)

        /**
         * @brief Default constructor for ProfileData.
         */
        constexpr ProfileData() = default;

        /**
         * @brief Constructor to initialise a ProfileData object.
         *
         * @param playerName The name of the player associated with a PlayerData.
         * @param totalPlayTime The total amount of time played in the save slot in seconds.
         */
        constexpr ProfileData(StringView playerName, u64 totalPlayTime):
            playerName{String(playerName)}, totalPlayTime{totalPlayTime} {}

        /**
         * @brief Default destructor for ProfileData
         */
        ~ProfileData() = default;
    };

    /**
     * @enum Error
     * @brief Enumeration of errors occuring in ProfileManager operations
     */
    enum class Error: u8 {
        DESERIALISATION_FAILED, ///< Deserialisation of profile data failed
        CORRUPTED_PROFILE_TOML, ///< The TOML file storing the profile is corrupted or has invalid data
        PROFILE_LOAD_FAILED, ///< Loading profile data failed
        PROFILE_SAVE_LOCATION_INVALID, ///< The profile save location is invalid
        PROFILE_SAVE_WRITE_FAILED, ///< Writing profile data to file failed
        PROFILE_SAVE_FAILED, ///< Saving profile data failed
    };
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("ProfileManager"); ///< The logger instance.

    ProfileData currentProfile; ///< The information of the current save file.
    bool profileLoaded = false; ///< Whether the profile has been loaded by the game yet.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    ProfileManager() {
        try {
            std::fs::create_directories(USERDATA_DIR);
            if (Expected<void, Error> result = loadProfile(); !result) {
                LOGGER->warn("Failed to load profile during initialisation");
            }
        } catch (const FileSystemException& e) {
            LOGGER->warn("Failed to create directory {}: {}", USERDATA_DIR, e.what());
        }
    }

    /**
     * @brief Private destructor to prevent destruction.
     */
    ~ProfileManager() = default;

    /**
     * @brief Deserialises a TOML into the ProfileData instance.
     * 
     * @param table The TOML table to deserialize from
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> deserialise(const TomlTable& table) noexcept {
        try {
            if (NodeView<const TomlNode> playerNameNode = table["playerName"]; playerNameNode) {
                if (Optional<String> playerNameValue = playerNameNode.value<String>()) {
                    currentProfile.setPlayerName(*playerNameValue);
                } else {
                    LOGGER->warn("playerName field is not a string");
                    return Unexpected(Error::DESERIALISATION_FAILED);
                }
            } else {
                LOGGER->debug("playerName field not found, using default");
                currentProfile.setPlayerName("");
            }

            if (NodeView<const TomlNode> playTimeNode = table["totalPlayTime"]; playTimeNode) {
                if (Optional<i64> playTimeValue = playTimeNode.value<i64>()) {
                    currentProfile.setTotalPlayTime(static_cast<u64>(*playTimeValue));
                } else {
                    LOGGER->warn("totalPlayTime field is not a valid integer");
                    return Unexpected(Error::DESERIALISATION_FAILED);
                }
            } else {
                LOGGER->debug("totalPlayTime field not found, using default");
                currentProfile.setTotalPlayTime(0);
            }

            return {};
        } catch (const Exception& e) {
            LOGGER->error("Exception during deserialisation: {}", e.what());
            return Unexpected(Error::DESERIALISATION_FAILED);
        }
    }
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    ProfileManager(const ProfileManager&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    ProfileManager& operator=(const ProfileManager&) = delete;

    /**
     * @brief Get the singleton instance of ProfileManager.
     * @return The singleton instance.
     */
    [[nodiscard]]
    static ProfileManager& getInstance() {
        static ProfileManager instance;
        return instance;
    }

    /**
     * @brief Load profile data from file.
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> loadProfile() noexcept {
        if (!std::fs::exists(PATH_SAVEFILE)) {
            LOGGER->info("Save file not found, creating new profile");
            return saveProfile();
        }

        try {
            TomlTable data = tomlpp::parse_file(PATH_SAVEFILE);
            
            if (!deserialise(data).has_value()) {
                LOGGER->error("Failed to deserialise profile data");
                return Unexpected(Error::DESERIALISATION_FAILED);
            }

            profileLoaded = true;
            LOGGER->info("Profile loaded successfully for {}", currentProfile.getPlayerName());
            return {};
        } catch (const TomlParseException& e) {
            LOGGER->error("Failed to parse TOML file: {}", e.what());
            return Unexpected(Error::CORRUPTED_PROFILE_TOML);
        } catch (const Exception& e) {
            LOGGER->error("Error loading profile: {}", e.what());
            return Unexpected(Error::PROFILE_LOAD_FAILED);
        }
    }

    /**
     * @brief Save profile data to file.
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> saveProfile() noexcept {
        try {
            TomlTable data;
            data.insert("playerName", currentProfile.getPlayerName());
            data.insert("totalPlayTime", static_cast<i64>(currentProfile.getTotalPlayTime()));

            OutputFileStream file{Path(PATH_SAVEFILE)};
            file.exceptions(IOState::STREAM_ERROR | IOState::IO_OPERATION_FAIL);

            file << data;
            file.close();

            LOGGER->info("Profile saved successfully for {}", currentProfile.getPlayerName());
            return {};
        } catch (const IOException& e) {
            if (!std::fs::exists(PATH_SAVEFILE)) {
                LOGGER->warn("Failed to save profile, file/directory does not exist: {}", e.what());
                return Unexpected(Error::PROFILE_SAVE_LOCATION_INVALID);
            } else {
                LOGGER->warn("Failed to save profile, write operation failed: {}", e.what());
                return Unexpected(Error::PROFILE_SAVE_WRITE_FAILED);
            }
        } catch (const Exception& e) {
            LOGGER->warn("Error saving profile: {}", e.what());
            return Unexpected(Error::PROFILE_SAVE_FAILED);
        }
    }

    /**
     * @brief Reset profile data (start new game)
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> resetProfile() noexcept {
        LOGGER->info("Attempting to reset profile for {}", currentProfile.getPlayerName());
        return saveProfile();
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::managers::ProfileManager;

template <>
struct Formatter<ProfileManager::Error> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(ProfileManager::Error err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case ProfileManager::Error::DESERIALISATION_FAILED:
                name = "Deserialisation failed"; 
                break;
            case ProfileManager::Error::CORRUPTED_PROFILE_TOML:
                name = "Corrupted profile TOML"; 
                break;
            case ProfileManager::Error::PROFILE_LOAD_FAILED:
                name = "Profile load failed"; 
                break;
            case ProfileManager::Error::PROFILE_SAVE_LOCATION_INVALID:
                name = "Profile save location invalid"; 
                break;
            case ProfileManager::Error::PROFILE_SAVE_WRITE_FAILED:
                name = "Profile save write failed"; 
                break;
            case ProfileManager::Error::PROFILE_SAVE_FAILED:
                name = "Profile save failed"; 
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(ProfileManager::Error);
