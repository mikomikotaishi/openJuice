/**
 * @file AttackDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.AttackDownMushroom
 * @brief Implementation of the AttackDownMushroom class.
 *
 * This file contains the implementation of the AttackDownMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::AttackDown effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.AttackDownMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class AttackDownMushroom
 * @brief Class representing the AttackDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The AttackDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class AttackDownMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ATTACKDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a AttackDownMushroom object.
     */
    AttackDownMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, ATTACK_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
