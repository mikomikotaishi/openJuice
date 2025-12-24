/**
 * @file CoopCard.cppm
 * @module openjuice.engine.card.spawntypes:CoopCard
 * @brief Definition of the CoopCard abstract class.
 *
 * This file contains the definition of the CoopCard abstract class, which represents a Co-op card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.spawntypes:CoopCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class CoopCard
 * @brief Abstract class representing a Co-op card.
 *
 * @extends Card
 * 
 * The CoopCard abstract class extends the Card abstract class and represents a Co-op card with specific attributes.
 */
export class CoopCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for CoopCard.
     */
    CoopCard() = default;
};

/**
 * @concept ExtendsCoopCard
 * @brief Concept that checks if a type extends the CoopCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsCoopCard = IsBaseOfValue<CoopCard, T>;

END_MODULE_NAMESPACE();
