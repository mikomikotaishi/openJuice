/**
 * @file BossCard.cppm
 * @module openjuice.engine.card.spawntypes:BossCard
 * @brief Definition of the BossCard abstract class.
 *
 * This file contains the definition of the BossCard abstract class, which represents a Boss card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.spawntypes:BossCard;

import stdx;

import openjuice.engine.card.Card;

using stdx::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class BossCard
 * @brief Abstract class representing a Boss card.
 *
 * @extends Card
 * 
 * The BossCard abstract class extends the Card abstract class and represents a Boss card with specific attributes.
 */
export class BossCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BossCard.
     */
    BossCard() = default;
};

/**
 * @concept ExtendsBossCard
 * @brief Concept that checks if a type extends the BossCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBossCard = IsBaseOfValue<BossCard, T>;

END_MODULE_NAMESPACE();
