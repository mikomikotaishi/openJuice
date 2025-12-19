/**
 * @file CloudOfSeagulls.cppm
 * @module openjuice.card.standard.expansion.CloudOfSeagulls
 * @brief Implementation of the CloudOfSeagulls class.
 *
 * This file contains the implementation of the CloudOfSeagulls class, which represents the card "Cloud of Seagulls" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion.CloudOfSeagulls;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

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
    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card
    
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
