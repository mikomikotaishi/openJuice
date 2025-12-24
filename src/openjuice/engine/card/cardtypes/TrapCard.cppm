/**
 * @file TrapCard.cppm
 * @module openjuice.engine.card.cardtypes:TrapCard
 * @brief Definition of the TrapCard abstract class.
 *
 * This file contains the definition of the TrapCard abstract class, which represents a Trap card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.cardtypes:TrapCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::cardtypes);

/**
 * @class TrapCard
 * @brief Abstract class representing a Trap card.
 *
 * @extends Card
 * 
 * The TrapCard abstract class extends the Card abstract class and represents a Trap card with specific attributes.
 */
export class TrapCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for TrapCard.
     */
    TrapCard() = default;
};

/**
 * @concept ExtendsTrapCard
 * @brief Concept that checks if a type extends the TrapCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsTrapCard = IsBaseOfValue<TrapCard, T>;

END_MODULE_NAMESPACE();
