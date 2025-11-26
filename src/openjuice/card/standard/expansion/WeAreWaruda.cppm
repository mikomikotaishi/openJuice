/**
 * @file WeAreWaruda.cppm
 * @module openjuice.card.standard.expansion.WeAreWaruda
 * @brief Implementation of the WeAreWaruda class.
 *
 * This file contains the implementation of the WeAreWaruda class, which represents the card "We Are Waruda" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion.WeAreWaruda;

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
 * @class WeAreWaruda
 * @brief Class representing the WeAreWaruda card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The WeAreWaruda class extends both EventCard and StandardCard to represent the card "We Are Waruda" in the game.
 */
export class WeAreWaruda final: public EventCard, public StandardCard {
private:
    static constexpr u16 ID = 37; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::EVENT_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_WARUDA", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a WeAreWaruda object.
     */
    WeAreWaruda(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
