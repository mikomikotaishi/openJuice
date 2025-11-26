/**
 * @file FrostwalkerMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.FrostwalkerMushroom
 * @brief Implementation of the FrostwalkerMushroom class.
 *
 * This file contains the implementation of the FrostwalkerMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Frostwalker effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.FrostwalkerMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class FrostwalkerMushroom
 * @brief Class representing the FrostwalkerMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The FrostwalkerMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class FrostwalkerMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_FROSTWALKER");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a FrostwalkerMushroom object.
     */
    FrostwalkerMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, FROSTWALKER) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
