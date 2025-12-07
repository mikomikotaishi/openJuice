/**
 * @file HealthDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.HealthDownMushroom
 * @brief Implementation of the HealthDownMushroom class.
 *
 * This file contains the implementation of the HealthDownMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::HealthDown effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.HealthDownMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class HealthDownMushroom
 * @brief Class representing the HealthDownMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The HealthDownMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class HealthDownMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_HEALTHDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HealthDownMushroom object.
     */
    HealthDownMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, HEALTH_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
