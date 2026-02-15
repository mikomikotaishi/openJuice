/**
 * @file Seagull.cppm
 * @module openjuice.unit.enemies:Seagull
 * @brief Implementation of the Seagull class.
 *
 * This file contains the implementation of the Seagull class, which represents a basic enemy in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.enemies:Seagull;

import stdx;

import openjuice.engine.unit;

using openjuice::engine::unit::BasicEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::enemies);

/**
 * @class Seagull
 * @brief Class representing the Seagull enemy.
 *
 * @extends BasicEnemy
 *
 * The Seagull class is a final class that inherits from BasicEnemy and represents a specific type of enemy in the game.
 */
export class Seagull final: public BasicEnemy {
public:
    static constexpr u16 ID = 3; ///< ID of this specific enemy
private:
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific enemy
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific enemy
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific enemy
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific enemy

    UNIT_METADATA("CARD_UNIT_SEAGULL", "CARD_ARTIST_HONO", "");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Seagull class.
     */
    Seagull():
        SET_BASIC_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
