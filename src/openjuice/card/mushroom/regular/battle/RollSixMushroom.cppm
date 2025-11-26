/**
 * @file RollSixMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.RollSixMushroom
 * @brief Implementation of the RollSixMushroom class.
 *
 * This file contains the implementation of the RollSixMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::RollSix effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.RollSixMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class RollSixMushroom
 * @brief Class representing the RollSixMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The RollSixMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class RollSixMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ROLLSIX");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a RollSixMushroom object.
     */
    RollSixMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, ROLL_SIX) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
