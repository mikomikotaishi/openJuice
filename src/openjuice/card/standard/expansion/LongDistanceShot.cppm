/**
 * @file LongDistanceShot.cppm
 * @module openjuice.card.standard.expansion.LongDistanceShot
 * @brief Implementation of the LongDistanceShot class.
 *
 * This file contains the implementation of the LongDistanceShot class, which represents the card "Long-Distance Shot" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion.LongDistanceShot;

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
 * @class LongDistanceShot
 * @brief Class representing the LongDistanceShot card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The LongDistanceShot class extends both BoostCard and StandardCard to represent the card "Long-Distance Shot" in the game.
 */
export class LongDistanceShot final: public BoostCard, public StandardCard {
private:
    static constexpr u16 ID = 21; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_LONGSHOT", "CARD_ARTIST_YUUNANASE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LongDistanceShot object.
     */
    LongDistanceShot(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
