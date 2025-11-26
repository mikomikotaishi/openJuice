/**
 * @file LegendaryWinsMushroom.cppm
 * @module openjuice.card.mushroom.legendary.LegendaryWinsMushroom
 * @brief Implementation of the LegendaryWinsMushroom class.
 *
 * This file contains the implementation of the LegendaryWinsMushroom class, which is a
 * Legendary Mushroom providing the LegendaryMushroomType::Wins effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.legendary.LegendaryWinsMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::LegendaryMushroomColour;
using openjuice::engine::card::LegendaryMushroomType;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;

using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::legendary);

/**
 * @class LegendaryWinsMushroom
 * @brief Class representing the LegendaryWinsMushroom card.
 *
 * @extends LegendaryMushroomCard
 *
 * The LegendaryWinsMushroom class extends LegendaryMushroomCard to represent the card 
 * providing the LegendaryMushroomType::Wins effect in the game.
 */
export class LegendaryWinsMushroom final: public LegendaryMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_LEGEND_WINS");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LegendaryWinsMushroom object.
     */
    LegendaryWinsMushroom(LegendaryMushroomColour colour):
        SET_MUSHROOM_STATS(Legendary, WINS) {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
