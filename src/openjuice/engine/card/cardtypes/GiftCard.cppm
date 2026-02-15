/**
 * @file GiftCard.cppm
 * @module openjuice.engine.card.cardtypes:GiftCard
 * @brief Definition of the GiftCard abstract class.
 *
 * This file contains the definition of the GiftCard abstract class, which represents a Gift card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.cardtypes:GiftCard;

import stdx;

import openjuice.engine.card.Card;

using stdx::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::cardtypes);

/**
 * @class GiftCard
 * @brief Abstract class representing a Gift card.
 * 
 * @extends Card
 *
 * The GiftCard abstract class extends the Card abstract class and represents a Gift card with specific attributes.
 */
export class GiftCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for GiftCard.
     */
    GiftCard() = default;
};

/**
 * @concept ExtendsGiftCard
 * @brief Concept that checks if a type extends the GiftCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsGiftCard = IsBaseOfValue<GiftCard, T>;

END_MODULE_NAMESPACE();
