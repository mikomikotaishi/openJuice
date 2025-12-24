/**
 * @file MushroomType.cppm
 * @module openjuice.engine.card.Card:MushroomType
 * @brief Definition of the MushroomType enum class.
 *
 * This file contains the definition of the MushroomType enum class, which represents mushroom card types.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.Card:MushroomType;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @enum BattleMushroomType
 * @brief Enumeration for battle card mushroom types.
 * 
 * The BattleMushroomType enumeration defines the types of possible mushroom cards of Battle type in the game.
 */
export enum class BattleMushroomType: u8 {
    NULL_BATTLE = 1, ///< No effect (always appears)
    ATTACK_UP, ///< Gain +1/2/3 ATK during this battle
    ATTACK_DOWN, ///< Gain -1/2/3 ATK during this battle
    DEFENCE_UP, ///< Gain +1/2/3 DEF during this battle
    DEFENCE_DOWN, ///< Gain -1/2/3 DEF during this battle
    EVADE_UP, ///< Gain +1/2/3 EVD during this battle
    EVADE_DOWN, ///< Gain -1/2/3 EVD during this battle
    HEAL, ///< Gain 1/2/3 HP
    DAMAGE, ///< Take 1/2/3 damage
    ROLL_ONE, ///< Only roll 1 in this battle
    ROLL_SIX, ///< Only roll 6 in this battle
};

/**
 * @enum BoostMushroomType
 * @brief Enumeration for boost card mushroom types.
 * 
 * The BoostMushroomType enumeration defines the types of possible mushroom cards of Boost type in the game.
 */
export enum class BoostMushroomType: u8 {
    NULL_BOOST = std::util::to_underlying(BattleMushroomType::ROLL_SIX) + 1, ///< No effect (always appears)
    MOVE_UP, ///< Gain +1/2/3 MOV on next roll
    MOVE_DOWN, ///< Gain -1/2/3 MOV on next roll
    GAIN_STARS, ///< Gain Lvl x 1/2/3/4/5 stars
    LOSE_STARS, ///< Lose Lvl x 1/2/3/4/5 stars
    HEALTH_UP, ///< Gain 1/2/3 HP
    HEALTH_DOWN, ///< Lose 1/2/3 HP
    FROSTWALKER, ///< Gain Frostwalker for 1/2/3 chapter(s)
    WARP, ///< Warp to a random panel
    CONFUSION, ///< For 1/2/3 chapters, all cards are reversed (player cannot see their cards, but other players can)
    DRAW, ///< Draw 2 cards
    DISCARD, ///< Discard a random card
    WIN, ///< Gain 1 win
};

/**
 * @enum LegendaryMushroomType
 * @brief Enumeration for legendary mushroom types.
 * 
 * The LegendaryMushroomType enumeration defines the types of possible ;egendary mushroom cards in the game.
 */
export enum class LegendaryMushroomType: u8 {
    STARS = 1, ///< Gain +Lvl stars from all sources, winner (player) steals this card upon battle KO
    WINS, ///< Gain +1 win from all sources, winner (player) steals this card upon battle KO
};

/**
 * @enum MushroomColour
 * @brief Enumeration for mushroom colours.
 * 
 * The MushroomColour enumeration defines the possible colours a mushroom card may have.
 */
export enum class MushroomColour: u8 {
    BLUE,
    BROWN,
    GREEN,
    ORANGE,
    PINK,
    PURPLE,
    RAINBOW,
    RED,
    WHITE,
    YELLOW,
};

/**
 * @enum LegendaryMushroomColour
 * @brief Enumeration for legendary mushroom colours.
 * 
 * The MushroomColour enumeration defines the possible colours a legendary mushroom card may have.
 */
export enum class LegendaryMushroomColour: u8 {
    LEGENDARY_RED,
    PHANTOM_BLUE,
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::LegendaryMushroomColour;
using openjuice::engine::card::LegendaryMushroomType;
using openjuice::engine::card::MushroomColour;

template <>
struct Formatter<BoostMushroomType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(BoostMushroomType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case BoostMushroomType::NULL_BOOST:
                name = "No Effect";
                break;
            case BoostMushroomType::MOVE_UP:
                name = "Gain Movement";
                break;
            case BoostMushroomType::MOVE_DOWN:
                name = "Lose Movement";
                break;
            case BoostMushroomType::GAIN_STARS:
                name = "Gain Stars";
                break;
            case BoostMushroomType::LOSE_STARS:
                name = "Lose Stars";
                break;
            case BoostMushroomType::HEALTH_UP:
                name = "Gain HP";
                break;
            case BoostMushroomType::HEALTH_DOWN:
                name = "Lose HP";
                break;
            case BoostMushroomType::FROSTWALKER:
                name = "Frostwalker";
                break;
            case BoostMushroomType::WARP:
                name = "Warp";
                break;
            case BoostMushroomType::CONFUSION:
                name = "Confusion";
                break;
            case BoostMushroomType::DRAW:
                name = "Draw Cards";
                break;
            case BoostMushroomType::DISCARD:
                name = "Discard Card";
                break;
            case BoostMushroomType::WIN:
                name = "Gain Win";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<BattleMushroomType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(BattleMushroomType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case BattleMushroomType::NULL_BATTLE:
                name = "No Effect";
                break;
            case BattleMushroomType::ATTACK_UP:
                name = "Gain Attack";
                break;
            case BattleMushroomType::ATTACK_DOWN:
                name = "Lose Attack";
                break;
            case BattleMushroomType::DEFENCE_UP:
                name = "Gain Defence";
                break;
            case BattleMushroomType::DEFENCE_DOWN:
                name = "Lose Defence";
                break;
            case BattleMushroomType::EVADE_UP:
                name = "Gain Evade";
                break;
            case BattleMushroomType::EVADE_DOWN:
                name = "Lose Evade";
                break;
            case BattleMushroomType::HEAL:
                name = "Heal";
                break;
            case BattleMushroomType::DAMAGE:
                name = "Damage";
                break;
            case BattleMushroomType::ROLL_ONE:
                name = "Roll 1";
                break;
            case BattleMushroomType::ROLL_SIX:
                name = "Roll 6";
                break;                
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<LegendaryMushroomColour> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(LegendaryMushroomColour type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case LegendaryMushroomColour::LEGENDARY_RED:
                name = "Legendary Red Mushroom";
                break;
            case LegendaryMushroomColour::PHANTOM_BLUE:
                name = "Phantom Blue Mushroom";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<LegendaryMushroomType> {
    static constexpr const char* parse(FormatParseContext& ctx) {
        return ctx.begin();
    }

    static FormatContext::Iterator format(LegendaryMushroomType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case LegendaryMushroomType::STARS:
                name = "Gain +Lvl stars from all sources";
                break;
            case LegendaryMushroomType::WINS:
                name = "Gain +1 win from all sources";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<MushroomColour> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(MushroomColour type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case MushroomColour::BLUE:
                name = "Blue Mushroom";
                break;
            case MushroomColour::BROWN:
                name = "Brown Mushroom";
                break;
            case MushroomColour::GREEN:
                name = "Green Mushroom";
                break;
            case MushroomColour::ORANGE:
                name = "Orange Mushroom";
                break;
            case MushroomColour::PINK:
                name = "Pink Mushroom";
                break;
            case MushroomColour::PURPLE:
                name = "Purple Mushroom";
                break;
            case MushroomColour::RAINBOW:
                name = "Rainbow Mushroom";
                break;
            case MushroomColour::RED:
                name = "Red Mushroom";
                break;
            case MushroomColour::WHITE:
                name = "White Mushroom";
                break;
            case MushroomColour::YELLOW:
                name = "Yellow Mushroom";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BattleMushroomType);
SPECIALISE_FORMATTER(BoostMushroomType);
SPECIALISE_FORMATTER(LegendaryMushroomColour);
SPECIALISE_FORMATTER(LegendaryMushroomType);
SPECIALISE_FORMATTER(MushroomColour);
