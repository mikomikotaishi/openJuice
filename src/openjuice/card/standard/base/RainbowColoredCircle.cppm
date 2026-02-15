/**
 * @file RainbowColoredCircle.cppm
 * @module openjuice.card.standard.base:RainbowColoredCircle
 * @brief Implementation of the RainbowColoredCircle class.
 *
 * This file contains the implementation of the RainbowColoredCircle class, which represents the card "Rainbow-Colored Circle" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:RainbowColoredCircle;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class RainbowColoredCircle
 * @brief Class representing the RainbowColoredCircle card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The RainbowColoredCircle class extends both BattleCard and StandardCard to represent the card "Rainbow-Colored Circle" in the game.
 */
export class RainbowColoredCircle final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 9; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BATTLE_RAINBOW", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a RainbowColoredCircle object.
     */
    RainbowColoredCircle(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
