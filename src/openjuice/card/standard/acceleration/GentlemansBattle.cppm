/**
 * @file GentlemansBattle.cppm
 * @module openjuice.card.standard.acceleration.GentlemansBattle
 * @brief Implementation of the GentlemansBattle class.
 *
 * This file contains the implementation of the GentlemansBattle class, which represents the card "Gentleman's Battle" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration.GentlemansBattle;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class GentlemansBattle
 * @brief Class representing the GentlemansBattle card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The GentlemansBattle class extends both BoostCard and StandardCard to represent the card "Gentleman's Battle" in the game.
 */
export class GentlemansBattle final: public BoostCard, public StandardCard {
private:
    static constexpr u16 ID = 55; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BOOST_GENTLEMANSBATTLE", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GentlemansBattle object.
     */
    GentlemansBattle(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
