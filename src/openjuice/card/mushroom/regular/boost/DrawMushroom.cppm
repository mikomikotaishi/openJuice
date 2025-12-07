/**
 * @file DrawMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.DrawMushroom
 * @brief Implementation of the DrawMushroom class.
 *
 * This file contains the implementation of the DrawMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Draw effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.DrawMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class DrawMushroom
 * @brief Class representing the DrawMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The DrawMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class DrawMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DRAW");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a DrawMushroom object.
     */
    DrawMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, DRAW) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
