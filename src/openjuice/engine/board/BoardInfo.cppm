/**
 * @file BoardInfo.cppm
 * @module openjuice.engine.board:BoardInfo
 * @brief Definition of the BoardInfo struct.
 *
 * This file contains the definition of the BoardInfo struct, which aggregates key information about boards.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board:BoardInfo;

import stdx;

import openjuice.engine.util;

using openjuice::engine::util::Constants;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class BoardInfo
 * @brief Struct aggregating key information about boards.
 * 
 * The BoardInfo record aggregates key information about boards, such as ID, name, dimensions, and home panels.
 */
export class [[nodiscard]] BoardInfo final {
public:
    static constexpr u8 MAX_PLAYERS = Constants::GAME_MAX_PLAYERS; ///< Maximum number of players.
    using HomePanels = Array<Pair<u8, u8>, MAX_PLAYERS>;
private:
    const String name; ///< The name of the board.
    const HomePanels homePanels; ///< The home panels for each player.
    const u32 id; ///< The ID of the board. 0 denotes an error.
    const u8 width; ///< The width of the board.
    const u8 height; ///< The height of the board.
public:
    /**
     * @brief Get the name of the board
     * @return The board's name
     */
    [[nodiscard]]
    String getName() const noexcept {
        return name;
    }

    /**
     * @brief Get the ID of the board
     * @return The board's ID
     */
    [[nodiscard]]
    u32 getId() const noexcept {
        return id;
    }

    /**
     * @brief Get the width of the board
     * @return The board's width
     */
    [[nodiscard]]
    u8 getWidth() const noexcept {
        return width;
    }

    /**
     * @brief Get the height of the board
     * @return The board's height
     */
    [[nodiscard]]
    u8 getHeight() const noexcept {
        return height;
    }

    /**
     * @brief Get the home panels of the board
     * @return The home panels of the board (array of 4 coordinates)
     */
    [[nodiscard]]
    HomePanels getHomePanels() const noexcept {
        return homePanels;
    }

    /**
     * @brief Constructor with parameters
     * 
     * @param id The board ID
     * @param name The board name
     * @param width The board width
     * @param height The board height
     * @param panels The home panels for each player
     */
    constexpr BoardInfo(u32 id, StringView name, u8 width, u8 height, const HomePanels& panels):
        name{String(name)}, homePanels{panels}, id{id},
        width{width}, height{height} {}

    /**
     * @brief Destructor
     */
    constexpr ~BoardInfo() noexcept = default;
};

END_MODULE_NAMESPACE();
