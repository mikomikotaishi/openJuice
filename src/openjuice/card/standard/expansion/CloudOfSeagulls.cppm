/**
 * @file CloudOfSeagulls.cppm
 * @module openjuice.card.standard.expansion:CloudOfSeagulls
 * @brief Implementation of the CloudOfSeagulls class.
 *
 * This file contains the implementation of the CloudOfSeagulls class, which represents the card "Cloud of Seagulls" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:CloudOfSeagulls;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class CloudOfSeagulls
 * @brief Class representing the CloudOfSeagulls card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The CloudOfSeagulls class extends both EventCard and StandardCard to represent the card "Cloud of Seagulls" in the game.
 */
export class CloudOfSeagulls final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 36; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_EVENT_SEAGULLS", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a CloudOfSeagulls object.
     */
    CloudOfSeagulls(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
