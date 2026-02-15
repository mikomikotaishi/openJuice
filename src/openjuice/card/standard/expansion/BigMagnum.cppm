/**
 * @file BigMagnum.cppm
 * @module openjuice.card.standard.expansion:BigMagnum
 * @brief Implementation of the BigMagnum class.
 *
 * This file contains the implementation of the BigMagnum class, which represents the card "Big Magnum" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:BigMagnum;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class BigMagnum
 * @brief Class representing the BigMagnum card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The BigMagnum class extends both BattleCard and StandardCard to represent the card "Big Magnum" in the game.
 */
export class BigMagnum final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 25; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BATTLE_BIGMAGNUM", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a BigMagnum object.
     */
    BigMagnum(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
