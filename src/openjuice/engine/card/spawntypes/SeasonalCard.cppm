/**
 * @file SeasonalCard.cppm
 * @module openjuice.engine.card.spawntypes:SeasonalCard
 * @brief Definition of the SeasonalCard abstract class.
 *
 * This file contains the definition of the SeasonalCard abstract class, which represents a Seasonal card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.spawntypes:SeasonalCard;

import stdx;

import openjuice.engine.card.Card;

using stdx::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class SeasonalCard
 * @brief Abstract class representing a Seasonal card.
 *
 * @extends Card
 * 
 * The SeasonalCard abstract class extends the Card abstract class and represents a Seasonal card with specific attributes.
 */
export class SeasonalCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for SeasonalCard.
     */
    SeasonalCard() = default;
};

/**
 * @concept ExtendsSeasonalCard
 * @brief Concept that checks if a type extends the SeasonalCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsSeasonalCard = IsBaseOfValue<SeasonalCard, T>;

END_MODULE_NAMESPACE();
