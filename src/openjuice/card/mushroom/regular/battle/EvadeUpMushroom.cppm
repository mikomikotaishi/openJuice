/**
 * @file EvadeUpMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.EvadeUpMushroom
 * @brief Implementation of the EvadeUpMushroom class.
 *
 * This file contains the implementation of the EvadeUpMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::EvadeUp effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.EvadeUpMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class EvadeUpMushroom
 * @brief Class representing the EvadeUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The EvadeUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class EvadeUpMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_EVADEUP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a EvadeUpMushroom object.
     */
    EvadeUpMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, EVADE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
