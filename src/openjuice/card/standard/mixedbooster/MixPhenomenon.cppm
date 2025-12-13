/**
 * @file MixPhenomenon.cppm
 * @module openjuice.card.standard.mixedbooster.MixPhenomenon
 * @brief Implementation of the MixPhenomenon class.
 *
 * This file contains the implementation of the MixPhenomenon class, which represents the card "Mix Phenomenon" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster.MixPhenomenon;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::mixedbooster);

/**
 * @class MixPhenomenon
 * @brief Class representing the MixPhenomenon card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The MixPhenomenon class extends both EventCard and StandardCard to represent the card "Mix Phenomenon" in the game.
 */
export class MixPhenomenon final: public EventCard, public StandardCard {
private:
    static constexpr u16 ID = 52; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_MIXPHENOMENON", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MixPhenomenon object.
     */
    MixPhenomenon(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
