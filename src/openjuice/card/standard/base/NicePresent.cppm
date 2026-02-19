/**
 * @file NicePresent.cppm
 * @module openjuice.card.standard.base:NicePresent
 * @brief Implementation of the NicePresent class.
 *
 * This file contains the implementation of the NicePresent class, which represents the card "Nice Present" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:NicePresent;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class NicePresent
 * @brief Class representing the NicePresent card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The NicePresent class extends both BoostCard and StandardCard to represent the card "Nice Present" in the game.
 */
export class NicePresent final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 5; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_NICEPRESENT", "CARD_ARTIST_KITSUNE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a NicePresent object.
     */
    NicePresent(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
