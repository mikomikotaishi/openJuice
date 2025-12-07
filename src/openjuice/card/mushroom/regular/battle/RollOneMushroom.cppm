/**
 * @file RollOneMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.RollOneMushroom
 * @brief Implementation of the RollOneMushroom class.
 *
 * This file contains the implementation of the RollOneMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::RollOne effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.RollOneMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class RollOneMushroom
 * @brief Class representing the RollOneMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The RollOneMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class RollOneMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ROLLONE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a RollOneMushroom object.
     */
    RollOneMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, ROLL_ONE) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
