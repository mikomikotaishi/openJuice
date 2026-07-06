/**
 * @file type.cppm
 * @module openjuice.engine.card.type
 * @brief Import of card classification type module partitions.
 *
 * This file imports the module partitions for different card types.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.type;

import stdx;

import openjuice.engine.card.Card;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::type);

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
 * @class BoostCard
 * @brief Abstract class representing a Boost card.
 * 
 * @extends Card
 *
 * The BoostCard abstract class extends the Card abstract class and represents a Boost card with specific attributes.
 */
export class BoostCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BoostCard.
     */
    BoostCard() = default;
};

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

END_MODULE_NAMESPACE();
