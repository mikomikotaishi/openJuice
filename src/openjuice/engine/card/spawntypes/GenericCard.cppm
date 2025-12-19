/**
 * @file GenericCard.cppm
 * @module openjuice.engine.card.SpawnTypes:GenericCard
 * @brief Definition of the GenericCard abstract class.
 *
 * This file contains the definition of the GenericCard abstract class, which represents a Generic (placeholder) card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.SpawnTypes:GenericCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class GenericCard
 * @brief Abstract class representing a Generic (placeholder) card.
 *
 * @extends Card
 * 
 * The GenericCard abstract class extends the Card abstract class and represents a Generic (placeholder) card.
 */
export class GenericCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for GenericCard.
     */
    GenericCard() = default;
};

/**
 * @concept ExtendsGenericCard
 * @brief Concept that checks if a type extends the GenericCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsGenericCard = IsBaseOfValue<GenericCard, T>;

END_MODULE_NAMESPACE();
