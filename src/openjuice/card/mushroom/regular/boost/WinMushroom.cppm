/**
 * @file WinMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.WinMushroom
 * @brief Implementation of the WinMushroom class.
 *
 * This file contains the implementation of the WinMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Win effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.WinMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class WinMushroom
 * @brief Class representing the WinMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The WinMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class WinMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_WIN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a WinMushroom object.
     */
    WinMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, WIN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
