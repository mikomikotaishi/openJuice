/**
 * @file mixedbooster.cppm
 * @module openjuice.card.standard.mixedbooster
 * @brief Import of cards belonging to the Mixed Booster Pack.
 *
 * This file imports the modules for cards belonging to the Mixed Booster Pack.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.mixedbooster;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::mixedbooster);

/**
 * @class LonelyChariot
 * @brief Class representing the LonelyChariot card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The LonelyChariot class extends both BoostCard and StandardCard to represent the card "Lonely Chariot" in the game.
 */
export class LonelyChariot final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_LONELYCHARIOT", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 43; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a LonelyChariot object.
     */
    LonelyChariot(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Ambush
 * @brief Class representing the Ambush card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Ambush class extends both BoostCard and StandardCard to represent the card "Ambush" in the game.
 */
export class Ambush final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_AMBUSH", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 44; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a Ambush object.
     */
    Ambush(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PassionateResearch
 * @brief Class representing the PassionateResearch card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The PassionateResearch class extends both BoostCard and StandardCard to represent the card "Passionate Research" in the game.
 */
export class PassionateResearch final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_PASSIONATE", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 45; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a PassionateResearch object.
     */
    PassionateResearch(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PresidentsPrivilege
 * @brief Class representing the PresidentsPrivilege card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The PresidentsPrivilege class extends both BoostCard and StandardCard to represent the card "President's Privilege" in the game.
 */
export class PresidentsPrivilege final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_PRESIDENT", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 46; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a PresidentsPrivilege object.
     */
    PresidentsPrivilege(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Mimic
 * @brief Class representing the Mimic card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Mimic class extends both BoostCard and StandardCard to represent the card "Mimic" in the game.
 */
export class Mimic final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_MIMIC", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 47; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a Mimic object.
     */
    Mimic(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class TacticalRetreat
 * @brief Class representing the TacticalRetreat card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The TacticalRetreat class extends both BattleCard and StandardCard to represent the card "Tactical Retreat" in the game.
 */
export class TacticalRetreat final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_RETREAT", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 48; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = nullopt; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a TacticalRetreat object.
     */
    TacticalRetreat():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ShieldCounter
 * @brief Class representing the ShieldCounter card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The ShieldCounter class extends both BattleCard and StandardCard to represent the card "Shield Counter" in the game.
 */
export class ShieldCounter final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_SHIELDCOUNTER", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 49; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a ShieldCounter object.
     */
    ShieldCounter(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PiyopiyoProcession
 * @brief Class representing the PiyopiyoProcession card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The PiyopiyoProcession class extends both TrapCard and StandardCard to represent the card "Piyopiyo Procession" in the game.
 */
export class PiyopiyoProcession final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_PIYOPIYO", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 50; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a PiyopiyoProcession object.
     */
    PiyopiyoProcession(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SealedMemories
 * @brief Class representing the SealedMemories card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The SealedMemories class extends both TrapCard and StandardCard to represent the card "Sealed Memories" in the game.
 */
export class SealedMemories final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_SEALEDMEMORIES", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 51; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a SealedMemories object.
     */
    SealedMemories(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class MixPhenomenon
 * @brief Class representing the MixPhenomenon card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The MixPhenomenon class extends both EventCard and StandardCard to represent the card "Mix Phenomenon" in the game.
 */
export class MixPhenomenon final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_MIXPHENOMENON", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 52; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a MixPhenomenon object.
     */
    MixPhenomenon(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ScarySolicitation
 * @brief Class representing the ScarySolicitation card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The ScarySolicitation class extends both EventCard and StandardCard to represent the card "Scary Solicitation" in the game.
 */
export class ScarySolicitation final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_SOLICITATION", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 53; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a ScarySolicitation object.
     */
    ScarySolicitation(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
