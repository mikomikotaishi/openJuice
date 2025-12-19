/**
 * @file GenericBattleCard.cppm
 * @module openjuice.card.generic.GenericBattleCard
 * @brief Implementation of the GenericBattleCard class.
 *
 * This file contains the implementation of the GenericBattleCard class, which represents a generic Battle card.
 */

module;

#include "Macros.hpp"

export module openjuice.card.generic.GenericBattleCard;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::generic);

/**
 * @class GenericBattleCard
 * @brief Class representing the GenericBattleCard card.
 *
 * @extends BattleCard
 * @extends GenericCard
 *
 * The GenericBattleCard class extends BattleCard and GenericCard, and represents a generic Battle card.
 */
export class GenericBattleCard final: public BattleCard, public GenericCard {
public:
    static constexpr u8 ID = std::util::to_underlying(CardType::BATTLE); ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_BATTLE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericBattleCard object.
     */
    GenericBattleCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
