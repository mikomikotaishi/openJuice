/**
 * @file StoreManager.cppm
 * @module openjuice.unit.bosses.StoreManager
 * @brief Implementation of the StoreManager class.
 *
 * This file contains the implementation of the StoreManager class, which represents a boss enemy in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.bosses.StoreManager;

import std;

import openjuice.engine.unit.BossEnemy;

using openjuice::engine::unit::BossEnemy;

BEGIN_MODULE_NAMESPACE(openjuice::unit::bosses);

/**
 * @class StoreManager
 * @brief Class representing the StoreManager boss enemy.
 *
 * @extends BossEnemy
 *
 * The StoreManager class is a final class that inherits from BossEnemy and represents a specific type of boss enemy in the game.
 */
export class StoreManager final: public BossEnemy {
private:
    static constexpr u16 ID = 3; ///< ID of this specific boss
    
    static constexpr u8 HEALTH = 8; ///< Health stat of this specific boss
    static constexpr i8 ATTACK = 3; ///< Attack stat of this specific boss
    static constexpr i8 DEFENCE = 2; ///< Defence stat of this specific boss
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific boss

    UNIT_METADATA("CARD_UNIT_MANAGER", "CARD_ARTIST_HONO", "");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the StoreManager class.
     */
    StoreManager():
        SET_BOSS_ENEMY_STATS() {}
};

END_MODULE_NAMESPACE();
