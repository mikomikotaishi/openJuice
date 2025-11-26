/**
 * @file ShifuRobot.cppm
 * @module openjuice.unit.bosses.ShifuRobot
 * @brief Implementation of the ShifuRobot class.
 *
 * This file contains the implementation of the ShifuRobot class, which represents a boss enemy in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.bosses.ShifuRobot;

import std;

import openjuice.engine.unit.BossEnemy;

using openjuice::engine::unit::BossEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::bosses);

/**
 * @class ShifuRobot
 * @brief Class representing the ShifuRobot boss enemy.
 *
 * @extends BossEnemy
 *
 * The ShifuRobot class is a final class that inherits from BossEnemy and represents a specific type of boss enemy in the game.
 */
export class ShifuRobot final: public BossEnemy {
private:
    static constexpr u16 ID = 2; ///< ID of this specific boss
    
    static constexpr u8 HEALTH = 7; ///< Health stat of this specific boss
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific boss
    static constexpr i8 DEFENCE = 3; ///< Defence stat of this specific boss
    static constexpr i8 EVADE = -2; ///< Evade stat of this specific boss

    UNIT_METADATA("CARD_UNIT_SHIFUROBOT", "CARD_ARTIST_HONO", "");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the ShifuRobot class.
     */
    ShifuRobot():
        SET_BOSS_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
