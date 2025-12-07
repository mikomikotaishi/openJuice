/**
 * @file HealthUpMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.HealthUpMushroom
 * @brief Implementation of the HealthUpMushroom class.
 *
 * This file contains the implementation of the HealthUpMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::HealthUp effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.HealthUpMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class HealthUpMushroom
 * @brief Class representing the HealthUpMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The HealthUpMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class HealthUpMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_HEALTHUP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HealthUpMushroom object.
     */
    HealthUpMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, HEALTH_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
