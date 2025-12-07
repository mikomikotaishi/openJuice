/**
 * @file EvadeDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.EvadeDownMushroom
 * @brief Implementation of the EvadeDownMushroom class.
 *
 * This file contains the implementation of the EvadeDownMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::EvadeDown effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.EvadeDownMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class EvadeDownMushroom
 * @brief Class representing the EvadeDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The EvadeDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class EvadeDownMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_EVADEDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a EvadeDownMushroom object.
     */
    EvadeDownMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, EVADE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
