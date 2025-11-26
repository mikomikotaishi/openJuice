/**
 * @file DiscardMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.DiscardMushroom
 * @brief Implementation of the DiscardMushroom class.
 *
 * This file contains the implementation of the DiscardMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Discard effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.DiscardMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class DiscardMushroom
 * @brief Class representing the DiscardMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The DiscardMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class DiscardMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DISCARD");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a DiscardMushroom object.
     */
    DiscardMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, DISCARD) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
