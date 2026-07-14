/**
 * @file seasonal.cppm
 * @module openjuice.card.coop.seasonal
 * @brief Import of all Seasonal Co-op Hyper Cards.
 *
 * This file imports the modules for all Seasonal Co-op Hyper Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:coop.seasonal;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::seasonal);

/**
 * @class SeasonalUltimateWeaponInTheSun
 * @brief Class representing the SeasonalUltimateWeaponInTheSun card.
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalUltimateWeaponInTheSun class extends both BoostCard, HyperCard, and CoopCard to represent the card "Chaos Protect" in the game.
 */
export class SeasonalUltimateWeaponInTheSun final: public BoostCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_SUMMER2018_ATTACKER", "CARD_ARTIST_IKUSE")
public:
    static constexpr u16 ID = 1; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SeasonalUltimateWeaponInTheSun object.
     */
    SeasonalUltimateWeaponInTheSun(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SeasonalLifeguardOnTheWhiteBeach
 * @brief Class representing the SeasonalLifeguardOnTheWhiteBeach card.
 * @extends EventCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalLifeguardOnTheWhiteBeach class extends both EventCard, HyperCard, and CoopCard to represent the card "Lifeguard on the White Beach" (seasonal) in the game.
 */
export class SeasonalLifeguardOnTheWhiteBeach final: public EventCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_SUMMER2018_DEFENDER", "CARD_ARTIST_HEXUN")
public:
    static constexpr u16 ID = 2; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SeasonalLifeguardOnTheWhiteBeach object.
     */
    SeasonalLifeguardOnTheWhiteBeach(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SeasonalGuardianOfBloomingFlowers
 * @brief Class representing the SeasonalGuardianOfBloomingFlowers card.
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalGuardianOfBloomingFlowers class extends both BoostCard, HyperCard, and CoopCard to represent the card "Guardian of Blooming Flowers" (seasonal) in the game.
 */
export class SeasonalGuardianOfBloomingFlowers final: public BoostCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_SUMMER2018_SUPPORT", "CARD_ARTIST_COFFGIRL")
public:
    static constexpr u16 ID = 3; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SeasonalGuardianOfBloomingFlowers object.
     */
    SeasonalGuardianOfBloomingFlowers(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SeasonalUnforgivingAvenger
 * @brief Class representing the SeasonalUnforgivingAvenger card.
 * @extends BattleCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalUnforgivingAvenger class extends both BoostCard and CoopCard to represent the card "Unforgiving Avenger" (seasonal) in the game.
 */
export class SeasonalUnforgivingAvenger final: public BattleCard, public HyperCard, public CoopCard {
private:
    CARD_METADATA("CARD_HYPER_SUMMER2018_AVENGER", "CARD_ARTIST_LENDO_KHAR")
public:
    static constexpr u16 ID = 2004; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SeasonalUnforgivingAvenger object.
     */
    SeasonalUnforgivingAvenger(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
