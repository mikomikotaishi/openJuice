/**
 * @file PresentThief.cppm
 * @module openjuice.card.standard.acceleration.PresentThief
 * @brief Implementation of the PresentThief class.
 *
 * This file contains the implementation of the PresentThief class, which represents the card "Present Thief" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration.PresentThief;

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
 * @class PresentThief
 * @brief Class representing the PresentThief card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The PresentThief class extends both TrapCard and StandardCard to represent the card "Present Thief" in the game.
 */
export class PresentThief final: public TrapCard, public StandardCard {
private:
    static constexpr u16 ID = 60; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::TRAP_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card
    
    CARD_METADATA("CARD_TRAP_PRESENTTHIEF", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a PresentThief object.
     */
    PresentThief(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
