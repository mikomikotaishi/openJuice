/**
 * @file Constants.cppm
 * @module openjuice.engine.util.Constants
 * @brief Definition of the Constants static class.
 *
 * This file contains the definition of the Constants static class, which provides predefined constants.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Constants;

import std;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @class Constants
 * @brief Static class containing game-related constants in a central location.
 */
export class Constants {
private:
    UTILITY_CLASS(Constants);
public:
    // Paths
    static constexpr StringView MAPS_DIR = "./maps"; ///< The maps directory path.
    static constexpr StringView PATH_DEBUGFILE = "./userdata/debug.txt"; ///< The debug file path.
    static constexpr StringView USERDATA_DIR = "./userdata"; ///< The user data directory path.
    static constexpr StringView PATH_SAVEFILE = "./userdata/savedata.toml"; ///< The save file path.
    static constexpr StringView PATH_BLACKLIST_FILE = "./blacklist/blacklist_{}.txt"; ///< The blacklist file path.
    static constexpr StringView ORANGE_JUICE_WIKI_URL = "https://100orangejuice.fandom.com"; ///< The URL for the 100% Orange Juice! wiki

    // Discord constants
    static constexpr u64 DISCORD_APPLICATION_ID = 1374097529788039318; ///< Application ID
    static constexpr StringView DISCORD_APPLICATION_NAME = "openJuice"; ///< The name of the application on Discord
    static constexpr StringView DISCORD_LARGE_IMAGE_KEY = ""; ///< The large image key on Discord
    static constexpr StringView DISCORD_SMALL_IMAGE_KEY = ""; ///< The small image key on Discord

    // Game constants
    static constexpr usize DICEROLL_HISTORY_CAPACITY = 100; ///< Maximum number of dice rolls stored.
    static constexpr u8 GAME_MAX_PLAYERS = 4; ///< Maximum number of players.
    static constexpr usize GAME_MAX_WIDTH = 20; ///< Maximum game width.
    static constexpr usize GAME_MAX_HEIGHT = 20; ///< Maximum game height.
};

END_MODULE_NAMESPACE();
