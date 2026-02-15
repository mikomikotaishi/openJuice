/**
 * @file CharacterSpecificCard.cppm
 * @module openjuice.engine.card.spawntypes:CharacterSpecificCard
 * @brief Definition of the CharacterSpecificCard abstract class.
 *
 * This file contains the definition of the CharacterSpecificCard abstract class, which represents a Character-specific card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.spawntypes:CharacterSpecificCard;

import stdx;

import openjuice.engine.card.Card;

using stdx::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class CharacterSpecificCard
 * @brief Abstract class representing a Hyper card.
 *
 * @extends Card
 * 
 * The CharacterSpecificCard abstract class extends the Card abstract class and represents a Hyper card with specific attributes.
 */
export class CharacterSpecificCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for CharacterSpecificCard.
     */
    CharacterSpecificCard() = default;
};

/**
 * @concept ExtendsCharacterSpecificCard
 * @brief Concept that checks if a type extends the CharacterSpecificCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsCharacterSpecificCard = IsBaseOfValue<CharacterSpecificCard, T>;

END_MODULE_NAMESPACE();
