/**
 * @file BasicEnemy.cppm
 * @module openjuice.engine.unit:BasicEnemy
 * @brief Definition of the BasicEnemy interface.
 *
 * This file contains the structure of the BasicEnemy interface, which represents a basic enemy unit.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit:BasicEnemy;

import stdx;

import :Enemy;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @interface BasicEnemy
 * @brief Interface representing a basic enemy unit.
 * @extends Enemy
 * 
 * The BasicEnemy interface extends the Enemy interface and represents a basic enemy unit with specific attributes.
 */
export class BasicEnemy: public Enemy {
public:
    /**
     * @brief Constructor to initialize a BasicEnemy object.
     * @param id The ID of the enemy.
     * @param health The health of the enemy.
     * @param attack The attack value of the enemy.
     * @param defense The defense value of the enemy.
     * @param evade The evade value of the enemy.
     */
    BasicEnemy(u16 id, u8 health, i8 attack, i8 defense, i8 evade):
        Enemy(Encounter::BASIC, id, health, attack, defense, evade) {}
};

END_MODULE_NAMESPACE();
