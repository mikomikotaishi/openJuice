/**
 * @file StandardCard.cppm
 * @module openjuice.engine.card.SpawnTypes:StandardCard
 * @brief Definition of the StandardCard abstract class.
 *
 * This file contains the definition of the StandardCard abstract class, which represents a Standard card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.SpawnTypes:StandardCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class StandardCard
 * @brief Abstract class representing a Standard card.
 *
 * @extends Card
 * 
 * The StandardCard abstract class extends the Card abstract class and represents a Standard card with specific attributes.
 */
export class StandardCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for StandardCard.
     */
    StandardCard() = default;
};

/**
 * @concept ExtendsStandardCard
 * @brief Concept that checks if a type extends the StandardCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsStandardCard = IsBaseOfValue<StandardCard, T>;

END_MODULE_NAMESPACE();
