/**
 * @file Dash.cppm
 * @module openjuice.card.standard.base:Dash
 * @brief Implementation of the Dash class.
 *
 * This file contains the implementation of the Dash class, which represents the card "Dash" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:Dash;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class Dash
 * @brief Class representing the Dash card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Dash class extends both BoostCard and StandardCard to represent the card "Dash" in the game.
 */
export class Dash final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 1; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 3; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_DASH", "CARD_ARTIST_TORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Dash object.
     */
    Dash():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
