/**
 * @file EventCard.cppm
 * @module openjuice.engine.card.CardTypes:EventCard
 * @brief Definition of the EventCard abstract class.
 *
 * This file contains the definition of the EventCard abstract class, which represents an Event card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.CardTypes:EventCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::cardtypes);

/**
 * @class EventCard
 * @brief Abstract class representing an Event card.
 * 
 * @extends Card
 *
 * The EventCard abstract class extends the Card abstract class and represents an Event card with specific attributes.
 */
export class EventCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for EventCard.
     */
    EventCard() = default;
};

/**
 * @concept ExtendsEventCard
 * @brief Concept that checks if a type extends the EventCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsEventCard = IsBaseOfValue<EventCard, T>;

END_MODULE_NAMESPACE();
