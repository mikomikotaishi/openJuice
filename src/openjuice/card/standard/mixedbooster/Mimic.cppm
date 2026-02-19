/**
 * @file Mimic.cppm
 * @module openjuice.card.standard.mixedbooster:Mimic
 * @brief Implementation of the Mimic class.
 *
 * This file contains the implementation of the Mimic class, which represents the card "Mimic" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster:Mimic;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::mixedbooster);

/**
 * @class Mimic
 * @brief Class representing the Mimic card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Mimic class extends both BoostCard and StandardCard to represent the card "Mimic" in the game.
 */
export class Mimic final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 47; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_MIMIC", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Mimic object.
     */
    Mimic(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
