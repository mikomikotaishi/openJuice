/**
 * @file HereAndThere.cppm
 * @module openjuice.card.standard.base.HereAndThere
 * @brief Implementation of the HereAndThere class.
 *
 * This file contains the implementation of the HereAndThere class, which represents the card "Here and There" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base.HereAndThere;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class HereAndThere
 * @brief Class representing the HereAndThere card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The HereAndThere class extends both EventCard and StandardCard to represent the card "Here and There" in the game.
 */
export class HereAndThere final: public EventCard, public StandardCard {
private:
    static constexpr u16 ID = 16; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::EVENT_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_HEREANDTHERE", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HereAndThere object.
     */
    HereAndThere(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
