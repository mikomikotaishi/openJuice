/**
 * @file PanelType.cppm
 * @module openjuice.engine.board.Panel:PanelType
 * @brief Definition of the PanelType enum class.
 *
 * This file contains the definition of the PanelType enum class, which represents panel types.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.board.Panel:PanelType;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @enum PanelType
 * @brief Enumeration for panel types.
 *
 * The PanelType enumeration defines the types of panels in the game.
 */
export enum class PanelType: u8 {
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
    PLAYER_ENCOUNTER // 25 - UNUSED, face a random player in combat
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::PanelType;

template <>
struct Formatter<PanelType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(PanelType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case PanelType::HOME:
                name = "Home";
                break;
            case PanelType::NEUTRAL:
                name = "Neutral";
                break;
            case PanelType::BONUS:
                name = "Bonus";
                break;
            case PanelType::BONUS_2:
                name = "Double Bonus";
                break;
            case PanelType::DROP:
                name = "Drop";
                break;
            case PanelType::DROP_2:
                name = "Double Drop";
                break;
            case PanelType::DRAW:
                name = "Draw";
                break;
            case PanelType::DRAW_2:
                name = "Double Draw";
                break;
            case PanelType::WARP:
                name = "Warp";
                break;
            case PanelType::WARP_MOVE:
                name = "Warp Move";
                break;
            case PanelType::WARP_MOVE_2:
                name = "Double Warp Move";
                break;
            case PanelType::ENCOUNTER:
                name = "Encounter";
                break;
            case PanelType::ENCOUNTER_2:
                name = "Double Encounter";
                break;
            case PanelType::BOSS_ENCOUNTER:
                name = "Boss Encounter";
                break;
            case PanelType::MOVE:
                name = "Move";
                break;
            case PanelType::MOVE_2:
                name = "Double Move";
                break;
            case PanelType::ICE:
                name = "Ice";
                break;
            case PanelType::GOO:
                name = "Goo";
                break;
            case PanelType::HEAL:
                name = "Heal";
                break;
            case PanelType::HEAL_2:
                name = "Double Heal";
                break;
            case PanelType::DAMAGE:
                name = "Damage";
                break;
            case PanelType::DAMAGE_2:
                name = "Double Damage";
                break;
            case PanelType::MINIGAME:
                name = "Minigame";
                break;
            case PanelType::BOSS_HOME:
                name = "Boss Home";
                break;
            case PanelType::DECORATION:
                name = "Decoration";
                break;
            case PanelType::PLAYER_ENCOUNTER:
                name = "Player Encounter";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(PanelType);
