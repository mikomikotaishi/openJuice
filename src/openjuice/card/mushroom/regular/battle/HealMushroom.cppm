/**
 * @file HealMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.HealMushroom
 * @brief Implementation of the HealMushroom class.
 *
 * This file contains the implementation of the HealMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::Heal effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.HealMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class HealMushroom
 * @brief Class representing the HealMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The HealMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class HealMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_HEAL");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HealMushroom object.
     */
    HealMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, HEAL) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
