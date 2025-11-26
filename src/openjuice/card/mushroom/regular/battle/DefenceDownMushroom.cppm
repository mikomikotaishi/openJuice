/**
 * @file DefenceDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.DefenceDownMushroom
 * @brief Implementation of the DefenceDownMushroom class.
 *
 * This file contains the implementation of the DefenceDownMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::DefenceDown effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.DefenceDownMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class DefenceDownMushroom
 * @brief Class representing the DefenceDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DefenceDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class DefenceDownMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DEFENSEDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a DefenceDownMushroom object.
     */
    DefenceDownMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, DEFENCE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
