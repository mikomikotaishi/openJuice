/**
 * @file BannerCard.cppm
 * @module openjuice.engine.card.cardtypes:BannerCard
 * @brief Definition of the BannerCard abstract class.
 *
 * This file contains the definition of the BannerCard abstract class, which represents a Banner card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.cardtypes:BannerCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::cardtypes);

/**
 * @class BannerCard
 * @brief Abstract class representing a Banner card.
 *
 * @extends Card
 * 
 * The Banner abstract class extends the Card abstract class and represents a banner card with specific attributes.
 */
export class BannerCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for Banner.
     */
    BannerCard() = default;
};

/**
 * @concept ExtendsBannerCard
 * @brief Concept that checks if a type extends the BannerCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBannerCard = IsBaseOfValue<BannerCard, T>; 

END_MODULE_NAMESPACE();
