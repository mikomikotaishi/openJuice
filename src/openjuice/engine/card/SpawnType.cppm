/**
 * @file SpawnType.cppm
 * @module openjuice.engine.card.Card:SpawnType
 * @brief Definition of the SpawnType enum class.
 *
 * This file contains the definition of the SpawnType enum class, which represents spawn types.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.Card:SpawnType;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @enum SpawnType
 * @brief Enumeration for card spawn types.
 * 
 * The SpawnType enumeration defines the spawn types of cards in the game.
 */
export enum class SpawnType: u8 {
    STANDARD, ///< Standard spawn type.
    HYPER, ///< Hyper spawn type.
    CHARACTER_SPECIFIC, ///< Character-specific spawn type.
    SEASONAL, ///< Seasonal spawn type.
    MUSHROOM, ///< Mushroom spawn type.
    COOP, ///< Co-op spawn type.
    BOSS, ///< Boss spawn type.
    BOUNTY_HUNT, ///< Bounty Hunt spawn type.
    GENERIC ///< Generic (placeholder) spawn type.
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::SpawnType;

template <>
struct Formatter<SpawnType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(SpawnType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case SpawnType::STANDARD:
                name = "Standard";
                break;
            case SpawnType::HYPER:
                name = "Hyper";
                break;
            case SpawnType::CHARACTER_SPECIFIC:
                name = "Character-specific";
                break;
            case SpawnType::SEASONAL:
                name = "Seasonal";
                break;
            case SpawnType::MUSHROOM:
                name = "Mushroom";
                break;
            case SpawnType::COOP:
                name = "Co-op";
                break;
            case SpawnType::BOSS:
                name = "Boss";
                break;
            case SpawnType::BOUNTY_HUNT:
                name = "Bounty Hunt";
                break;
            case SpawnType::GENERIC:
                name = "Generic";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(SpawnType);
