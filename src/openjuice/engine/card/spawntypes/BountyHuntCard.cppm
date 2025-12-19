/**
 * @file BountyHuntCard.cppm
 * @module openjuice.engine.card.SpawnTypes:BountyHuntCard
 * @brief Definition of the BountyHuntCard abstract class.
 *
 * This file contains the definition of the BountyHuntCard abstract class, which represents a Bounty Hunt card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.SpawnTypes:BountyHuntCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class BountyHuntCard
 * @brief Abstract class representing a Bounty Hunt card.
 *
 * @extends Card
 * 
 * The BountyHuntCard abstract class extends the Card abstract class and represents a Bounty Hunt card with specific attributes.
 */
export class BountyHuntCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BountyHuntCard.
     */
    BountyHuntCard() = default;
};

/**
 * @concept ExtendsBountyHuntCard
 * @brief Concept that checks if a type extends the BountyHuntCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBountyHuntCard = IsBaseOfValue<BountyHuntCard, T>;

END_MODULE_NAMESPACE();
