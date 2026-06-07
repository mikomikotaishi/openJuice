/**
 * @file extracurricular.cppm
 * @module openjuice.card.standard.extracurricular
 * @brief Import of cards belonging to the Extracurricular Pack.
 *
 * This file imports the classes for cards belonging to the Extracurricular Pack.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.extracurricular;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::extracurricular);

// export import :FullBurst; // 102
// export import :ChefsSpecial; // 103
// export import :GoWithTheFlow; // 104
// export import :MousseTheThief; // 105
// export import :ComingBackStronger; // 106
// export import :ExtremeAlteration; // 107
// export import :TheGreatestTroublemakerEver; // 108
// export import :LookHowLongMyArmsAndLegsAreNow; // 109
// export import :WereTickedOff; // 110
// export import :ProtectionFee; // 111
// export import :FluffyAndFuzzy; // 112
// export import :FeelTheRushWithAnEnergyDrink; // 113

END_MODULE_NAMESPACE();
