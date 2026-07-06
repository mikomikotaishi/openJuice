/**
 * @file ProfileManager.cppm
 * @module openjuice.engine.services:ProfileManager
 * @brief Implementation of the ProfileManager class.
 *
 * This file contains the implementation of the ProfileManager class, which manages the current profile for the application.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.services:ProfileManager;

import stdx;

import openjuice.engine.util;

import marzer.toml;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::fs::FileSystemException;
using stdx::fs::Path;
using stdx::io::IOException;
using stdx::io::IOS;
using stdx::io::IOState;
using stdx::io::OutputFileStream;
using stdx::mem::SharedPointer;
using stdx::time::Seconds;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::util::Constants;

using marzer::toml::NodeView;
using marzer::toml::TomlNode;
using marzer::toml::TomlParseException;
using marzer::toml::TomlTable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::services);

/**
 * @class ProfileManager
 * @brief Service class to manage profile information.
 *
 * The ProfileManager class is a service class that manages profile information for the application.
 */
export class ProfileManager {
public:
    static constexpr StringView USERDATA_DIR = Constants::USERDATA_DIR; ///< The user data directory path.
    static constexpr StringView PATH_SAVE_FILE = Constants::PATH_SAVE_FILE; ///< The save file path.

    /**
     * @enum Error
     * @brief Enumeration of errors occuring in ProfileManager operations
     */
    enum class Error: u8 {
        DESERIALIZATION_FAILED, ///< Deserialization of profile data failed
        CORRUPTED_PROFILE_TOML, ///< The TOML file storing the profile is corrupted or has invalid data
        PROFILE_LOAD_FAILED, ///< Loading profile data failed
        PROFILE_SAVE_LOCATION_INVALID, ///< The profile save location is invalid
        PROFILE_SAVE_WRITE_FAILED, ///< Writing profile data to file failed
        PROFILE_SAVE_FAILED, ///< Saving profile data failed
    };

    /**
     * @class ProfileData
     * @brief Record to store profile data across the game.
     */
    class ProfileData final {
    private:
        String playerName = ""; ///< The player name
        u64 totalPlayTime = 0; ///< The total amount of time played in the save slot, in seconds
    public:
        /**
         * @brief Default constructor for ProfileData.
         */
        constexpr ProfileData() = default;

        /**
         * @brief Constructor to initialize a ProfileData object.
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

        [[nodiscard]]
        String getPlayerName() const noexcept {
            return playerName;
        }

        [[nodiscard]]
        u64 getTotalPlayTime() const noexcept {
            return totalPlayTime;
        }

        void setPlayerName(StringView name) noexcept {
            playerName = String(name);
        }

        void setTotalPlayTime(u64 time) noexcept {
            totalPlayTime = time;
        }

        void setTotalPlayTime(Seconds time) noexcept {
            totalPlayTime = static_cast<u64>(time.count());
        }
    };
private:
    SharedPointer<LoggerFactory> loggerFactory; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The logger instance.

    ProfileData currentProfile; ///< The information of the current save file.
    bool profileLoaded = false; ///< Whether the profile has been loaded by the game yet.

    /**
     * @brief Deserializes a TOML into the ProfileData instance.
     * 
     * @param table The TOML table to deserialize from
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> deserialize(const TomlTable& table) noexcept {
        try {
            if (NodeView<const TomlNode> playerNameNode = table["playerName"]; playerNameNode) {
                if (Optional<String> playerNameValue = playerNameNode.value<String>()) {
                    currentProfile.setPlayerName(*playerNameValue);
                } else {
                    logger->warn("playerName field is not a string");
                    return Unexpected(Error::DESERIALIZATION_FAILED);
                }
            } else {
                logger->debug("playerName field not found, using default");
                currentProfile.setPlayerName("");
            }

            if (NodeView<const TomlNode> playTimeNode = table["totalPlayTime"]; playTimeNode) {
                if (Optional<i64> playTimeValue = playTimeNode.value<i64>()) {
                    currentProfile.setTotalPlayTime(static_cast<u64>(*playTimeValue));
                } else {
                    logger->warn("totalPlayTime field is not a valid integer");
                    return Unexpected(Error::DESERIALIZATION_FAILED);
                }
            } else {
                logger->debug("totalPlayTime field not found, using default");
                currentProfile.setTotalPlayTime(0);
            }

            return {};
        } catch (const Exception& e) {
            logger->error("Exception during deserialization: {}", e.what());
            return Unexpected(Error::DESERIALIZATION_FAILED);
        }
    }
public:
    /**
     * @brief Constructs a new ProfileManager object.
     *
     * @param loggerFactory The injected logger factory.
     */
    explicit ProfileManager(SharedPointer<LoggerFactory> loggerFactory):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("ProfileManager")} {
        try {
            stdx::fs::create_directories(USERDATA_DIR);
            if (Expected<void, Error> result = loadProfile(); !result) {
                logger->warn("Failed to load profile during initialization");
            }
        } catch (const FileSystemException& e) {
            logger->warn("Failed to create directory {}: {}", USERDATA_DIR, e.what());
        }
    }

    /**
     * @brief Destroy the ProfileManager object.
     */
    ~ProfileManager() = default;

    /**
     * @brief Load profile data from file.
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> loadProfile() noexcept {
        if (!stdx::fs::exists(PATH_SAVE_FILE)) {
            logger->info("Save file not found, creating new profile");
            return saveProfile();
        }

        try {
            TomlTable data = marzer::toml::parse_file(PATH_SAVE_FILE);
            
            if (!deserialize(data).has_value()) {
                logger->error("Failed to deserialize profile data");
                return Unexpected(Error::DESERIALIZATION_FAILED);
            }

            profileLoaded = true;
            logger->info("Profile loaded successfully for {}", currentProfile.getPlayerName());
            return {};
        } catch (const TomlParseException& e) {
            logger->error("Failed to parse TOML file: {}", e.what());
            return Unexpected(Error::CORRUPTED_PROFILE_TOML);
        } catch (const Exception& e) {
            logger->error("Error loading profile: {}", e.what());
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

            OutputFileStream file{Path(PATH_SAVE_FILE)};
            file.exceptions(IOState::STREAM_ERROR | IOState::IO_OPERATION_FAIL);

            file << data;
            file.close();

            logger->info("Profile saved successfully for {}", currentProfile.getPlayerName());
            return {};
        } catch (const IOException& e) {
            if (!stdx::fs::exists(PATH_SAVE_FILE)) {
                logger->warn("Failed to save profile, file/directory does not exist: {}", e.what());
                return Unexpected(Error::PROFILE_SAVE_LOCATION_INVALID);
            } else {
                logger->warn("Failed to save profile, write operation failed: {}", e.what());
                return Unexpected(Error::PROFILE_SAVE_WRITE_FAILED);
            }
        } catch (const Exception& e) {
            logger->warn("Error saving profile: {}", e.what());
            return Unexpected(Error::PROFILE_SAVE_FAILED);
        }
    }

    /**
     * @brief Reset profile data (start new game)
     * @return Expected<void, ProfileManager::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> resetProfile() noexcept {
        logger->info("Attempting to reset profile for {}", currentProfile.getPlayerName());
        return saveProfile();
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::services::ProfileManager;

template <>
struct Formatter<ProfileManager::Error> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(ProfileManager::Error err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case ProfileManager::Error::DESERIALIZATION_FAILED:
                name = "Deserialization failed"; 
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
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(ProfileManager::Error);
