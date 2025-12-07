/**
 * @file MoveUpMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.MoveUpMushroom
 * @brief Implementation of the MoveUpMushroom class.
 *
 * This file contains the implementation of the MoveUpMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::MoveUp effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.MoveUpMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class MoveUpMushroom
 * @brief Class representing the MoveUpMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The MoveUpMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class MoveUpMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_MOVEUP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MoveUpMushroom object.
     */
    MoveUpMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, MOVE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
