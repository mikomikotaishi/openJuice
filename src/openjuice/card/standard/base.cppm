/**
 * @file base.cppm
 * @module openjuice.card.standard.base
 * @brief Import of cards belonging to the Base Pack.
 *
 * This file imports the classes for cards belonging to the Base Pack.
 */

module;

#include "Macros.hpp"

export module openjuice.card:standard.base;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class Dash
 * @brief Class representing the Dash card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Dash class extends both BoostCard and StandardCard to represent the card "Dash" in the game.
 */
export class Dash final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_DASH", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 1; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 3; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a Dash object.
     */
    Dash():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class SakisCookie
 * @brief Class representing the SakisCookie card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The SakisCookie class extends both BoostCard and StandardCard to represent the card "Saki's Cookie" in the game.
 */
export class SakisCookie final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_COOKIE", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 2; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 3; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a SakisCookie object.
     */
    SakisCookie(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class FlipOut
 * @brief Class representing the FlipOut card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The FlipOut class extends both BoostCard and StandardCard to represent the card "Flip Out" in the game.
 */
export class FlipOut final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_FLIPOUT", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 3; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a FlipOut object.
     */
    FlipOut(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class NiceJingle
 * @brief Class representing the NiceJingle card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The NiceJingle class extends both BoostCard and StandardCard to represent the card "Nice Jingle" in the game.
 */
export class NiceJingle final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_NICEJINGLE", "CARD_ARTIST_MIZUKISEO")
public:
    static constexpr u16 ID = 4; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a NiceJingle object.
     */
    NiceJingle(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class NicePresent
 * @brief Class representing the NicePresent card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The NicePresent class extends both BoostCard and StandardCard to represent the card "Nice Present" in the game.
 */
export class NicePresent final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_NICEPRESENT", "CARD_ARTIST_KITSUNE")
public:
    static constexpr u16 ID = 5; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a NicePresent object.
     */
    NicePresent(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Pudding
 * @brief Class representing the Pudding card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Pudding class extends both BoostCard and StandardCard to represent the card "Pudding" in the game.
 */
export class Pudding final: public BoostCard, public StandardCard {
private:
    CARD_METADATA("CARD_BOOST_PUDDING", "CARD_ARTIST_TAMAKISEO")
public:
    static constexpr u16 ID = 6; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a Pudding object.
     */
    Pudding(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ImOnFire
 * @brief Class representing the ImOnFire card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The ImOnFire class extends both BattleCard and StandardCard to represent the card "I'm on Fire!" in the game.
 */
export class ImOnFire final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_ONFIRE", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 7; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an ImOnFire object.
     */
    ImOnFire(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Rbits
 * @brief Class representing the Rbits card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The Rbits class extends both BattleCard and StandardCard to represent the card "Rbits" in the game.
 */
export class Rbits final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_RBITS", "CARD_ARTIST_MIZUKISEO")
public:
    static constexpr u16 ID = 8; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 3; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an Rbits object.
     */
    Rbits(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class RainbowColoredCircle
 * @brief Class representing the RainbowColoredCircle card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The RainbowColoredCircle class extends both BattleCard and StandardCard to represent the card "Rainbow-Colored Circle" in the game.
 */
export class RainbowColoredCircle final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_RAINBOW", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 9; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a RainbowColoredCircle object.
     */
    RainbowColoredCircle(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class FinalBattle
 * @brief Class representing the FinalBattle card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The FinalBattle class extends both BattleCard and StandardCard to represent the card "Final Battle" in the game.
 */
export class FinalBattle final: public BattleCard, public StandardCard {
private:
    CARD_METADATA("CARD_BATTLE_FINALBATTLE", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 10; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a FinalBattle object.
     */
    FinalBattle():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class BadPudding
 * @brief Class representing the BadPudding card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The BadPudding class extends both TrapCard and StandardCard to represent the card "Bad Pudding" in the game.
 */
export class BadPudding final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_BADPUDDING", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 11; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a BadPudding object.
     */
    BadPudding():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {
        
    }
};

/**
 * @class MimyuusHammer
 * @brief Class representing the MimyuusHammer card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The MimyuusHammer class extends both TrapCard and StandardCard to represent the card "Mimyuu's Hammer" in the game.
 */
export class MimyuusHammer final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_MIMYUU", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 12; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a MimyuusHammer object.
     */
    MimyuusHammer(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class DangerousPudding
 * @brief Class representing the DangerousPudding card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The DangerousPudding class extends both TrapCard and StandardCard to represent the card "Dangerous Pudding" in the game.
 */
export class DangerousPudding final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_DANGEROUSPUDDING", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 13; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a DangerousPudding object.
     */
    DangerousPudding():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Assault
 * @brief Class representing the Assault card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Assault class extends both TrapCard and StandardCard to represent the "Assault" in the game.
 */
export class Assault final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_ASSAULT", "CARD_ARTIST_JUNPYON")
public:
    static constexpr u16 ID = 14; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an Assault object.
     */
    Assault():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {
        
    }
};

/**
 * @class SkyRestaurantPures
 * @brief Class representing the SkyRestaurantPures card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The SkyRestaurantPures class extends both TrapCard and StandardCard to represent the card "Sky Restaurant 'Pures'" in the game.
 */
export class SkyRestaurantPures final: public TrapCard, public StandardCard {
private:
    CARD_METADATA("CARD_TRAP_PURES", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 15; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a SkyRestaurantPures object.
     */
    SkyRestaurantPures(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HereAndThere
 * @brief Class representing the HereAndThere card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The HereAndThere class extends both EventCard and StandardCard to represent the card "Here and There" in the game.
 */
export class HereAndThere final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_HEREANDTHERE", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 16; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a HereAndThere object.
     */
    HereAndThere(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HolyNight
 * @brief Class representing the HolyNight card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The HolyNight class extends both EventCard and StandardCard to represent the card "Holy Night" in the game.
 */
export class HolyNight final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_HOLYNIGHT", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 17; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a HolyNight object.
     */
    HolyNight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class OutOfAmmo
 * @brief Class representing the OutOfAmmo card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The OutOfAmmo class extends both EventCard and StandardCard to represent the card "Out of Ammo" in the game.
 */
export class OutOfAmmo final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_OUTOFAMMO", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 18; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an OutOfAmmo object.
     */
    OutOfAmmo(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GiftExchange
 * @brief Class representing the GiftExchange card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The GiftExchange class extends both EventCard and StandardCard to represent the card "Gift Exchange" in the game.
 */
export class GiftExchange final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_GIFTEXCHANGE", "CARD_ARTIST_TAMAKISEO")
public:
    static constexpr u16 ID = 19; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a GiftExchange object.
     */
    GiftExchange(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class LittleWar
 * @brief Class representing the LittleWar card.
 *
 * @extends EventCard
 * @extends @StandardCard
 *
 * The LittleWar class extends both EventCard and StandardCard to represent the card "Little War" in the game.
 */
export class LittleWar final: public EventCard, public StandardCard {
private:
    CARD_METADATA("CARD_EVENT_LITTLEWAR", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 20; ///< The id of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 50; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a LittleWar object.
     */
    LittleWar():
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
