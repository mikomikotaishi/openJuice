/**
 * @file FlyingCastle.cppm
 * @module openjuice.unit.bosses.FlyingCastle
 * @brief Implementation of the FlyingCastle class.
 *
 * This file contains the implementation of the FlyingCastle class, which represents a boss enemy in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.bosses.FlyingCastle;

import std;

import openjuice.engine.unit.BossEnemy;

using openjuice::engine::unit::BossEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::bosses);

/**
 * @class FlyingCastle
 * @brief Class representing the FlyingCastle boss enemy.
 *
 * @extends BossEnemy
 *
 * The FlyingCastle class is a final class that inherits from BossEnemy and represents a specific type of boss enemy in the game.
 */
export class FlyingCastle final: public BossEnemy {
private:
    static constexpr u16 ID = 1; ///< ID of this specific boss
    
    static constexpr u8 HEALTH = 10; ///< Health stat of this specific boss
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific boss
    static constexpr i8 DEFENCE = 1; ///< Defence stat of this specific boss
    static constexpr i8 EVADE = -3; ///< Evade stat of this specific boss

    UNIT_METADATA("CARD_UNIT_CASTLE", "CARD_ARTIST_HONO", "");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the FlyingCastle class.
     */
    FlyingCastle():
        SET_BOSS_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
