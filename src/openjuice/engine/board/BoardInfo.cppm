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
 * @class BoardInfo
 * @brief Struct aggregating key information about boards.
 * 
 * The BoardInfo record aggregates key information about boards, such as ID, name, dimensions, and home panels.
 */
export class BoardInfo final {
public:
    static constexpr u8 MAX_PLAYERS = 4; ///< Maximum number of players.
    using HomePanels = Array<Pair<u8, u8>, MAX_PLAYERS>;
private:
    const String name; ///< The name of the board.
    const u32 id; ///< The ID of the board. 0 denotes an error.
    const u8 width; ///< The width of the board.
    const u8 height; ///< The height of the board.
    const HomePanels homePanels; ///< The home panels for each player.
public:
    GETTER(String, Name, name);
    GETTER(u32, Id, id);
    GETTER(u8, Width, width);
    GETTER(u8, Height, height);
    GETTER(HomePanels, HomePanels, homePanels);

    /**
     * @brief Constructor with parameters
     * 
     * @param name The board name
     * @param id The board ID
     * @param width The board width
     * @param height The board height
     * @param panels The home panels for each player
     */
    constexpr BoardInfo(StringView name, u32 id, u8 width, u8 height, HomePanels& panels):
        name{String(name)}, id{id}, width{width}, 
        height{height}, homePanels{panels} {}

    /**
     * @brief Destructor
     */
    constexpr ~BoardInfo() noexcept = default;
};

END_MODULE_NAMESPACE();
