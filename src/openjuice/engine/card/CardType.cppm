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

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @enum CardType
 * @brief Enumeration for card types.
 * 
 * The CardType enumeration defines the types of cards in the game.
 */
export enum class CardType: u8 {
    BATTLE = 1, ///< Battle card type.
    BOOST, ///< Boost card type.
    TRAP, ///< Trap card type.
    EVENT, ///< Event card type.
    GIFT, ///< Gift card type.
    BANNER ///< Banner card type.
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
            case CardType::BATTLE:
                name = "Battle";
                break;
            case CardType::BOOST:
                name = "Boost";
                break;
            case CardType::TRAP:
                name = "Trap";
                break;
            case CardType::EVENT:
                name = "Event";
                break;
            case CardType::GIFT:
                name = "Gift";
                break;
            case CardType::BANNER:
                name = "Banner";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(CardType);
