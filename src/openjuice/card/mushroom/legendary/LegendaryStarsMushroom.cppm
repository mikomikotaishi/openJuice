/**
 * @file LegendaryStarsMushroom.cppm
 * @module openjuice.card.mushroom.legendary.LegendaryStarsMushroom
 * @brief Implementation of the LegendaryStarsMushroom class.
 *
 * This file contains the implementation of the LegendaryStarsMushroom class, which is a
 * Legendary Mushroom providing the LegendaryMushroomType::Stars effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.legendary.LegendaryStarsMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::LegendaryMushroomColour;
using openjuice::engine::card::LegendaryMushroomType;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::legendary);

/**
 * @class LegendaryStarsMushroom
 * @brief Class representing the LegendaryStarsMushroom card.
 *
 * @extends LegendaryMushroomCard
 *
 * The LegendaryStarsMushroom class extends LegendaryMushroomCard to represent the card 
 * providing the LegendaryMushroomType::Stars effect in the game.
 */
export class LegendaryStarsMushroom final: public LegendaryMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_LEGEND_STARS");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LegendaryStarsMushroom object.
     */
    LegendaryStarsMushroom(LegendaryMushroomColour colour):
        SET_MUSHROOM_STATS(Legendary, STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
