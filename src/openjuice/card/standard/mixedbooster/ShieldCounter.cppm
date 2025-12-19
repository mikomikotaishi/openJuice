/**
 * @file ShieldCounter.cppm
 * @module openjuice.card.standard.mixedbooster.ShieldCounter
 * @brief Implementation of the ShieldCounter class.
 *
 * This file contains the implementation of the ShieldCounter class, which represents the card "Shield Counter" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster.ShieldCounter;

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
 * @class ShieldCounter
 * @brief Class representing the ShieldCounter card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The ShieldCounter class extends both BattleCard and StandardCard to represent the card "Shield Counter" in the game.
 */
export class ShieldCounter final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 49; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    CARD_METADATA("CARD_BATTLE_SHIELDCOUNTER", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ShieldCounter object.
     */
    ShieldCounter(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
