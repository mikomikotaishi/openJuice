/**
 * @file BoostCard.cppm
 * @module openjuice.engine.card.CardTypes:BoostCard
 * @brief Definition of the BoostCard abstract class.
 *
 * This file contains the definition of the BoostCard abstract class, which represents a Boost card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.CardTypes:BoostCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::cardtypes);

/**
 * @class BoostCard
 * @brief Abstract class representing a Boost card.
 * 
 * @extends Card
 *
 * The BoostCard abstract class extends the Card abstract class and represents a Boost card with specific attributes.
 */
export class BoostCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BoostCard.
     */
    BoostCard() = default;
};

/**
 * @concept ExtendsBoostCard
 * @brief Concept that checks if a type extends the BoostCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBoostCard = IsBaseOfValue<BoostCard, T>;

END_MODULE_NAMESPACE();
