/**
 * @file seasonal.cppm
 * @module openjuice.card.seasonal
 * @brief Import of all Seasonal Cards.
 *
 * This file imports the modules for all Seasonal Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:seasonal;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class SweetBattle
 * @brief Class representing the SweetBattle card.
 *
 * @extends GiftCard
 * @extends SeasonalCard
 *
 * The SweetBattle class extends both GiftCard and SeasonalCard to represent the card "Sweet Battle" in the game.
 */
export class SweetBattle final: public GiftCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_GIFT_VALENTINESDAY2018", "CARD_ARTIST_HONO")
public:
    static constexpr u8 ID = 1; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SweetBattle object.
     */
    SweetBattle(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SnowballReflector
 * @brief Class representing the SnowballReflector card.
 *
 * @extends BattleCard
 * @extends SeasonalCard
 *
 * The SnowballReflector class extends both BattleCard and SeasonalCard to represent the card "Snowball Reflector" in the game.
 */
export class SnowballReflector final: public BattleCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_XMAS2018_SNOWBALLREFLECTOR", "CARD_ARTIST_COFFGIRL")
public:
    static constexpr u8 ID = 2; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SnowballReflector object.
     */
    SnowballReflector(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GrownupSnowballFight
 * @brief Class representing the GrownupSnowballFight card.
 *
 * @extends BattleCard
 * @extends SeasonalCard
 *
 * The GrownupSnowballFight class extends both BattleCard and SeasonalCard to represent the card "Grown-up Snowball Fight" in the game.
 */
export class GrownupSnowballFight final: public BattleCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_XMAS2018_GROWNUPSNOWBALLFIGHT", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 3; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a GrownupSnowballFight object.
     */
    GrownupSnowballFight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class MiosFalseCake
 * @brief Class representing the MiosFalseCake card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The MiosFalseCake class extends both BoostCard and SeasonalCard to represent the card "Mio's False Cake" in the game.
 */
export class MiosFalseCake final: public BoostCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_WINTER2022_FALSECAKE", "CARD_ARTIST_YULAY_DEVLET")
public:
    static constexpr u8 ID = 4; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a MiosFalseCake object.
     */
    MiosFalseCake(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChaoticLaunch
 * @brief Class representing the ChaoticLaunch card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The ChaoticLaunch class extends both EventCard and SeasonalCard to represent the card "Chaotic Launch" in the game.
 */
export class ChaoticLaunch final: public EventCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_LAUNCH", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 5; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ChaoticLaunch object.
     */
    ChaoticLaunch(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChaosRoost
 * @brief Class representing the ChaosRoost card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The ChaosRoost class extends both EventCard and SeasonalCard to represent the card "Chaos Roost" in the game.
 */
export class ChaosRoost final: public EventCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_ROOST", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 6; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ChaosRoost object.
     */
    ChaosRoost(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChaosProtect
 * @brief Class representing the ChaosProtect card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The ChaosProtect class extends both BoostCard and SeasonalCard to represent the card "Chaos Protect" in the game.
 */
export class ChaosProtect final: public BoostCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_PROTECT", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 7; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ChaosProtect object.
     */
    ChaosProtect(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class FromTheChaoticAbyss
 * @brief Class representing the FromTheChaoticAbyss card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The FromTheChaoticAbyss class extends both EventCard and SeasonalCard to represent the card "From the Chaotic Abyss" in the game.
 */
export class FromTheChaoticAbyss final: public EventCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_ABYSS", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 8; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a FromTheChaoticAbyss object.
     */
    FromTheChaoticAbyss(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChaoticRampage
 * @brief Class representing the ChaoticRampage card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The ChaoticRampage class extends both EventCard and SeasonalCard to represent the card "Chaotic Rampage" in the game.
 */
export class ChaoticRampage final: public EventCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_RAMPAGE", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 9; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ChaoticRampage object.
     */
    ChaoticRampage(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChaosRoulette
 * @brief Class representing the ChaosRoulette card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The ChaosRoulette class extends both BoostCard and SeasonalCard to represent the card "Chaos Roulette" in the game.
 */
export class ChaosRoulette final: public BoostCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_ROULETTE", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 10; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ChaosRoulette object.
     */
    ChaosRoulette(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChaoticPool
 * @brief Class representing the ChaoticPool card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The ChaoticPool class extends both EventCard and SeasonalCard to represent the card "Chaotic Pool" in the game.
 */
export class ChaoticPool final: public EventCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_POOL", "CARD_ARTIST_IKUSE")
public:
    static constexpr u8 ID = 11; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ChaoticPool object.
     */
    ChaoticPool(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HoldTheGremlin
 * @brief Class representing the HoldTheGremlin card.
 *
 * @extends GiftCard
 * @extends SeasonalCard
 *
 * The HoldTheGremlin class extends both GiftCard and SeasonalCard to represent the card "Hold the Gremlin" in the game.
 */
export class HoldTheGremlin final: public GiftCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_GIFT_HOTPOTATO", "CARD_ARTIST_HONO")
public:
    static constexpr u8 ID = 12; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a HoldTheGremlin object.
     */
    HoldTheGremlin(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Terrorize
 * @brief Class representing the Terrorize card.
 *
 * @extends GiftCard
 * @extends HyperCard
 * @extends SeasonalCard
 *
 * The Terrorize class extends both GiftCard and SeasonalCard to represent the card "Terrorize" in the game.
 */
export class Terrorize final: public BoostCard, public HyperCard, public SeasonalCard {
private:
    CARD_METADATA("CARD_CHAOS_GIFT_HOTPOTATO", "CARD_CHAOS_BDTT_HYPER")
public:
    static constexpr u8 ID = 13; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Terrorize object.
     */
    Terrorize(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
