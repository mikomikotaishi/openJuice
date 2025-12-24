/**
 * @file Ambush.cppm
 * @module openjuice.card.standard.mixedbooster:Ambush
 * @brief Implementation of the Ambush class.
 *
 * This file contains the implementation of the Ambush class, which represents the card "Ambush" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster:Ambush;

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
 * @class Ambush
 * @brief Class representing the Ambush card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Ambush class extends both BoostCard and StandardCard to represent the card "Ambush" in the game.
 */
export class Ambush final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 44; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_AMBUSH", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Ambush object.
     */
    Ambush(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
