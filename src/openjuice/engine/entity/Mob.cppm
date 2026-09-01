/**
 * @file Mob.cppm
 * @module openjuice.engine.entity:Mob
 * @brief Implementation of the Mob class.
 *
 * This file contains the implementation of the Mob class, which represents a mob entity in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.entity:Mob;

import :Combatant;

import stdx;

import openjuice.engine.unit;

using stdx::mem::SharedPointer;

using openjuice::engine::unit::Enemy;

BEGIN_MODULE_NAMESPACE(openjuice::engine::entity);

/**
 * @class Mob
 * @brief Class representing a mob entity.
 * @extends Combatant
 *
 * The Mob class extends the Combatant abstract class and represents a mob entity in the game.
 */
export class Mob: public Combatant {
public:
    /**
     * @brief Constructor to initialize a Mob object.
     * @param enemy The enemy associated with the mob.
     */
    explicit Mob(const SharedPointer<Enemy>& enemy = nullptr) noexcept:
        Combatant(enemy) {}
};

END_MODULE_NAMESPACE();
