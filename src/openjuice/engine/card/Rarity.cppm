/**
 * @file Rarity.cppm
 * @module openjuice.engine.card.Card:Rarity
 * @brief Definition of the Rarity enum class.
 *
 * This file contains the definition of the Rarity enum class, which represents the rarity of a card.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.Card:Rarity;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @enum Rarity
 * @brief Enumeration for card rarities.
 * 
 * The Rarity enumeration defines the rarities of cards in the game.
 */
export enum class Rarity: u8 {
    NONE, ///< No rarity (for hyper cards).
    COMMON, ///< Common rarity.
    UNCOMMON, ///< Uncommon rarity.
    RARE, ///< Rare rarity.
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::Rarity;

template <>
struct Formatter<Rarity> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Rarity type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case Rarity::NONE:
                name = "None";
                break;
            case Rarity::COMMON:
                name = "Common";
                break;
            case Rarity::UNCOMMON:
                name = "Uncommon";
                break;
            case Rarity::RARE:
                name = "Rare";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(Rarity);
