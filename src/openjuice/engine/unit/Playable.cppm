/**
 * @file Playable.cppm
 * @module openjuice.engine.unit:Playable
 * @brief Definition of the Playable abstract class.
 *
 * This file contains the definition of the Playable abstract class, which represents a playable unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit:Playable;

import stdx;

import :Unit;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @class Playable
 * @brief Abstract class representing a playable unit.
 * 
 * @extends Unit
 *
 * The Playable abstract class extends the Unit abstract class and represents a playable unit with a specific recovery attribute.
 */
export class Playable: public Unit {
private:
    const u8 recovery; ///< The recovery value of the playable.
public:
    /**
     * @brief Constructor to initialize a Playable object.
     *
     * @param id The ID of the playable.
     * @param health The health of the playable.
     * @param attack The attack value of the playable.
     * @param defense The defense value of the playable.
     * @param evade The evade value of the playable.
     * @param recovery The recovery value of the playable.
     */
    Playable(u16 id, u8 health, i8 attack, i8 defense, i8 evade, u8 recovery):
        Unit(id, health, attack, defense, evade), recovery{recovery} {}

    /**
     * @brief Get the recovery stat of the unit.
     * @return The recovery stat.
     */
    [[nodiscard]]
    u8 getRecovery() const noexcept {
        return recovery;
    }
};

END_MODULE_NAMESPACE();
