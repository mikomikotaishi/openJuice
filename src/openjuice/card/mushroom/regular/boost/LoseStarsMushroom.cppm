/**
 * @file LoseStarsMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.LoseStarsMushroom
 * @brief Implementation of the LoseStarsMushroom class.
 *
 * This file contains the implementation of the LoseStarsMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::LoseStars effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.LoseStarsMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class LoseStarsMushroom
 * @brief Class representing the LoseStarsMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The LoseStarsMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::Stars effect in the game.
 */
export class LoseStarsMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_LOSESTARS");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LoseStarsMushroom object.
     */
    LoseStarsMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, LOSE_STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
