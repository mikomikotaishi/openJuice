/**
 * @file role.cppm
 * @module openjuice.card.coop.role
 * @brief Import of all Role Hyper Cards.
 *
 * This file imports the modules for all Role Hyper Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:coop.role;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::role);

/**
 * @class UltimateWeaponInTheSun
 * @brief Class representing the UltimateWeaponInTheSun card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The UltimateWeaponInTheSun class extends both BoostCard, HyperCard, and SeasonalCard to represent the card "Ultimate Weapon in the Sun" in the game.
 */
export class UltimateWeaponInTheSun final: public BoostCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_COOP_CLASS_ATTACKER", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 1; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a UltimateWeaponInTheSun object.
     */
    UltimateWeaponInTheSun(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class LifeguardOnTheWhiteBeach
 * @brief Class representing the LifeguardOnTheWhiteBeach card.
 *
 * @extends EventCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The LifeguardOnTheWhiteBeach class extends both EventCard, HyperCard, and SeasonalCard to represent the card "Lifeguard on the White Beach" in the game.
 */
export class LifeguardOnTheWhiteBeach final: public EventCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_COOP_CLASS_GUARDIAN", "CARD_ARTIST_HEXUN")
public:
    static constexpr u8 ID = 2; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a LifeguardOnTheWhiteBeach object.
     */
    LifeguardOnTheWhiteBeach(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GuardianOfBloomingFlowers
 * @brief Class representing the GuardianOfBloomingFlowers card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The GuardianOfBloomingFlowers class extends both BoostCard, HyperCard, and SeasonalCard to represent the card "Guardian of Blooming Flowers" in the game.
 */
export class GuardianOfBloomingFlowers final: public BoostCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_COOP_CLASS_SUPPORT", "CARD_ARTIST_COFFGIRL")
public:
    static constexpr u8 ID = 3; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a GuardianOfBloomingFlowers object.
     */
    GuardianOfBloomingFlowers(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class UnforgivingAvenger
 * @brief Class representing the UnforgivingAvenger card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The UnforgivingAvenger class extends both BoostCard, HyperCard, and SeasonalCard to represent the card "Unforgiving Avenger" in the game.
 */
export class UnforgivingAvenger final: public BoostCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_COOP_CLASS_AVENGER", "CARD_ARTIST_LENDO_KHAR")
public:
    static constexpr u8 ID = 4; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a UnforgivingAvenger object.
     */
    UnforgivingAvenger(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SummerGames
 * @brief Class representing the SummerGames card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SummerGames class extends both BoostCard, HyperCard, and SeasonalCard to represent the card "Summer Games" in the game.
 */
export class SummerGames final: public BoostCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_COOP_CLASS_DEALER", "CARD_ARTIST_AIRIE")
public:
    static constexpr u8 ID = 5; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a SummerGames object.
     */
    SummerGames(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
