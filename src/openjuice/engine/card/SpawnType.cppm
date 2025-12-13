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

namespace fmt = std::fmt;
namespace sys = std::sys;

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
    SEASONAL, ///< Seasonal spawn type.
    MUSHROOM, ///< Mushroom spawn type.
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
            case SpawnType::SEASONAL:
                name = "Seasonal";
                break;
            case SpawnType::MUSHROOM:
                name = "Mushroom";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(SpawnType);
