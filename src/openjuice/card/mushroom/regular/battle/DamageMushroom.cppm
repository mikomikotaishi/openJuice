/**
 * @file DamageMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle.DamageMushroom
 * @brief Implementation of the DamageMushroom class.
 *
 * This file contains the implementation of the DamageMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomType::Damage effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle.DamageMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BattleMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class DamageMushroom
 * @brief Class representing the DamageMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DamageMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomType::Stars effect in the game.
 */
export class DamageMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DAMAGE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a DamageMushroom object.
     */
    DamageMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Battle, DAMAGE) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
