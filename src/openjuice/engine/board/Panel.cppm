/**
 * @file Panel.cppm
 * @module openjuice.engine.board:Panel
 * @brief Implementation of the Panel class.
 *
 * This file contains the implementation of the Panel class, which represents a panel on the game board.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.board:Panel;

import std;

import openjuice.engine.util;

using std::collections::BitSet;
using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::mem::SharedPointer;
using std::mem::WeakPointer;

using openjuice::engine::util::Direction;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class Panel
 * @brief Class representing a panel on the game board.
 *
 * The Panel class represents a panel on the game board with attributes such as type, neighbours, and entry/exit directions.
 */
export class [[nodiscard]] Panel {
public:
    using Neighbours = Array<WeakPointer<Panel>, 4>;

    /**
     * @enum Type
     * @brief Enumeration for panel types.
     *
     * The Type enumeration defines the types of panels in the game.
     */
    enum class Type: u8 {
        HOME, // 0 - Home panel - level up on achieving norma and heal 1 HP
        NEUTRAL, // 1 - Nothing happens
        BONUS, // 2 - Roll to gain star amount multiplied by level
        BONUS_2, // 3 - Roll twice the dice for Bonus tile
        DROP, // 4 - Roll to lose star amount multiplied by level
        DROP_2, // 5 - Roll twice the dice for Drop tile
        DRAW, // 6 - Draw a card from the top of the deck
        DRAW_2, // 7 - Draw 2 cards from the top of the deck
        WARP, // 8 - Teleport to any Warp or Warp Move panel
        WARP_MOVE, // 9 - Teleport to any Warp or Warp Move panel, then roll/move again
        WARP_MOVE_2, // 10 - Roll twice the dice for Warp Move panel
        ENCOUNTER, // 11 - Face a random enemy unit in combat
        ENCOUNTER_2, // 12 - Trigger Encounter panel, gain twice the wins upon KOing the unit
        BOSS_ENCOUNTER, // 13 - Face this board's boss in combat
        MOVE, // 14 - Roll and move again
        MOVE_2, // 15 - Roll twice the dice for Move panel
        ICE, // 16 - Slide to the next panel without deducting from the move roll
        GOO, // 17 - Deduct 2 points from the move roll instead of 1
        HEAL, // 18 - Heal 1 HP
        HEAL_2, // 19 - Heal 2 HP
        DAMAGE, // 20 - Take 1 damage
        DAMAGE_2, // 21 - Take 2 damage
        MINIGAME, // 22 - UNUSED, Play a random minigame
        BOSS_HOME, // 23 - UNUSED, Spawn panel for Boss, face this board's boss in combat
        DECORATION, // 24 - UNUSED, gain 1 decoration
        PLAYER_ENCOUNTER, // 25 - UNUSED, face a random player in combat
        RANDOM, // 26 - Causes either a positive or negative effect of any normal panel
    };
private:
    Neighbours neighbours; ///< The neighbouring panels.
    BitSet<4> enters; ///< The directions from which the panel can be entered.
    BitSet<4> exits; ///< The directions from which the panel can be exited.
    u16 id; ///< The ID of the panel.
    Type type; ///< The type of the panel.
    Type alternativeType = Type::NEUTRAL; ///< The alternative type of the panel.
public:
    /**
     * @brief Constructor to initialise a Panel object.
     *
     * @param id The ID of the panel.
     * @param type The type of the panel.
     * @param enters The directions from which the panel can be entered.
     * @param exits The directions from which the panel can be exited.
     * @param alternativeType The alternative type of the panel (if any).
     */
    Panel(u16 id, Type type, Type alternativeType, const BitSet<4>& enters, const BitSet<4>& exits):
        neighbours{}, enters{enters}, exits{exits}, id{id}, type{type}, alternativeType{alternativeType} {}

    GETTER(u16, Id, id);
    PROPERTY(Type, Type, type);
    PROPERTY(Type, AlternativeType, alternativeType);
    GETTER(BitSet<4>, Enters, enters);
    GETTER(BitSet<4>, Exits, exits);
    GETTER(Neighbours, Neighbours, neighbours);

    /**
     * @brief Set the neighbour of the panel in a specific direction.
     *
     * @param direction The direction of the neighbour.
     * @param neighbour The neighbouring panel.
     */
    void setNeighbour(Direction direction, const SharedPointer<Panel>& neighbour) RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        neighbours.at(std::util::to_underlying(direction)) = neighbour;
        #else
        neighbours[std::util::to_underlying(direction)] = neighbour;
        #endif
    }

    /**
     * @brief Get the neighbour of the panel in a specific direction.
     *
     * @param direction The direction of the neighbour.
     * @return The neighbouring panel.
     */
    [[nodiscard]]
    SharedPointer<Panel> getNeighbour(Direction direction) const RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        return neighbours.at(std::util::to_underlying(direction)).lock();
        #else
        return neighbours[std::util::to_underlying(direction)].lock();
        #endif
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::Panel;

template <>
struct Formatter<Panel::Type> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Panel::Type type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case Panel::Type::HOME:
                name = "Home";
                break;
            case Panel::Type::NEUTRAL:
                name = "Neutral";
                break;
            case Panel::Type::BONUS:
                name = "Bonus";
                break;
            case Panel::Type::BONUS_2:
                name = "Double Bonus";
                break;
            case Panel::Type::DROP:
                name = "Drop";
                break;
            case Panel::Type::DROP_2:
                name = "Double Drop";
                break;
            case Panel::Type::DRAW:
                name = "Draw";
                break;
            case Panel::Type::DRAW_2:
                name = "Double Draw";
                break;
            case Panel::Type::WARP:
                name = "Warp";
                break;
            case Panel::Type::WARP_MOVE:
                name = "Warp Move";
                break;
            case Panel::Type::WARP_MOVE_2:
                name = "Double Warp Move";
                break;
            case Panel::Type::ENCOUNTER:
                name = "Encounter";
                break;
            case Panel::Type::ENCOUNTER_2:
                name = "Double Encounter";
                break;
            case Panel::Type::BOSS_ENCOUNTER:
                name = "Boss Encounter";
                break;
            case Panel::Type::MOVE:
                name = "Move";
                break;
            case Panel::Type::MOVE_2:
                name = "Double Move";
                break;
            case Panel::Type::ICE:
                name = "Ice";
                break;
            case Panel::Type::GOO:
                name = "Goo";
                break;
            case Panel::Type::HEAL:
                name = "Heal";
                break;
            case Panel::Type::HEAL_2:
                name = "Double Heal";
                break;
            case Panel::Type::DAMAGE:
                name = "Damage";
                break;
            case Panel::Type::DAMAGE_2:
                name = "Double Damage";
                break;
            case Panel::Type::MINIGAME:
                name = "Minigame";
                break;
            case Panel::Type::BOSS_HOME:
                name = "Boss Home";
                break;
            case Panel::Type::DECORATION:
                name = "Decoration";
                break;
            case Panel::Type::PLAYER_ENCOUNTER:
                name = "Player Encounter";
                break;
            case Panel::Type::RANDOM:
                name = "Random";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(Panel::Type);
