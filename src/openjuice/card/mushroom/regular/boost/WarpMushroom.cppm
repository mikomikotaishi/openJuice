/**
 * @file WarpMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.WarpMushroom
 * @brief Implementation of the WarpMushroom class.
 *
 * This file contains the implementation of the WarpMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Warp effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.WarpMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class WarpMushroom
 * @brief Class representing the WarpMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The WarpMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class WarpMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_WARP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a WarpMushroom object.
     */
    WarpMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, WARP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
