/**
 * @file BattleCard.cppm
 * @module openjuice.engine.card.CardTypes:BattleCard
 * @brief Definition of the BattleCard abstract class.
 *
 * This file contains the definition of the BattleCard abstract class, which represents a Battle card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.CardTypes:BattleCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::cardtypes);

/**
 * @class BattleCard
 * @brief Abstract class representing a Battle card.
 *
 * @extends Card
 * 
 * The BattleCard abstract class extends the Card abstract class and represents a battle card with specific attributes.
 */
export class BattleCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BattleCard.
     */
    BattleCard() = default;
};

/**
 * @concept ExtendsBattleCard
 * @brief Concept that checks if a type extends the BattleCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBattleCard = IsBaseOfValue<BattleCard, T>; 

END_MODULE_NAMESPACE();
