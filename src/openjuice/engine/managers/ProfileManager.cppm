/**
 * @file ProfileManager.cppm
 * @module openjuice.engine.managers.ProfileManager
 * @brief Implementation of the ProfileManager class.
 *
 * This file contains the implementation of the ProfileManager class, which manages the current profile for the application.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.managers.ProfileManager;

import std;
import stdx;

import openjuice.engine.util.Constants;

import tomlpp;

using std::fs::FileSystemException;
using std::fs::Path;
using std::io::IOException;
using std::io::IOS;
using std::io::IOState;
using std::io::OutputFileStream;
using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fs = std::fs;

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
        String playerName; ///< The player name
        u64 totalPlayTime; ///< The total amount of time played in the save slot, in seconds
    public:
        PROPERTY(String, PlayerName, playerName);
        PROPERTY(u64, TotalPlayTime, totalPlayTime)

        /**
         * @brief Constructor to initialise a ProfileData object.
         *
         * @param playerName The name of the player associated with a PlayerData.
         * @param totalPlayTime The total amount of time played in the save slot in seconds.
         */
        constexpr ProfileData(StringView playerName = "", u64 totalPlayTime = 0):
            playerName{String(playerName)}, totalPlayTime{totalPlayTime} {}

        /**
         * @brief Default destructor for ProfileData
         */
        ~ProfileData() = default;
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
            fs::create_directories(USERDATA_DIR);
            loadProfile();
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
     * @return True if successful, false otherwise
     */
    bool deserialise(const TomlTable& table) noexcept {
        try {
            if (NodeView<const TomlNode> playerNameNode = table["playerName"]; playerNameNode) {
                if (Optional<String> playerNameValue = playerNameNode.value<String>()) {
                    currentProfile.setPlayerName(*playerNameValue);
                } else {
                    LOGGER->warn("playerName field is not a string");
                    return false;
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
                    return false;
                }
            } else {
                LOGGER->debug("totalPlayTime field not found, using default");
                currentProfile.setTotalPlayTime(0);
            }

            return true;
        } catch (const Exception& e) {
            LOGGER->error("Exception during deserialization: {}", e.what());
            return false;
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
     * @return True if successfully loaded, false otherwise.
     */
    bool loadProfile() noexcept {
        if (!fs::exists(PATH_SAVEFILE)) {
            LOGGER->info("Save file not found, creating new profile");
            return saveProfile();
        }

        try {
            TomlTable data = tomlpp::parse_file(PATH_SAVEFILE);
            
            if (!deserialise(data)) {
                LOGGER->error("Failed to deserialize profile data");
                return false;
            }

            profileLoaded = true;
            LOGGER->info("Profile loaded successfully for {}", currentProfile.getPlayerName());
            return true;
        } catch (const TomlParseException& e) {
            LOGGER->error("Failed to parse TOML file: {}", e.what());
            return false;
        } catch (const Exception& e) {
            LOGGER->error("Error loading profile: {}", e.what());
            return false;
        }
    }

    /**
     * @brief Save profile data to file.
     * @return True if successfully saved, false otherwise.
     */
    bool saveProfile() noexcept {
        try {
            TomlTable data;
            data.insert("playerName", currentProfile.getPlayerName());
            data.insert("totalPlayTime", static_cast<i64>(currentProfile.getTotalPlayTime()));

            OutputFileStream file{Path(PATH_SAVEFILE)};
            file.exceptions(IOState::STREAM_ERROR | IOState::IO_OPERATION_FAIL);

            file << data;
            file.close();

            LOGGER->info("Profile saved successfully for {}", currentProfile.getPlayerName());
            return true;
        } catch (const IOException& e) {
            if (!fs::exists(PATH_SAVEFILE)) {
                LOGGER->warn("Failed to save profile, file/directory does not exist: {}", e.what());
            } else {
                LOGGER->warn("Failed to save profile, write operation failed: {}", e.what());
            }
            return false;
        } catch (const Exception& e) {
            LOGGER->warn("Error saving profile: {}", e.what());
            return false;
        }
    }

    /**
     * @brief Reset profile data (start new game)
     * @return True if successfully reset, false otherwise.
     */
    bool resetProfile() noexcept {
        LOGGER->info("Attempting to reset profile for {}", currentProfile.getPlayerName());
        return saveProfile();
    }
};

END_MODULE_NAMESPACE();
