/**
 * @file BoardInfo.cppm
 * @module openjuice.engine.board.BoardInfo
 * @brief Definition of the BoardInfo struct.
 *
 * This file contains the definition of the BoardInfo struct, which aggregates key information about boards.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board.BoardInfo;

import std;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @struct BoardInfo
 * @brief Struct aggregating key information about boards.
 * 
 * The BoardInfo struct aggregates key information about boards, such as ID, name, dimensions, and home panels.
 */
export struct BoardInfo {
    static constexpr u8 MAX_PLAYERS = 4; ///< Maximum number of players.
    u32 id; ///< The ID of the board.
    String boardName; ///< The name of the board.
    u8 boardWidth; ///< The width of the board.
    u8 boardHeight; ///< The height of the board.
    Array<Pair<u8, u8>, MAX_PLAYERS> homePanels; ///< The home panels for each player.
};

END_MODULE_NAMESPACE();
