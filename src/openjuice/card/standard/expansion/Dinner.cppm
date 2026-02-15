/**
 * @file Dinner.cppm
 * @module openjuice.card.standard.expansion:Dinner
 * @brief Implementation of the Dinner class.
 *
 * This file contains the implementation of the Dinner class, which represents the card "Dinner" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:Dinner;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class Dinner
 * @brief Class representing the Dinner card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The Dinner class extends both EventCard and StandardCard to represent the card "Dinner" in the game.
 */
export class Dinner final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 38; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_DINNER", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Dinner object.
     */
    Dinner(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
