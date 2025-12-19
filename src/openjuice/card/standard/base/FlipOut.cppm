/**
 * @file FlipOut.cppm
 * @module openjuice.card.standard.base.FlipOut
 * @brief Implementation of the FlipOut class.
 *
 * This file contains the implementation of the FlipOut class, which represents the card "Flip Out" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base.FlipOut;

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
 * @class FlipOut
 * @brief Class representing the FlipOut card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The FlipOut class extends both BoostCard and StandardCard to represent the card "Flip Out" in the game.
 */
export class FlipOut final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 3; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_FLIPOUT", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a FlipOut object.
     */
    FlipOut(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
