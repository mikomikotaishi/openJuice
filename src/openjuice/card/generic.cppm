/**
 * @file generic.cppm
 * @module openjuice.card.generic
 * @brief Definition of all Generic Cards.
 *
 * This file defines all Generic cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card.generic;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::generic);

/**
 * @class GenericBannerCard
 * @brief Class representing the GenericBannerCard card.
 *
 * @extends BannerCard
 * @extends GenericCard
 *
 * The GenericBannerCard class extends BannerCard and GenericCard, and represents a generic Banner card.
 */
export class GenericBannerCard final: public BannerCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::BANNER); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BANNER; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_BANNER");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericBannerCard object.
     */
    GenericBannerCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GenericBattleCard
 * @brief Class representing the GenericBattleCard card.
 *
 * @extends BattleCard
 * @extends GenericCard
 *
 * The GenericBattleCard class extends BattleCard and GenericCard, and represents a generic Battle card.
 */
export class GenericBattleCard final: public BattleCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::BATTLE); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_BATTLE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericBattleCard object.
     */
    GenericBattleCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GenericBoostCard
 * @brief Class representing the GenericBoostCard card.
 *
 * @extends BoostCard
 * @extends GenericCard
 *
 * The GenericBoostCard class extends BoostCard and GenericCard, and represents a generic Boost card.
 */
export class GenericBoostCard final: public BoostCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::BOOST); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_BOOST");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericBoostCard object.
     */
    GenericBoostCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GenericEventCard
 * @brief Class representing the GenericEventCard card.
 *
 * @extends EventCard
 * @extends GenericCard
 *
 * The GenericEventCard class extends EventCard and GenericCard, and represents a generic Event card.
 */
export class GenericEventCard final: public EventCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::EVENT); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_EVENT");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericEventCard object.
     */
    GenericEventCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GenericGiftCard
 * @brief Class representing the GenericGiftCard card.
 *
 * @extends GiftCard
 * @extends GenericCard
 *
 * The GenericGiftCard class extends GiftCard and GenericCard, and represents a generic Gift card.
 */
export class GenericGiftCard final: public GiftCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::GIFT); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_GIFT");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericGiftCard object.
     */
    GenericGiftCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GenericTrapCard
 * @brief Class representing the GenericTrapCard card.
 *
 * @extends TrapCard
 * @extends GenericCard
 *
 * The GenericTrapCard class extends TrapCard and GenericCard, and represents a generic Trap card.
 */
export class GenericTrapCard final: public TrapCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::TRAP); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_TRAP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericTrapCard object.
     */
    GenericTrapCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
