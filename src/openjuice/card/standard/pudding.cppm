/**
 * @file pudding.cppm
 * @module openjuice.card.standard.pudding
 * @brief Import of cards belonging to the Pudding Pack.
 *
 * This file imports the classes for cards belonging to the Pudding Pack.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.pudding;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::pudding);

// export import :BackdoorTrade; // 78
// export import :SinkOrSwim; // 79
// export import :SeriousBattle; // 80
// export import :PortablePudding; // 81
// export import :IWannaSeeYou; // 82
// export import :Encore; // 83
// export import :SweetDestroyer; // 84
// export import :SereneHush; // 85
// export import :UnpaidWork; // 86
// export import :IndiscriminateFireSupport; // 87
// export import :LuckyCharm; // 88
// export import :MetallicMonocoque; // 89

END_MODULE_NAMESPACE();
