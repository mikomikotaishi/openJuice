/**
 * @file BasicEnemyFactory.cppm
 * @module openjuice.unit.BasicEnemyFactory
 * @brief Implementation of the BasicEnemyFactory class.
 *
 * This file contains the implementation of the BasicEnemyFactory class, which is used to create BasicEnemy objects.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.BasicEnemyFactory;

import std;
import stdx;

import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.unit.BasicEnemy;
import openjuice.unit.enemies;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

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
private:
    UTILITY_CLASS(BasicEnemyFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("TextUserInterface"); ///< The logger instance.
public:
    /**
     * @brief Create a BasicEnemy object with the given ID.
     *
     * @param id ID of the BasicEnemy to create
     * @return Shared pointer to the created BasicEnemy object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BasicEnemy>> create(u8 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating BasicEnemy of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            case 1:
                return std::mem::make_shared<Chicken>();
            case 2:
                return std::mem::make_shared<RoboBall>();
            case 3:
                return std::mem::make_shared<Seagull>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
