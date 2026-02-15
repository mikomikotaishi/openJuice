/**
 * @file FinalBattle.cppm
 * @module openjuice.card.standard.base:FinalBattle
 * @brief Implementation of the FinalBattle class.
 *
 * This file contains the implementation of the FinalBattle class, which represents the card "Final Battle" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:FinalBattle;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class FinalBattle
 * @brief Class representing the FinalBattle card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The FinalBattle class extends both BattleCard and StandardCard to represent the card "Final Battle" in the game.
 */
export class FinalBattle final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 10; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_BATTLE_FINALBATTLE", "CARD_ARTIST_TORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a FinalBattle object.
     */
    FinalBattle():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
