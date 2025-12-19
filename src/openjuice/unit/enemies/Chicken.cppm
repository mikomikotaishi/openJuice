/**
 * @file Chicken.cppm
 * @module openjuice.unit.enemies.Chicken
 * @brief Implementation of the Chicken class.
 *
 * This file contains the implementation of the Chicken class, which represents a basic enemy in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.enemies.Chicken;

import std;

import openjuice.engine.unit.BasicEnemy;

using openjuice::engine::unit::BasicEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::enemies);

/**
 * @class Chicken
 * @brief Class representing the Chicken enemy.
 *
 * @extends BasicEnemy
 *
 * The Chicken class is a final class that inherits from BasicEnemy and represents a specific type of enemy in the game.
 */
export class Chicken final: public BasicEnemy {
public:
    static constexpr u16 ID = 1; ///< ID of this specific enemy
private:
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific enemy
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific enemy
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific enemy
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific enemy

    UNIT_METADATA("CARD_UNIT_CHICKEN", "CARD_ARTIST_HONO", "");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Chicken class.
     */
    Chicken():
        SET_BASIC_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
