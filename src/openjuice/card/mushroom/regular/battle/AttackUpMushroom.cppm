/**
 * @file AttackUpMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.AttackUpMushroom
 * @brief Implementation of the AttackUpMushroom class.
 *
 * This file contains the implementation of the AttackUpMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::AttackUp effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.AttackUpMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class AttackUpMushroom
 * @brief Class representing the AttackUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The AttackUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class AttackUpMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ATTACKUP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a AttackUpMushroom object.
     */
    AttackUpMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, ATTACK_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
