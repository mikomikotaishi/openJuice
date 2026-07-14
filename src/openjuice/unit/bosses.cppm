/**
 * @file bosses.cppm
 * @module openjuice.unit.bosses
 * @brief Import of all Boss Enemies.
 *
 * This file imports the classes for all Boss Enemies.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.bosses;

import stdx;

import openjuice.engine.unit;

using openjuice::engine::unit::BossEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::bosses);

/**
 * @class FlyingCastle
 * @brief Class representing the FlyingCastle boss enemy.
 * @extends BossEnemy
 *
 * The FlyingCastle class is a final class that inherits from BossEnemy and represents a specific type of boss enemy in the game.
 */
export class FlyingCastle final: public BossEnemy {
private:
    UNIT_METADATA("CARD_UNIT_CASTLE", "CARD_ARTIST_HONO", "")
public:
    static constexpr u16 ID = 1; ///< ID of this specific boss
    static constexpr u8 HEALTH = 10; ///< Health stat of this specific boss
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific boss
    static constexpr i8 DEFENSE = 1; ///< Defense stat of this specific boss
    static constexpr i8 EVADE = -3; ///< Evade stat of this specific boss

    /**
     * @brief Constructor for the FlyingCastle class.
     */
    FlyingCastle():
        SET_BOSS_ENEMY_STATS() {}
};

/**
 * @class ShifuRobot
 * @brief Class representing the ShifuRobot boss enemy.
 * @extends BossEnemy
 *
 * The ShifuRobot class is a final class that inherits from BossEnemy and represents a specific type of boss enemy in the game.
 */
export class ShifuRobot final: public BossEnemy {
private:
    UNIT_METADATA("CARD_UNIT_SHIFUROBOT", "CARD_ARTIST_HONO", "")
public:
    static constexpr u16 ID = 2; ///< ID of this specific boss
    static constexpr u8 HEALTH = 7; ///< Health stat of this specific boss
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific boss
    static constexpr i8 DEFENSE = 3; ///< Defense stat of this specific boss
    static constexpr i8 EVADE = -2; ///< Evade stat of this specific boss

    /**
     * @brief Constructor for the ShifuRobot class.
     */
    ShifuRobot():
        SET_BOSS_ENEMY_STATS() {}
};

/**
 * @class StoreManager
 * @brief Class representing the StoreManager boss enemy.
 * @extends BossEnemy
 *
 * The StoreManager class is a final class that inherits from BossEnemy and represents a specific type of boss enemy in the game.
 */
export class StoreManager final: public BossEnemy {
private:
    UNIT_METADATA("CARD_UNIT_MANAGER", "CARD_ARTIST_HONO", "")
public:
    static constexpr u16 ID = 3; ///< ID of this specific boss
    static constexpr u8 HEALTH = 8; ///< Health stat of this specific boss
    static constexpr i8 ATTACK = 3; ///< Attack stat of this specific boss
    static constexpr i8 DEFENSE = 2; ///< Defense stat of this specific boss
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific boss

    /**
     * @brief Constructor for the StoreManager class.
     */
    StoreManager():
        SET_BOSS_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
