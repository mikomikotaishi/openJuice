/**
 * @file BossEnemyFactory.cppm
 * @module openjuice.unit:BossEnemyFactory
 * @brief Implementation of the BossEnemyFactory class.
 *
 * This file contains the implementation of the BossEnemyFactory class, which is used to create BossEnemy objects.
 */

module;

#include "Macros.hpp"

export module openjuice.unit:BossEnemyFactory;

import stdx;

import openjuice.engine.services;
import openjuice.engine.unit;
import openjuice.unit.bosses;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using namespace openjuice::engine::unit;
using namespace openjuice::unit::bosses;

BEGIN_MODULE_NAMESPACE(openjuice::unit);

/**
 * @class BossEnemyFactory
 * @brief Factory class for creating BossEnemy objects.
 *
 * The BossEnemyFactory class is a singleton factory class that creates BossEnemy objects based on the given ID.
 */
export class BossEnemyFactory final {
public:
    BossEnemyFactory() = delete("BossEnemyFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a BossEnemy object with the given ID.
    *
     * @param id ID of the BossEnemy to create
     * @return Shared pointer to the created BossEnemy object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BossEnemy>> create(u8 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            case FlyingCastle::ID:
                return Pointers::shared<FlyingCastle>();
            case ShifuRobot::ID:
                return Pointers::shared<ShifuRobot>();
            case StoreManager::ID:
                return Pointers::shared<StoreManager>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
