/**
 * @file HyperCard.cppm
 * @module openjuice.engine.card.SpawnTypes:HyperCard
 * @brief Definition of the HyperCard abstract class.
 *
 * This file contains the definition of the HyperCard abstract class, which represents a Hyper card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.SpawnTypes:HyperCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class HyperCard
 * @brief Abstract class representing a Hyper card.
 *
 * @extends Card
 * 
 * The HyperCard abstract class extends the Card abstract class and represents a Hyper card with specific attributes.
 */
export class HyperCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for HyperCard.
     */
    HyperCard() = default;
};

/**
 * @concept ExtendsHyperCard
 * @brief Concept that checks if a type extends the HyperCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsHyperCard = IsBaseOfValue<HyperCard, T>;

END_MODULE_NAMESPACE();
