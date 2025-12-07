/**
 * @file ImOnFire.cppm
 * @module openjuice.card.standard.base.ImOnFire
 * @brief Implementation of the ImOnFire class.
 *
 * This file contains the implementation of the ImOnFire class, which represents the card "I'm on Fire!" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base.ImOnFire;

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
 * @class ImOnFire
 * @brief Class representing the ImOnFire card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The ImOnFire class extends both BattleCard and StandardCard to represent the card "I'm on Fire!" in the game.
 */
export class ImOnFire final: public BattleCard, public StandardCard {
private:
    static constexpr u16 ID = 7; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BATTLE_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BATTLE_ONFIRE", "CARD_ARTIST_TORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise an ImOnFire object.
     */
    ImOnFire(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
