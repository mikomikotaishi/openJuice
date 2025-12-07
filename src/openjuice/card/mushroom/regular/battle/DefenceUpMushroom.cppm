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
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class DefenceUpMushroom
 * @brief Class representing the DefenceUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DefenceUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class DefenceUpMushroom final: public BattleMushroomCard {
private:
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
