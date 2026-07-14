/**
 * @file BasicEnemyFactory.cppm
 * @module openjuice.unit:BasicEnemyFactory
 * @brief Implementation of the BasicEnemyFactory class.
 *
 * This file contains the implementation of the BasicEnemyFactory class, which is used to create BasicEnemy objects.
 */

module;

#include "Macros.hpp"

export module openjuice.unit:BasicEnemyFactory;

import stdx;

import openjuice.engine.services;
import openjuice.engine.unit;
import openjuice.engine.util;
import openjuice.unit.enemies;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using namespace openjuice::engine::unit;
using namespace openjuice::unit::enemies;

BEGIN_MODULE_NAMESPACE(openjuice::unit);

/**
 * @class BasicEnemyFactory
 * @brief Factory class for creating BasicEnemy objects.
 *
 * The BasicEnemyFactory class is a singleton factory class that creates BasicEnemy objects based on the given ID.
 */
export class BasicEnemyFactory final {
public:
    BasicEnemyFactory() = delete("BasicEnemyFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Get the ID of a BasicEnemy from its name.
     * @param name Name of the BasicEnemy
     * @return Optional containing the ID of the BasicEnemy, or nullopt if not found
     */
    [[nodiscard]]
    static constexpr Optional<u8> idOf(StringView name) noexcept {
        switch (engine::util::hashString(name)) {
            case "Chicken"_hash:
                return Chicken::ID;
            case "Robo Ball"_hash:
                return RoboBall::ID;
            case "Seagull"_hash:
                return Seagull::ID;
            default:
                return nullopt;
        }
    }

    /**
     * @brief Create a BasicEnemy object with the given ID.
     * @param id ID of the BasicEnemy to create
     * @return Shared pointer to the created BasicEnemy object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static constexpr Optional<SharedPointer<BasicEnemy>> create(u8 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            case Chicken::ID:
                return Pointers::shared<Chicken>();
            case RoboBall::ID:
                return Pointers::shared<RoboBall>();
            case Seagull::ID:
                return Pointers::shared<Seagull>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
