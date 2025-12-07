/**
 * @file ConfusionMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.ConfusionMushroom
 * @brief Implementation of the ConfusionMushroom class.
 *
 * This file contains the implementation of the ConfusionMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Confusion effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.ConfusionMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class ConfusionMushroom
 * @brief Class representing the ConfusionMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The ConfusionMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class ConfusionMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_CONFUSION");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ConfusionMushroom object.
     */
    ConfusionMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, CONFUSION) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
