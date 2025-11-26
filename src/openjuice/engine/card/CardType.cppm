/**
 * @file CardType.cppm
 * @module openjuice.engine.card.Card:CardType
 * @brief Definition of the CardType enum class.
 *
 * This file contains the definition of the CardType enum class, which represents card types.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.Card:CardType;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @enum CardType
 * @brief Enumeration for card types.
 * 
 * The CardType enumeration defines the types of cards in the game.
 */
export enum class CardType: u8 {
    BANNER_CARD, ///< Banner card type.
    BATTLE_CARD, ///< Battle card type.
    BOOST_CARD, ///< Boost card type.
    EVENT_CARD, ///< Event card type.
    GIFT_CARD, ///< Gift card type.
    TRAP_CARD ///< Trap card type.
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::CardType;

template <>
struct Formatter<CardType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(CardType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case CardType::BANNER_CARD:
                name = "Banner Card";
                break;
            case CardType::BATTLE_CARD:
                name = "Battle Card";
                break;
            case CardType::BOOST_CARD:
                name = "Boost Card";
                break;
            case CardType::EVENT_CARD:
                name = "Event Card";
                break;
            case CardType::GIFT_CARD:
                name = "Gift Card";
                break;
            case CardType::TRAP_CARD:
                name = "Trap Card";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(CardType);
