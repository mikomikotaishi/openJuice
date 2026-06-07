/**
 * @file battle.cppm
 * @module openjuice.card.mushroom.regular.battle
 * @brief Import of all Battle Mushroom Cards.
 *
 * This file imports the modules for all Battle Mushroom Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:mushroom.regular.battle;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class NullBattleMushroom
 * @brief Class representing the NullBattleMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The NullBattleMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::NULL_BATTLE effect in the game.
 */
export class NullBattleMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::NULL_BATTLE); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a NullBattleMushroom object.
     */
    NullBattleMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, NULL_BATTLE) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class AttackUpMushroom
 * @brief Class representing the AttackUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The AttackUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::ATTACK_UP effect in the game.
 */
export class AttackUpMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ATTACKUP")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::ATTACK_UP); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a AttackUpMushroom object.
     */
    AttackUpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, ATTACK_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class AttackDownMushroom
 * @brief Class representing the AttackDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The AttackDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::ATTACK_DOWN effect in the game.
 */
export class AttackDownMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ATTACKDOWN")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::ATTACK_DOWN); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a AttackDownMushroom object.
     */
    AttackDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, ATTACK_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class DefenceUpMushroom
 * @brief Class representing the DefenceUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DefenceUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::DEFENCE_UP effect in the game.
 */
export class DefenceUpMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DEFENSEUP")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::DEFENCE_UP); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a DefenceUpMushroom object.
     */
    DefenceUpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, DEFENCE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class DefenceDownMushroom
 * @brief Class representing the DefenceDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DefenceDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::DEFENCE_DOWN effect in the game.
 */
export class DefenceDownMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DEFENSEDOWN")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::DEFENCE_DOWN); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a DefenceDownMushroom object.
     */
    DefenceDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, DEFENCE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class EvadeUpMushroom
 * @brief Class representing the EvadeUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The EvadeUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::EVADE_UP effect in the game.
 */
export class EvadeUpMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_EVADEUP")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::EVADE_UP); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a EvadeUpMushroom object.
     */
    EvadeUpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, EVADE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class EvadeDownMushroom
 * @brief Class representing the EvadeDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The EvadeDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::EVADE_DOWN effect in the game.
 */
export class EvadeDownMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_EVADEDOWN")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::EVADE_DOWN); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a EvadeDownMushroom object.
     */
    EvadeDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, EVADE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HealMushroom
 * @brief Class representing the HealMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The HealMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::HEAL effect in the game.
 */
export class HealMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_HEAL")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::HEAL); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a HealMushroom object.
     */
    HealMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, HEAL) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class DamageMushroom
 * @brief Class representing the DamageMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The DamageMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::DAMAGE effect in the game.
 */
export class DamageMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DAMAGE")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::DAMAGE); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a DamageMushroom object.
     */
    DamageMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, DAMAGE) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class RollOneMushroom
 * @brief Class representing the RollOneMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The RollOneMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::ROLL_ONE effect in the game.
 */
export class RollOneMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ROLLONE")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::ROLL_ONE); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a RollOneMushroom object.
     */
    RollOneMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, ROLL_ONE) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class RollSixMushroom
 * @brief Class representing the RollSixMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The RollSixMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::ROLL_SIX effect in the game.
 */
export class RollSixMushroom final: public BattleMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_ROLLSIX")
public:
    static constexpr u16 ID = Ops::to_underlying(BattleMushroomCard::Effect::ROLL_SIX); ///< The ID of this specific card
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a RollSixMushroom object.
     */
    RollSixMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, ROLL_SIX) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
