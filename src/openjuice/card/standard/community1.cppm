/**
 * @file community1.cppm
 * @module openjuice.card.standard.community1
 * @brief Import of cards belonging to the Community Pack 1.
 *
 * This file imports the classes for cards belonging to the Community Pack 1.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.community1;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::community1);

// export import :TreasureThief; // 66
// export import :DarkSideOfBusiness; // 67
// export import :Wanted; // 68
// export import :PartyTime; // 69
// export import :LostChild; // 70
// export import :PriceOfPower; // 71

END_MODULE_NAMESPACE();
