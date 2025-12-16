/**
 * @file Mob.cppm
 * @module openjuice.engine.entity.Mob
 * @brief Implementation of the Mob class.
 *
 * This file contains the implementation of the Mob class, which represents a mob entity in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.entity.Mob;

import std;

import openjuice.engine.game.ecs.Components;
import openjuice.engine.game.ecs.Entity;
import openjuice.engine.game.ecs.Registry;
import openjuice.engine.unit.Enemy;

using std::mem::SharedPointer;
using std::meta::IsBaseOfValue;

using openjuice::engine::game::ecs::Entity;
using openjuice::engine::game::ecs::Registry;
using openjuice::engine::game::ecs::components::MobTag;
using openjuice::engine::unit::Enemy;

BEGIN_MODULE_NAMESPACE(openjuice::engine::entity);

/**
 * @class Mob
 * @brief Class representing a mob entity.
 *
 * @extends Entity
 *
 * The Mob class extends the Entity abstract class and represents a mob entity in the game.
 */
export class Mob: public Entity {
public:
    /**
     * @brief Constructor to initialise a Mob object.
     * @param reg Reference to the ECS registry
     * @param enemy The enemy associated with the mob.
     */
    explicit Mob(Registry& reg, const SharedPointer<Enemy>& enemy = nullptr):
        Entity(reg, enemy) {
        reg.emplace<MobTag>(getEntityId());
    }
};

/**
 * @concept ExtendsMob
 * @brief Concept that checks if a type extends the Mob class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsMob = IsBaseOfValue<Mob, T>;

END_MODULE_NAMESPACE();
