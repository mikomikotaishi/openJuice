/**
 * @file Shield.cppm
 * @module openjuice.card.standard.expansion:Shield
 * @brief Implementation of the Shield class.
 *
 * This file contains the implementation of the Shield class, which represents the card "Shield" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:Shield;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class Shield
 * @brief Class representing the Shield card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The Shield class extends both BattleCard and StandardCard to represent the card "Shield" in the game.
 */
export class Shield final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 26; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BATTLE_SHIELD", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Shield object.
     */
    Shield(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
