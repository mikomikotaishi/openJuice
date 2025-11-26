/**
 * @file RoboBall.cppm
 * @module openjuice.unit.enemies.RoboBall
 * @brief Implementation of the RoboBall class.
 *
 * This file contains the implementation of the RoboBall class, which represents a basic enemy in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.enemies.RoboBall;

import std;

import openjuice.engine.unit.BasicEnemy;

using openjuice::engine::unit::BasicEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::enemies);

/**
 * @class RoboBall
 * @brief Class representing the RoboBall enemy.
 *
 * @extends BasicEnemy
 *
 * The RoboBall class is a final class that inherits from BasicEnemy and represents a specific type of enemy in the game.
 */
export class RoboBall final: public BasicEnemy {
private:
    static constexpr u16 ID = 2; ///< ID of this specific enemy
    
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific enemy
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific enemy
    static constexpr i8 DEFENCE = 1; ///< Defence stat of this specific enemy
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific enemy

    UNIT_METADATA("CARD_UNIT_ROBOBALL", "CARD_ARTIST_HONO", "");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the RoboBall class.
     */
    RoboBall():
        SET_BASIC_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
