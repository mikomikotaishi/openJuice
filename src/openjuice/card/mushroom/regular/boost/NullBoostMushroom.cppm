/**
 * @file NullBoostMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.NullBoostMushroom
 * @brief Implementation of the NullBoostMushroom class.
 *
 * This file contains the implementation of the NullBoostMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::NullBoost effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.NullBoostMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class NullBoostMushroom
 * @brief Class representing the NullBoostMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The NullBoostMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class NullBoostMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a NullBoostMushroom object.
     */
    NullBoostMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, NULL_BOOST) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
