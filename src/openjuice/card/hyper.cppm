/**
 * @file hyper.cppm
 * @module openjuice.card.hyper
 * @brief Import of all Hyper Cards.
 *
 * This file imports the modules for all Hyper Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:hyper;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class ProtagonistsPrivilege
 * @brief Class representing the ProtagonistsPrivilege card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The ProtagonistsPrivilege class extends both BoostCard and HyperCard to represent the card "Protagonist's Privilege" in the game.
 */
export class ProtagonistsPrivilege final: public BoostCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_KAI", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 1; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a ProtagonistsPrivilege object.
     */
    ProtagonistsPrivilege():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class X16BigRocket
 * @brief Class representing the X16BigRocket card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The X16BigRocket class extends both BoostCard and HyperCard to represent the card "x16 Big Rocket" in the game.
 */
export class X16BigRocket final: public BoostCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_MARC", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 2; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = nullopt; ///< The cost of this specific card (deduct level * 10 stars from player)
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an X16BigRocket object.
     */
    X16BigRocket():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HyperMode
 * @brief Class representing the HyperMode card.
 *
 * @extends BattleCard
 * @extends HyperCard
 *
 * The HyperMode class extends both BattleCard and HyperCard to represent the card "Hyper Mode" in the game.
 */
export class HyperMode final: public BattleCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_QP", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 3; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a HyperMode object.
     */
    HyperMode():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Accelerator
 * @brief Class representing the Accelerator card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The Accelerator class extends both BoostCard and HyperCard to represent the card "Accelerator" in the game.
 */
export class Accelerator final: public BoostCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_SUGURI", "CARD_ARTIST_MIZUKISEO")
public:
    static constexpr u16 ID = 4; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an Accelerator object.
     */
    Accelerator():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class PresentForYou
 * @brief Class representing the PresentForYou card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The PresentForYou class extends both EventCard and HyperCard to represent the card "Present for You" in the game.
 */
export class PresentForYou final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_ARU", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 5; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a PresentForYou object.
     */
    PresentForYou():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class AirStrike
 * @brief Class representing the AirStrike card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The AirStrike class extends both EventCard and HyperCard to represent the card "Air Strike" in the game.
 */
export class AirStrike final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_FERNET", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 6; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a AirStrike object.
     */
    AirStrike():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class BindingChains
 * @brief Class representing the BindingChains card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The BindingChains class extends both EventCard and HyperCard to represent the card "Binding Chains" in the game.
 */
export class BindingChains final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_HIME", "CARD_ARTIST_TORI")
public:
    static constexpr u16 ID = 7; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a BindingChains object.
     */
    BindingChains():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Ubiquitous
 * @brief Class representing the Ubiquitous card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The Ubiquitous class extends both BoostCard and HyperCard to represent the card "Ubiquitous" in the game.
 */
export class Ubiquitous final: public BoostCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_POPPO", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 8; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise an Ubiquitous object.
     */
    Ubiquitous():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class MagicalInferno
 * @brief Class representing the MagicalInferno card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The MagicalInferno class extends both EventCard and HyperCard to represent the card "Magical Inferno" in the game.
 */
export class MagicalInferno final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_MIO", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 9; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 50; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a MagicalInferno object.
     */
    MagicalInferno():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ChristmasInferno
 * @brief Class representing the ChristmasInferno card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The ChristmasInferno class extends both EventCard and HyperCard to represent the card "Christmas Inferno" in the game.
 */
export class ChristmasInferno final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_MIOFESTIVE", "CARD_ARTIST_SENCA")
public:
    static constexpr u16 ID = 10; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a ChristmasInferno object.
     */
    ChristmasInferno():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class BlueCrowTheSecond
 * @brief Class representing the BlueCrowTheSecond card.
 *
 * @extends BattleCard
 * @extends HyperCard
 *
 * The BlueCrowTheSecond class extends both BattleCard and HyperCard to represent the card "Blue Crow the Second" in the game.
 */
export class BlueCrowTheSecond final: public BattleCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_PEAT", "CARD_ARTIST_HONO")
public:
    static constexpr u16 ID = 11; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a BlueCrowTheSecond object.
     */
    BlueCrowTheSecond():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ExtraordinarySpecs
 * @brief Class representing the ExtraordinarySpecs card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The ExtraordinarySpecs class extends both BoostCard and HyperCard to represent the card "Extraordinary Specs" in the game.
 */
export class ExtraordinarySpecs final: public BoostCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_SORA", "CARD_ARTIST_ERINA")
public:
    static constexpr u16 ID = 12; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a ExtraordinarySpecs object.
     */
    ExtraordinarySpecs():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class MagicalMassacre
 * @brief Class representing the MagicalMassacre card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The MagicalMassacre class extends both EventCard and HyperCard to represent the card "Magical Massacre" in the game.
 */
export class MagicalMassacre final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_TOMOMO", "CARD_ARTIST_MEGANE")
public:
    static constexpr u16 ID = 13; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a MagicalMassacre object.
     */
    MagicalMassacre():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Gamble
 * @brief Class representing the Gamble card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The Gamble class extends both EventCard and HyperCard to represent the card "Gamble!" in the game.
 */
export class Gamble final: public EventCard, public HyperCard {
private:
    CARD_METADATA("CARD_HYPER_YUKI", "CARD_ARTIST_NERIUME")
public:
    static constexpr u16 ID = 14; ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 13; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a Gamble object.
     */
    Gamble():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

// GoldenEgg; // 15
// ReflectiveShell; // 16
// JonathanRush; // 17
// BannedForLife; // 18
// TurboCharged; // 19
// ImmovableObject; // 20
// BeyondHell; // 21
// DeployBits; // 22
// SweetGuardian; // 23
// BigBangBell; // 24
// CastOff; // 25
// PlushieMaster; // 26
// Blazing; // 27
// SelfDestruct; // 28
// CrystalBarrier; // 29
// SubspaceTunnel; // 30
// DeltaField; // 31
// WhimsicalWindmill; // 32
// AwakeningOfTalent; // 33
// StarBlastingFuse; // 34
// MeltingMemories; // 35
// SantasJob; // 36
// AnotherUltimateWeapon; // 37
// EvilSpyWorkPreparation; // 38
// WarudaMachineBlastOff; // 39
// FinalSurgery; // 40
// Overseer; // 41
// WitchsHairLock; // 43
// SolidWitch; // 44
// EvilMastermind; // 45
// MiracleRedBeanIceCream; // 46
// MagicalRevenge; // 47
// RevivalOfStars; // 48
// StealthOn; // 49
// DoPiratesFlyInTheSky; // 50
// WhiteChristmasher; // 51
// CookingTime; // 52
// MiracleWalker; // 53
// BranchExplosionStrategy; // 54
// ExtendedPhotonRifle; // 55
// LeapThroughSpaceMarking; // 56
// SpecialStage; // 57
// YuukiHand; // 58
// Rival; // 59
// ObserverOfEternity; // 60
// ReproductionOfRecords; // 61
// ElliesMiracle; // 62
// LulusLuckyEgg; // 63
// RocketCannon; // 64
// FullSpeedAlicianrone; // 65
// BeastWitch; // 66
// IntelligenceOfficer; // 67
// RagingMadness; // 68
// SaintEyes; // 69
// ChefICouldUseSomeHelp; // 70
// SafeJourney; // 71
// GuidanceOfTheWeathercock; // 72
// Upshift; // 73
// ZealousSalesman; // 74
// DanceInTheMoonlitNight; // 75
// NewNobility; // 76
// TwilightColoredDream; // 77
// LittleMagnum; // 78
// IdealWorld; // 79
// StarCollector; // 80
// TorrentOfMagic; // 81
// GoodestBoy; // 82
// SweetParadise; // 83
// SweetMakersMagic; // 84
// OperationAMountainOfSweets; // 85
// ThreatsToMySlumber; // 86
// MakeBelievePrisonBreak; // 87
// MotherPower; // 88
// LuluIsAnUnluckyDragon; // 89
// ElliesHyperMiracle; // 90
// ExProtagonistsMomentOfGlory; // 91
// AllGunsAtTheReady; // 92
// HeartOfResistance; // 93
// SuperYouthTime; // 94
// IllGetALittleIntoIt; // 95
// HypeBringer; // 96
// IntellectualSoundingBluff; // 97
// PreciseDiceRolls; // 98
// BecauseImATeacher; // 99
// HardworkingGyaruStudentCouncilPresident; // 100
// DanceLongHairedBeasts; // 1026
// InvisibleBomb; // 1034
// EvilSpyWorkExecution; // 1038
// FlyingPirate; // 1050
// TrueWhiteChristmasher; // 1051
// RbitHobbyShop; // 1054
// LeapThroughSpace; // 1056
// AngelHand; // 1058
// DevilHand; // 1059
// BigRocketCannon; // 1064
// ManagerICouldUseSomeHelp; // 1070
// Affluence; // 1076
// SweetIndulgence; // 1083
// WhenMySlumberBreaks; // 1086

END_MODULE_NAMESPACE();
