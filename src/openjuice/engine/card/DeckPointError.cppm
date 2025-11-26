/**
 * @file DeckPointError.cppm
 * @module openjuice.engine.card.Card:DeckPointError
 * @brief Definition of the DeckPointError enum class.
 *
 * This file contains the definition of the DeckPointError enum class, which represents errors in deck point retrievals.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.Card:DeckPointError;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @enum DeckPointError
 * @brief Enumeration for deck point errors.
 * 
 * The DeckPointError enumeration defines the types of errors in retrieving deck points of a card.
 */
export enum class DeckPointError: u8 {
    NOT_PLAYABLE_IN_COOP, ///< Card cannot be played in Co-op mode
    NOT_STANDARD_CARD ///< Card is not a Standard-type card
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::DeckPointError;

template <>
struct Formatter<DeckPointError> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(DeckPointError err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case DeckPointError::NOT_PLAYABLE_IN_COOP:
                name = "Not playable in co-op";
                break;
            case DeckPointError::NOT_STANDARD_CARD:
                name = "Not standard card";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(DeckPointError);
