/**
 * @file acceleration.cppm
 * @module openjuice.card.standard.acceleration
 * @brief Import of cards belonging to the Acceleration Pack.
 *
 * This file imports the modules for cards belonging to the Acceleration Pack.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.acceleration;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class CompletionReward
 * @brief Class representing the CompletionReward card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The CompletionReward class extends both BoostCard and StandardCard to represent the card "Completion Reward" in the game.
 */
export class CompletionReward final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_COMPLETIONREWARD", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 54; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a CompletionReward object.
     */
    CompletionReward(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GentlemansBattle
 * @brief Class representing the GentlemansBattle card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The GentlemansBattle class extends both BoostCard and StandardCard to represent the card "Gentleman's Battle" in the game.
 */
export class GentlemansBattle final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_GENTLEMANSBATTLE", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 55; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a GentlemansBattle object.
     */
    GentlemansBattle(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class AccelHyper
 * @brief Class representing the AccelHyper card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The AccelHyper class extends both BattleCard and StandardCard to represent the card "Accel Hyper" in the game.
 */
export class AccelHyper final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_ACCELHYPER", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 56; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a AccelHyper object.
     */
    AccelHyper(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Extension
 * @brief Class representing the Extension card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The Extension class extends both BattleCard and StandardCard to represent the card "Extension" in the game.
 */
export class Extension final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_EXTENSION", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 57; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Extension object.
     */
    Extension(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class QuickRestoration
 * @brief Class representing the QuickRestoration card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The QuickRestoration class extends both BattleCard and StandardCard to represent the card "Quick Restoration" in the game.
 */
export class QuickRestoration final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_QUICKRESTORATION", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 58; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a QuickRestoration object.
     */
    QuickRestoration(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class BrutalPrank
 * @brief Class representing the BrutalPrank card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The BrutalPrank class extends both TrapCard and StandardCard to represent the card "Brutal Prank" in the game.
 */
export class BrutalPrank final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_BRUTALPRANK", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 59; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a BrutalPrank object.
     */
    BrutalPrank(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PresentThief
 * @brief Class representing the PresentThief card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The PresentThief class extends both TrapCard and StandardCard to represent the card "Present Thief" in the game.
 */
export class PresentThief final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_PRESENTTHIEF", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 60; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a PresentThief object.
     */
    PresentThief(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PlayOfTheGods
 * @brief Class representing the PlayOfTheGods card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The PlayOfTheGods class extends both EventCard and StandardCard to represent the card "Play of the Gods" in the game.
 */
export class PlayOfTheGods final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_PLAYOFTHEGODS", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 61; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a PlayOfTheGods object.
     */
    PlayOfTheGods(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ScrambledEve
 * @brief Class representing the ScrambledEve card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The ScrambledEve class extends both EventCard and StandardCard to represent the card "Scrambled Eve" in the game.
 */
export class ScrambledEve final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_SCRAMBLEDEVE", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 62; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ScrambledEve object.
     */
    ScrambledEve(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class StarBlastingLight
 * @brief Class representing the StarBlastingLight card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The StarBlastingLight class extends both EventCard and StandardCard to represent the card "Star-Blasting Light" in the game.
 */
export class StarBlastingLight final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_STARBLAZINGLIGHT", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 63; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 50; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a StarBlastingLight object.
     */
    StarBlastingLight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class UnluckyCharm
 * @brief Class representing the UnluckyCharm card.
 *
 * @extends GiftCard
 * @extends StandardCard
 *
 * The UnluckyCharm class extends both GiftCard and StandardCard to represent the card "Unlucky Charm" in the game.
 */
export class UnluckyCharm final: public GiftCard, public StandardCard {
private:
    CARD_METADATA("CARD_GIFT_UNLUCKYCHARM", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 64; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = nullopt; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a UnluckyCharm object.
     */
    UnluckyCharm():
        SET_CARD_STATS() {}

    /**
      * @brief Play the card.
      */
    void play() const noexcept override final {

    }
};

/**
 * @class WindyEnchantment
 * @brief Class representing the WindyEnchantment card.
 *
 * @extends GiftCard
 * @extends StandardCard
 *
 * The WindyEnchantment class extends both GiftCard and StandardCard to represent the card "Windy Enchantment" in the game.
 */
export class WindyEnchantment final: public GiftCard, public StandardCard {
private:
    CARD_METADATA("CARD_GIFT_WINDYENCHANTMENT", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 65; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a WindyEnchantment object.
     */
    WindyEnchantment(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
