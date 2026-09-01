/**
 * @file enemies.cppm
 * @module openjuice.unit.enemies
 * @brief Import of all Basic Enemies.
 *
 * This file imports the classes for all Basic Enemies.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.enemies;

import stdx;

import openjuice.engine.unit;

using openjuice::engine::unit::BasicEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::enemies);

/**
 * @class Chicken
 * @brief Class representing the Chicken enemy.
 * @extends BasicEnemy
 *
 * The Chicken class is a final class that inherits from BasicEnemy and represents a specific type of enemy in the game.
 */
export class Chicken final: public BasicEnemy {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_CHICKEN",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "",
    };
public:
    static constexpr u16 ID = 1; ///< ID of this specific enemy
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific enemy
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific enemy
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific enemy
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific enemy

    /**
     * @brief Constructor for the Chicken class.
     */
    Chicken():
        SET_BASIC_ENEMY_STATS() {}
};

/**
 * @class RoboBall
 * @brief Class representing the RoboBall enemy.
 * @extends BasicEnemy
 *
 * The RoboBall class is a final class that inherits from BasicEnemy and represents a specific type of enemy in the game.
 */
export class RoboBall final: public BasicEnemy {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_ROBOBALL",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "",
    };
public:
    static constexpr u16 ID = 2; ///< ID of this specific enemy
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific enemy
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific enemy
    static constexpr i8 DEFENSE = 1; ///< Defense stat of this specific enemy
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific enemy

    /**
     * @brief Constructor for the RoboBall class.
     */
    RoboBall():
        SET_BASIC_ENEMY_STATS() {}
};

/**
 * @class Seagull
 * @brief Class representing the Seagull enemy.
 * @extends BasicEnemy
 *
 * The Seagull class is a final class that inherits from BasicEnemy and represents a specific type of enemy in the game.
 */
export class Seagull final: public BasicEnemy {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_SEAGULL",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "",
    };
public:
    static constexpr u16 ID = 3; ///< ID of this specific enemy
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific enemy
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific enemy
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific enemy
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific enemy

    /**
     * @brief Constructor for the Seagull class.
     */
    Seagull():
        SET_BASIC_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
