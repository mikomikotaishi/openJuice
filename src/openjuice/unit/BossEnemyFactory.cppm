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

import openjuice.engine.managers;
import openjuice.engine.unit;
import openjuice.unit.bosses;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

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
private:
    UTILITY_CLASS(BossEnemyFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("TextUserInterface"); ///< The logger instance.
public:
    /**
     * @brief Create a BossEnemy object with the given ID.
    *
     * @param id ID of the BossEnemy to create
     * @return Shared pointer to the created BossEnemy object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BossEnemy>> create(u8 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating BossEnemy of ID: {}", id);
        #endif

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
