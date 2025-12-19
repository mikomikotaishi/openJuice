/**
 * @file DefenceUpMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.DefenceUpMushroom
 * @brief Implementation of the DefenceUpMushroom class.
 *
 * This file contains the implementation of the DefenceUpMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::DefenceUp effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.DefenceUpMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class DefenceUpMushroom
 * @brief Class representing the DefenceUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DefenceUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::DEFENCE_UP effect in the game.
 */
export class DefenceUpMushroom final: public BattleMushroomCard {
public:
    static constexpr u16 ID = std::util::to_underlying(BattleMushroomType::DEFENCE_UP); ///< The ID of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_DEFENSEUP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a DefenceUpMushroom object.
     */
    DefenceUpMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, DEFENCE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
