/**
 * @file SkyRestaurantPures.cppm
 * @module openjuice.card.standard.base:SkyRestaurantPures
 * @brief Implementation of the SkyRestaurantPures class.
 *
 * This file contains the implementation of the SkyRestaurantPures class, which represents the card "Sky Restaurant 'Pures'" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:SkyRestaurantPures;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class SkyRestaurantPures
 * @brief Class representing the SkyRestaurantPures card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The SkyRestaurantPures class extends both TrapCard and StandardCard to represent the card "Sky Restaurant 'Pures'" in the game.
 */
export class SkyRestaurantPures final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 15; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_PURES", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SkyRestaurantPures object.
     */
    SkyRestaurantPures(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
