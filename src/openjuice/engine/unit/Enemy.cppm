/**
 * @file Enemy.cppm
 * @module openjuice.engine.unit.Enemy
 * @brief Definition of the Enemy abstract class.
 *
 * This file contains the definition of the Enemy abstract class, which represents an enemy unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit.Enemy;

import std;

import openjuice.engine.unit.Unit;

using std::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @enum EnemyType
 * @brief Enumeration for enemy types.
 *
 * @extends Unit
 * 
 * The EnemyType enumeration defines the types of enemies in the game.
 */
export enum class EnemyType: u8 {
    BASIC_ENCOUNTER, ///< Basic encounter enemy.
    BOSS_ENCOUNTER ///< Boss encounter enemy.
};

/**
 * @class Enemy
 * @brief Abstract class representing an enemy unit.
 * 
 * @extends Unit
 *
 * The Enemy abstract class extends the Unit abstract class and represents an enemy unit with a specific type.
 */
export class Enemy: public Unit {
private:
    const EnemyType type; ///< The type of the enemy.
public:
    /**
     * @brief Constructor to initialise an Enemy object.
     *
     * @param enemyType The type of the enemy.
     * @param id The ID of the enemy.
     * @param health The health of the enemy.
     * @param attack The attack value of the enemy.
     * @param defence The defence value of the enemy.
     * @param evade The evade value of the enemy.
     */
    Enemy(EnemyType enemyType, u16 id, u8 health, i8 attack, i8 defence, i8 evade):
        Unit(id, health, attack, defence, evade), type{enemyType} {}

    GETTER(EnemyType, Type, type);
};

/**
 * @concept ExtendsEnemy
 * @brief Concept that checks if a type extends the Enemy class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsEnemy = IsBaseOfValue<Enemy, T>;

END_MODULE_NAMESPACE();
