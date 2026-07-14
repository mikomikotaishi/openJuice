/**
 * @file expansion.cppm
 * @module openjuice.card.standard.expansion
 * @brief Import of cards belonging to the Expansion Pack.
 *
 * This file imports the modules for cards belonging to the Expansion Pack.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.expansion;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class LongDistanceShot
 * @brief Class representing the LongDistanceShot card.
 * @extends BoostCard
 * @extends StandardCard
 *
 * The LongDistanceShot class extends both BoostCard and StandardCard to represent the card "Long-Distance Shot" in the game.
 */
export class LongDistanceShot final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_LONGSHOT", "CARD_ARTIST_YUUNANASE")
public:
    static constexpr u16 ID = 21; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a LongDistanceShot object.
     */
    LongDistanceShot(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class StiffCrystal
 * @brief Class representing the StiffCrystal card.
 * @extends BoostCard
 * @extends StandardCard
 *
 * The StiffCrystal class extends both BoostCard and StandardCard to represent the card "Stiff Crystal" in the game.
 */
export class StiffCrystal final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_STIFFCRYSTAL", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 22; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a StiffCrystal object.
     */
    StiffCrystal(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Extend
 * @brief Class representing the Extend card.
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Extend class extends both BoostCard and StandardCard to represent the card "Extend" in the game.
 */
export class Extend final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_EXTEND", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 23; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Extend object.
     */
    Extend(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PrincesssPrivilege
 * @brief Class representing the PrincesssPrivilege card.
 * @extends BoostCard
 * @extends StandardCard
 *
 * The PrincesssPrivilege class extends both BoostCard and StandardCard to represent the card "Princess's Privilege" in the game.
 */
export class PrincesssPrivilege final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_PRINCESS", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 24; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a PrincesssPrivilege object.
     */
    PrincesssPrivilege(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class BigMagnum
 * @brief Class representing the BigMagnum card.
 * @extends BattleCard
 * @extends StandardCard
 *
 * The BigMagnum class extends both BattleCard and StandardCard to represent the card "Big Magnum" in the game.
 */
export class BigMagnum final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_BIGMAGNUM", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 25; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a BigMagnum object.
     */
    BigMagnum(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Shield
 * @brief Class representing the Shield card.
 * @extends BattleCard
 * @extends StandardCard
 *
 * The Shield class extends both BattleCard and StandardCard to represent the card "Shield" in the game.
 */
export class Shield final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_SHIELD", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 26; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Shield object.
     */
    Shield(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ReverseAttributeField
 * @brief Class representing the ReverseAttributeField card.
 * @extends BattleCard
 * @extends StandardCard
 *
 * The ReverseAttributeField class extends both BattleCard and StandardCard to represent the card "Reverse Attribute Field" in the game.
 */
export class ReverseAttributeField final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_REVERSE", "CARD_ARTIST_KITSUNE")
public:
    static constexpr u16 ID = 27; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ReverseAttributeField object.
     */
    ReverseAttributeField(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PiggyBank
 * @brief Class representing the PiggyBank card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The PiggyBank class extends both TrapCard and StandardCard to represent the card "Piggy Bank" in the game.
 */
export class PiggyBank final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_PIGGYBANK", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 28; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a PiggyBank object.
     */
    PiggyBank(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Invasion
 * @brief Class representing the Invasion card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Invasion class extends both TrapCard and StandardCard to represent the card "Invasion" in the game.
 */
export class Invasion final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_INVASION", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 29; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Invasion object.
     */
    Invasion(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GoAway
 * @brief Class representing the GoAway card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The GoAway class extends both TrapCard and StandardCard to represent the card "Go Away" in the game.
 */
export class GoAway final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_GOAWAY", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 30; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a GoAway object.
     */
    GoAway(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Heat300
 * @brief Class representing the Heat300 card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Heat300 class extends both TrapCard and StandardCard to represent the card "Heat 300%" in the game.
 */
export class Heat300 final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_HEAT300", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 31; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Heat300 object.
     */
    Heat300(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class TragedyInTheDeadOfNight
 * @brief Class representing the TragedyInTheDeadOfNight card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The TragedyInTheDeadOfNight class extends both TrapCard and StandardCard to represent the card "Tragedy in the Dead of Night" in the game.
 */
export class TragedyInTheDeadOfNight final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_TRAGEDY", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 32; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a TragedyInTheDeadOfNight object.
     */
    TragedyInTheDeadOfNight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Exchange
 * @brief Class representing the Exchange card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Exchange class extends both TrapCard and StandardCard to represent the card "Exchange" in the game.
 */
export class Exchange final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_EXCHANGE", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 33; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Exchange object.
     */
    Exchange(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Flamethrower
 * @brief Class representing the Flamethrower card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Flamethrower class extends both TrapCard and StandardCard to represent the card "Flamethrower" in the game.
 */
export class Flamethrower final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_FLAMETHROWER", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 34; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Flamethrower object.
     */
    Flamethrower(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ForTheFutureOfTheToyStore
 * @brief Class representing the ForTheFutureOfTheToyStore card.
 * @extends TrapCard
 * @extends StandardCard
 *
 * The ForTheFutureOfTheToyStore class extends both TrapCard and StandardCard to represent the card "For the Future of the Toy Store" in the game.
 */
export class ForTheFutureOfTheToyStore final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_TOYSTORE", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 35; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ForTheFutureOfTheToyStore object.
     */
    ForTheFutureOfTheToyStore(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class CloudOfSeagulls
 * @brief Class representing the CloudOfSeagulls card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The CloudOfSeagulls class extends both EventCard and StandardCard to represent the card "Cloud of Seagulls" in the game.
 */
export class CloudOfSeagulls final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_SEAGULLS", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 36; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a CloudOfSeagulls object.
     */
    CloudOfSeagulls(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class WeAreWaruda
 * @brief Class representing the WeAreWaruda card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The WeAreWaruda class extends both EventCard and StandardCard to represent the card "We Are Waruda" in the game.
 */
export class WeAreWaruda final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_WARUDA", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 37; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a WeAreWaruda object.
     */
    WeAreWaruda(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Dinner
 * @brief Class representing the Dinner card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The Dinner class extends both EventCard and StandardCard to represent the card "Dinner" in the game.
 */
export class Dinner final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_DINNER", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 38; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a Dinner object.
     */
    Dinner(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SuperAllOutMode
 * @brief Class representing the SuperAllOutMode card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The SuperAllOutMode class extends both EventCard and StandardCard to represent the card "Super All-Out Mode" in the game.
 */
export class SuperAllOutMode final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_ALLOUTMODE", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 39; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SuperAllOutMode object.
     */
    SuperAllOutMode(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

// TODO: Implement co-op stats

/**
 * @class ForcedRevival
 * @brief Class representing the ForcedRevival card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The ForcedRevival class extends both EventCard and StandardCard to represent the card "Forced Revival" in the game.
 */
export class ForcedRevival final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_FORCEDREVIVAL", "CARD_ARTIST_KITSUNE")
public:
    static constexpr u16 ID = 40; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a ForcedRevival object.
     */
    ForcedRevival(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class OhMyFriend
 * @brief Class representing the OhMyFriend card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The OhMyFriend class extends both EventCard and StandardCard to represent the card "Oh My Friend" in the game.
 */
export class OhMyFriend final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_OHMYFRIEND", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 41; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card
    /**
     * @brief Constructor to initialize a OhMyFriend object.
     */
    OhMyFriend(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SealedGuardian
 * @brief Class representing the SealedGuardian card.
 * @extends EventCard
 * @extends StandardCard
 *
 * The SealedGuardian class extends both EventCard and StandardCard to represent the card "Sealed Guardian" in the game.
 */
export class SealedGuardian final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_LONGSHOT", "CARD_ARTIST_YUUNANASE")
public:
    static constexpr u16 ID = 42; ///< The id of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialize a SealedGuardian object.
     */
    SealedGuardian(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
