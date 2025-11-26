/**
 * @file GainStarsMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.GainStarsMushroom
 * @brief Implementation of the GainStarsMushroom class.
 *
 * This file contains the implementation of the GainStarsMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::GainStars effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.GainStarsMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class GainStarsMushroom
 * @brief Class representing the GainStarsMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The GainStarsMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class GainStarsMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_GAINSTARS");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GainStarsMushroom object.
     */
    GainStarsMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, GAIN_STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
