/**
 * @file AccelHyper.cppm
 * @module openjuice.card.standard.acceleration:AccelHyper
 * @brief Implementation of the AccelHyper class.
 *
 * This file contains the implementation of the AccelHyper class, which represents the card "Accel Hyper" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration:AccelHyper;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class AccelHyper
 * @brief Class representing the AccelHyper card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The AccelHyper class extends both BattleCard and StandardCard to represent the card "Accel Hyper" in the game.
 */
export class AccelHyper final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 56; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BATTLE_ACCELHYPER", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a AccelHyper object.
     */
    AccelHyper(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
