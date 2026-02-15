/**
 * @file StiffCrystal.cppm
 * @module openjuice.card.standard.expansion:StiffCrystal
 * @brief Implementation of the StiffCrystal class.
 *
 * This file contains the implementation of the StiffCrystal class, which represents the card "Stiff Crystal" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:StiffCrystal;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class StiffCrystal
 * @brief Class representing the StiffCrystal card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The StiffCrystal class extends both BoostCard and StandardCard to represent the card "Stiff Crystal" in the game.
 */
export class StiffCrystal final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 22; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_STIFFCRYSTAL", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a StiffCrystal object.
     */
    StiffCrystal(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
