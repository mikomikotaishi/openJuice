/**
 * @file Enemy.cppm
 * @module openjuice.engine.unit:Enemy
 * @brief Definition of the Enemy abstract class.
 *
 * This file contains the definition of the Enemy abstract class, which represents an enemy unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit:Enemy;

import stdx;

import :Unit;

using stdx::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @class Enemy
 * @brief Abstract class representing an enemy unit.
 * 
 * @extends Unit
 *
 * The Enemy abstract class extends the Unit abstract class and represents an enemy unit with a specific type.
 */
export class Enemy: public Unit {
public:
    /**
     * @enum Encounter
     * @brief Enumeration for enemy encounter types.
     *
     * The Emcpimter enumeration defines the types of enemies in the game.
     */
    enum class Encounter: u8 {
        BASIC, ///< Basic encounter enemy.
        BOSS, ///< Boss encounter enemy.
    };
private:
    const Encounter encounter; ///< The type of the enemy.
public:
    /**
     * @brief Constructor to initialise an Enemy object.
     *
     * @param Encounter The encounter type of the enemy.
     * @param id The ID of the enemy.
     * @param health The health of the enemy.
     * @param attack The attack value of the enemy.
     * @param defence The defence value of the enemy.
     * @param evade The evade value of the enemy.
     */
    Enemy(Encounter encounter, u16 id, u8 health, i8 attack, i8 defence, i8 evade):
        Unit(id, health, attack, defence, evade), encounter{encounter} {}

    Encounter getEncounter() const noexcept {
        return encounter;
    }
};

END_MODULE_NAMESPACE();
