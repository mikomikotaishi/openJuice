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
export class BoardInfo {
public:
    static constexpr u8 MAX_PLAYERS = 4; ///< Maximum number of players.
    using HomePanels = Array<Pair<u8, u8>, MAX_PLAYERS>;
private:
    u32 id; ///< The ID of the board. 0 denotes an error.
    String name; ///< The name of the board.
    u8 width; ///< The width of the board.
    u8 height; ///< The height of the board.
    HomePanels homePanels; ///< The home panels for each player.
public:
    GETTER(u32, Id, id);
    GETTER(String, Name, name);
    GETTER(u8, Width, width);
    GETTER(u8, Height, height);
    GETTER(HomePanels, HomePanels, homePanels);

    /**
     * @brief Default constructor
     */
    constexpr BoardInfo() noexcept = default;

    /**
     * @brief Constructor with parameters
     * 
     * @param id The board ID
     * @param name The board name
     * @param width The board width
     * @param height The board height
     * @param panels The home panels for each player
     */
    constexpr BoardInfo(u32 id, StringView name, u8 width, u8 height, HomePanels& panels):
        id{id}, name{String(name)}, width{width}, 
        height{height}, homePanels{panels} {}

    /**
     * @brief Copy constructor
     */
    constexpr BoardInfo(const BoardInfo&) noexcept = default;

    /**
     * @brief Move constructor
     */
    constexpr BoardInfo(BoardInfo&&) noexcept = default;

    /**
     * @brief Copy assignment operator
     */
    constexpr BoardInfo& operator=(const BoardInfo&) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    constexpr BoardInfo& operator=(BoardInfo&&) noexcept = default;

    /**
     * @brief Destructor
     */
    constexpr ~BoardInfo() noexcept = default;
};

END_MODULE_NAMESPACE();
