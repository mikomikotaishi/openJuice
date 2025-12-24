/**
 * @file BadPudding.cppm
 * @module openjuice.card.standard.base:BadPudding
 * @brief Implementation of the BadPudding class.
 *
 * This file contains the implementation of the BadPudding class, which represents the card "Bad Pudding" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:BadPudding;

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
 * @class BadPudding
 * @brief Class representing the BadPudding card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The BadPudding class extends both TrapCard and StandardCard to represent the card "Bad Pudding" in the game.
 */
export class BadPudding final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 11; ///< The ID of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::TRAP; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_BADPUDDING", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a BadPudding object.
     */
    BadPudding():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {
        
    }
};

END_MODULE_NAMESPACE();
