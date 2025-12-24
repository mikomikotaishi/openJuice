/**
 * @file Rbits.cppm
 * @module openjuice.card.standard.base:Rbits
 * @brief Implementation of the Rbits class.
 *
 * This file contains the implementation of the Rbits class, which represents the card "Rbits" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:Rbits;

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
 * @class Rbits
 * @brief Class representing the Rbits card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The Rbits class extends both BattleCard and StandardCard to represent the card "Rbits" in the game.
 */
export class Rbits final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 8; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 3; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BATTLE_RBITS", "CARD_ARTIST_MIZUKISEO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise an Rbits object.
     */
    Rbits(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
