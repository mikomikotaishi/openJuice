/**
 * @file Combatant.cppm
 * @module openjuice.engine.entity:Combatant
 * @brief Definition of the Combatant abstract class.
 *
 * This file contains the definition of the Combatant abstract class, which represents anything in the game that can
 * hold stars, take damage, and take part in a battle.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.entity:Combatant;

import stdx;

import openjuice.engine.unit;

using stdx::mem::SharedPointer;

using openjuice::engine::unit::Unit;

BEGIN_MODULE_NAMESPACE(openjuice::engine::entity);

/**
 * @class Combatant
 * @brief Abstract class representing anything that can take part in a battle.
 *
 * The Combatant abstract class represents a participant in the game with the following attributes: unit, stars, and
 * current health. The unit supplies the combatant's stat line, which is fixed for a given character, while everything
 * that changes over the course of a match is held here.
 */
export class Combatant {
protected:
    SharedPointer<Unit> unit; ///< The unit this combatant plays as, null until a character is assigned.
    u16 stars = 0; ///< The number of stars the combatant holds.
    u8 currentHealth = 0; ///< The combatant's current health.
    u8 maxHealth = 0; ///< The combatant's maximum health, taken from its unit.

    /**
     * @brief Constructor to initialize a Combatant object.
     * @param unit The unit associated with the combatant.
     */
    explicit Combatant(const SharedPointer<Unit>& unit = nullptr) noexcept:
        unit{unit} {
        if (unit != nullptr) {
            maxHealth = unit->getHealth();
            currentHealth = maxHealth;
        }
    }
public:
    /**
     * @brief Default destructor.
     */
    virtual ~Combatant() = default;

    /**
     * @brief Get the number of stars the combatant has.
     * @return The number of stars.
     */
    [[nodiscard]]
    u16 getStars() const noexcept {
        return stars;
    }

    /**
     * @brief Set the number of stars the combatant has.
     * @param amount The number of stars to set.
     */
    void setStars(u16 amount) noexcept {
        stars = amount;
    }

    /**
     * @brief Get the current health of the combatant.
     * @return The current health.
     */
    [[nodiscard]]
    u8 getCurrentHealth() const noexcept {
        return currentHealth;
    }

    /**
     * @brief Set the current health of the combatant.
     * @param health The current health to set.
     */
    void setCurrentHealth(u8 health) noexcept {
        currentHealth = health;
    }

    /**
     * @brief Get the max health of the combatant's unit.
     * @return The max health, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    u8 getMaxHealth() const noexcept {
        return maxHealth;
    }

    /**
     * @brief Get the unit associated with the combatant.
     * @return The unit.
     */
    [[nodiscard]]
    SharedPointer<Unit> getUnit() const noexcept {
        return unit;
    }

    /**
     * @brief Set the unit associated with the combatant, restoring it to that unit's full health.
     * @param newUnit The new unit to set. Ignored when null, since a combatant never loses its unit.
     */
    void setUnit(const SharedPointer<Unit>& newUnit) noexcept {
        if (newUnit == nullptr) {
            return;
        }

        unit = newUnit;
        maxHealth = newUnit->getHealth();
        currentHealth = maxHealth;
    }

    /**
     * @brief Get the attack value of the combatant's unit.
     * @return The attack value, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    i8 getAttack() const noexcept {
        return unit ? unit->getAttack() : 0;
    }

    /**
     * @brief Get the defense value of the combatant's unit.
     * @return The defense value, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    i8 getDefense() const noexcept {
        return unit ? unit->getDefense() : 0;
    }

    /**
     * @brief Get the evade value of the combatant's unit.
     * @return The evade value, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    i8 getEvade() const noexcept {
        return unit ? unit->getEvade() : 0;
    }
};

END_MODULE_NAMESPACE();
