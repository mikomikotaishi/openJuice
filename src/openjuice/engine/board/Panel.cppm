/**
 * @file Panel.cppm
 * @module openjuice.engine.board:Panel
 * @brief Implementation of the Panel class.
 *
 * This file contains the implementation of the Panel class, which represents a panel on the game board.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board:Panel;

import stdx;

import openjuice.engine.util;

using stdx::collections::BitSet;
using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::mem::SharedPointer;
using stdx::mem::WeakPointer;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class Panel
 * @brief Class representing a panel on the game board.
 *
 * The Panel class represents a panel on the game board with attributes such as type, neighbors, and entry/exit directions.
 */
export class [[nodiscard]] Panel {
public:
    using Neighbors = Array<WeakPointer<Panel>, 4>;
    using Adjacents = BitSet<4>;

    /**
     * @enum Direction
     * @brief Enumeration for directions.
     *
     * The Direction enumeration defines the four cardinal directions.
     */
    enum class Direction: u8 {
        UP = 0, ///< Up direction
        LEFT = 1, ///< Left direction
        RIGHT = 2, ///< Right direction
        DOWN = 3, ///< Down direction
    };

    /**
     * @enum Of
     * @brief Enumeration for panel types.
     *
     * The Of enumeration defines the types of panels in the game.
     */
    enum class Of: u8 {
        HOME, ///< 0 - Home panel - level up on achieving norma and heal 1 HP
        NEUTRAL, ///< 1 - Nothing happens
        BONUS, ///< 2 - Roll to gain star amount multiplied by level
        BONUS_2, ///< 3 - Roll twice the dice for Bonus tile
        DROP, ///< 4 - Roll to lose star amount multiplied by level
        DROP_2, ///< 5 - Roll twice the dice for Drop tile
        DRAW, ///< 6 - Draw a card from the top of the deck
        DRAW_2, ///< 7 - Draw 2 cards from the top of the deck
        WARP, ///< 8 - Teleport to any Warp or Warp Move panel
        WARP_MOVE, ///< 9 - Teleport to any Warp or Warp Move panel, then roll/move again
        WARP_MOVE_2, ///< 10 - Roll twice the dice for Warp Move panel
        ENCOUNTER, ///< 11 - Face a random enemy unit in combat
        ENCOUNTER_2, ///< 12 - Trigger Encounter panel, gain twice the wins upon KOing the unit
        BOSS_ENCOUNTER, ///< 13 - Face this board's boss in combat
        MOVE, ///< 14 - Roll and move again
        MOVE_2, ///< 15 - Roll twice the dice for Move panel
        ICE, ///< 16 - Slide to the next panel without deducting from the move roll
        GOO, ///< 17 - Deduct 2 points from the move roll instead of 1
        HEAL, ///< 18 - Heal 1 HP
        HEAL_2, ///< 19 - Heal 2 HP
        DAMAGE, ///< 20 - Take 1 damage
        DAMAGE_2, ///< 21 - Take 2 damage
        MINIGAME, ///< 22 - UNUSED, Play a random minigame
        BOSS_HOME, ///< 23 - UNUSED, Spawn panel for Boss, face this board's boss in combat
        DECORATION, ///< 24 - UNUSED, gain 1 decoration
        PLAYER_ENCOUNTER, ///< 25 - UNUSED, face a random player in combat
        RANDOM, ///< 26 - Causes either a positive or negative effect of any normal panel
    };
private:
    Neighbors neighbors; ///< The neighboring panels.
    Adjacents enters; ///< The directions from which the panel can be entered.
    Adjacents exits; ///< The directions from which the panel can be exited.
    u16 id; ///< The ID of the panel.
    Of type; ///< The type of the panel.
    Of alternativeType = Of::NEUTRAL; ///< The alternative type of the panel.
public:
    /**
     * @brief Constructor to initialize a Panel object.
     * @param id The ID of the panel.
     * @param type The type of the panel.
     * @param enters The directions from which the panel can be entered.
     * @param exits The directions from which the panel can be exited.
     * @param alternativeType The alternative type of the panel (if any).
     */
    Panel(u16 id, Of type, Of alternativeType, const Adjacents& enters, const Adjacents& exits):
        neighbors{{}}, enters{enters}, exits{exits}, id{id}, type{type}, alternativeType{alternativeType} {}

    [[nodiscard]]
    u16 getId() const noexcept {
        return id;
    }

    [[nodiscard]]
    Of getType() const noexcept {
        return type;
    }

    [[nodiscard]]
    Of getAlternativeType() const noexcept {
        return alternativeType;
    }

    void setType(Of t) noexcept {
        type = t;
    }

    void setAlternativeType(Of t) noexcept {
        alternativeType = t;
    }

    [[nodiscard]]
    Adjacents getEnters() const noexcept {
        return enters;
    }

    [[nodiscard]]
    Adjacents getExits() const noexcept {
        return exits;
    }

    [[nodiscard]]
    const Neighbors& getNeighbors() const noexcept {
        return neighbors;
    }

    /**
     * @brief Set the neighbor of the panel in a specific direction.
     * @param direction The direction of the neighbor.
     * @param neighbor The neighboring panel.
     */
    void setNeighbor(Direction direction, const SharedPointer<Panel>& neighbor) RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        neighbors.at(Ops::to_underlying(direction)) = neighbor;
        #else
        neighbors[Ops::to_underlying(direction)] = neighbor;
        #endif
    }

    /**
     * @brief Get the neighbor of the panel in a specific direction.
     * @param direction The direction of the neighbor.
     * @return The neighboring panel.
     */
    [[nodiscard]]
    SharedPointer<Panel> getNeighbor(Direction direction) const RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        return neighbors.at(Ops::to_underlying(direction)).lock();
        #else
        return neighbors[Ops::to_underlying(direction)].lock();
        #endif
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::Panel;

template <>
struct Formatter<Panel::Direction> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(Panel::Direction dir, FormatContext& ctx) {
        StringView name;
        switch (dir) {
            case Panel::Direction::UP:
                name = "Up";
                break;
            case Panel::Direction::LEFT:
                name = "Left";
                break;
            case Panel::Direction::RIGHT:
                name = "Right";
                break;
            case Panel::Direction::DOWN:
                name = "Down";
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<Panel::Of> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(Panel::Of type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case Panel::Of::HOME:
                name = "Home";
                break;
            case Panel::Of::NEUTRAL:
                name = "Neutral";
                break;
            case Panel::Of::BONUS:
                name = "Bonus";
                break;
            case Panel::Of::BONUS_2:
                name = "Double Bonus";
                break;
            case Panel::Of::DROP:
                name = "Drop";
                break;
            case Panel::Of::DROP_2:
                name = "Double Drop";
                break;
            case Panel::Of::DRAW:
                name = "Draw";
                break;
            case Panel::Of::DRAW_2:
                name = "Double Draw";
                break;
            case Panel::Of::WARP:
                name = "Warp";
                break;
            case Panel::Of::WARP_MOVE:
                name = "Warp Move";
                break;
            case Panel::Of::WARP_MOVE_2:
                name = "Double Warp Move";
                break;
            case Panel::Of::ENCOUNTER:
                name = "Encounter";
                break;
            case Panel::Of::ENCOUNTER_2:
                name = "Double Encounter";
                break;
            case Panel::Of::BOSS_ENCOUNTER:
                name = "Boss Encounter";
                break;
            case Panel::Of::MOVE:
                name = "Move";
                break;
            case Panel::Of::MOVE_2:
                name = "Double Move";
                break;
            case Panel::Of::ICE:
                name = "Ice";
                break;
            case Panel::Of::GOO:
                name = "Goo";
                break;
            case Panel::Of::HEAL:
                name = "Heal";
                break;
            case Panel::Of::HEAL_2:
                name = "Double Heal";
                break;
            case Panel::Of::DAMAGE:
                name = "Damage";
                break;
            case Panel::Of::DAMAGE_2:
                name = "Double Damage";
                break;
            case Panel::Of::MINIGAME:
                name = "Minigame";
                break;
            case Panel::Of::BOSS_HOME:
                name = "Boss Home";
                break;
            case Panel::Of::DECORATION:
                name = "Decoration";
                break;
            case Panel::Of::PLAYER_ENCOUNTER:
                name = "Player Encounter";
                break;
            case Panel::Of::RANDOM:
                name = "Random";
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALIZE_FORMATTER(Panel::Direction);
SPECIALIZE_FORMATTER(Panel::Of);
