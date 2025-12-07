/**
 * @file NullBattleMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.NullBattleMushroom
 * @brief Implementation of the NullBattleMushroom class.
 *
 * This file contains the implementation of the NullBattleMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::NullBattle effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.NullBattleMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class NullBattleMushroom
 * @brief Class representing the NullBattleMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The NullBattleMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class NullBattleMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a NullBattleMushroom object.
     */
    NullBattleMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, NULL_BATTLE) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
