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

import openjuice.engine.managers.GlobalSettings;

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

using toml::TomlTable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @struct ProfileData
 * @brief Struct to store profile data across the game.
 */
struct ProfileData {
    String playerName; ///< The player name
    u64 totalPlayTime; ///< The total amount of time played in the save slot, in seconds
};

/**
 * @class ProfileManager
 * @brief Class to manage global settings.
 *
 * The ProfileManager class is a singleton class that manages profile information for the application.
 */
export class ProfileManager {
public:
    static constexpr StringView USERDATA_DIR = GlobalSettings::USERDATA_DIR; ///< The user data directory path.
    static constexpr StringView PATH_SAVEFILE = "./userdata/savedata.toml"; ///< The save file path.
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

        profileLoaded = true;
        LOGGER->info("Profile loaded successfully for {}", currentProfile.playerName);
        return true;
    }

    /**
     * @brief Save profile data to file.
     * @return True if successfully saved, false otherwise.
     */
    bool saveProfile() noexcept {
        try {
            TomlTable data;

            OutputFileStream file{Path(PATH_SAVEFILE)};
            file.exceptions(IOState::STREAM_ERROR | IOState::IO_OPERATION_FAIL);

            file << data;
            file.close();

            LOGGER->info("Profile saved successfully for {}", currentProfile.playerName);
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
        LOGGER->info("Attempting to reset profile for {}", currentProfile.playerName);
        return saveProfile();
    }
};

END_MODULE_NAMESPACE();
