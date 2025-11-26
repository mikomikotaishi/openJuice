/**
 * @file MoveDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.MoveDownMushroom
 * @brief Implementation of the MoveDownMushroom class.
 *
 * This file contains the implementation of the MoveDownMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::MoveDown effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.MoveDownMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class MoveDownMushroom
 * @brief Class representing the MoveDownMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The MoveDownMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class MoveDownMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_MOVEDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MoveDownMushroom object.
     */
    MoveDownMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, MOVE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
