/**
 * @file BrutalPrank.cppm
 * @module openjuice.card.standard.acceleration.BrutalPrank
 * @brief Implementation of the BrutalPrank class.
 *
 * This file contains the implementation of the BrutalPrank class, which represents the card "Brutal Prank" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration.BrutalPrank;

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
 * @class BrutalPrank
 * @brief Class representing the BrutalPrank card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The BrutalPrank class extends both TrapCard and StandardCard to represent the card "Brutal Prank" in the game.
 */
export class BrutalPrank final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 59; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::TRAP; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card
    
    CARD_METADATA("CARD_TRAP_BRUTALPRANK", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a BrutalPrank object.
     */
    BrutalPrank(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
