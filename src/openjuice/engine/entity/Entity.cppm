/**
 * @file Entity.cppm
 * @module openjuice.engine.entity.Entity
 * @brief Definition of the Entity abstract class.
 *
 * This file contains the definition of the Entity abstract class, which represents a generic entity in the game.
 */

module;

#include <cassert>

#include "Macros.hpp"

export module openjuice.engine.entity.Entity;

import std;

import openjuice.engine.game.ecs.Components;
import openjuice.engine.game.ecs.Registry;
import openjuice.engine.unit.Unit;

using std::mem::SharedPointer;
using std::meta::IsBaseOfValue;

using openjuice::engine::game::ecs::EntityId;
using openjuice::engine::game::ecs::Registry;
using openjuice::engine::game::ecs::RegistryError;
using openjuice::engine::unit::Unit;

using namespace openjuice::engine::game::ecs::components;

BEGIN_MODULE_NAMESPACE(openjuice::engine::entity);

/**
 * @class Entity
 * @brief Abstract class representing a generic entity.
 *
 * The Entity abstract class represents a generic entity in the game with the following attributes: unit, stars, and current health.
 */
export class Entity {
private:
    EntityId id; ///< The ECS entity ID associated with this entity.
    Registry* registry; ///< Pointer to the ECS registry
public:
    /**
     * @brief Constructor to initialise an Entity object.
     * @param reg Reference to the ECS registry
     * @param unit The unit associated with the entity.
     */
    explicit Entity(Registry& reg, const SharedPointer<Unit>& unit = nullptr):
        registry{&reg} {
        Optional<EntityId> entityOpt = unit
            ? registry->entity(StarComponent(0), UnitComponent(unit), HealthComponent(unit->getHealth(), unit->getHealth()))
            : registry->entity(StarComponent(0));
        
        if (!entityOpt.has_value()) {
            throw RuntimeException("Failed to create entity!");
        }
        id = entityOpt.value();
    }

    /**
     * @brief Default destructor.
     */
    virtual ~Entity() = default;

    /**
     * @brief Get the entity ID used by the ECS.
     * @return The EntityId value.
     */
    [[nodiscard]]
    EntityId getEntityId() const noexcept {
        return id;
    }

    /**
     * @brief Get the number of stars the entity has.
     * @return The number of stars.
     */
    [[nodiscard]]
    u16 getStars() const {
        StarComponent* stars = registry->getIf<StarComponent>(id);
        return stars ? stars->stars : 0;
    }

    /**
     * @brief Set the number of stars the entity has.
     * @param amount The number of stars to set.
     */
    void setStars(u16 amount) const {
        if (StarComponent* stars = registry->getIf<StarComponent>(id)) {
            stars->stars = amount;
        } else {
            registry->emplace<StarComponent>(id, amount);
        }
    }

    /**
     * @brief Get the current health of the entity.
     * @return The current health.
     */
    [[nodiscard]]
    u8 getCurrentHealth() const {
        HealthComponent* health = registry->getIf<HealthComponent>(id);
        return health ? health->currentHealth : 0;
    }

    /**
     * @brief Set the current health of the entity.
     * @param health The current health to set.
     */
    void setCurrentHealth(u8 health) const {
        if (HealthComponent* healthComp = registry->getIf<HealthComponent>(id)) {
            healthComp->currentHealth = health;
        } else if (getUnit()) {
            registry->emplace<HealthComponent>(id, health, getUnit()->getHealth());
        }
    }

    /**
     * @brief Get the unit associated with the entity.
     * @return The unit.
     */
    [[nodiscard]]
    SharedPointer<Unit> getUnit() const {
        UnitComponent* unitComp = registry->getIf<UnitComponent>(id);
        return unitComp ? unitComp->unit : nullptr;
    }

    /**
     * @brief Set the unit associated with the entity.
     * @param newUnit The new unit to set.
     */
    void setUnit(const SharedPointer<Unit>& newUnit) const {
        assert(newUnit);

        if (newUnit) {
            if (UnitComponent* unitComp = registry->getIf<UnitComponent>(id)) {
                unitComp->unit = newUnit;
            } else {
                registry->emplace<UnitComponent>(id, newUnit);
            }

            if (HealthComponent* healthComp = registry->getIf<HealthComponent>(id)) {
                healthComp->maxHealth = newUnit->getHealth();
                healthComp->currentHealth = newUnit->getHealth();
            } else {
                registry->emplace<HealthComponent>(id, newUnit->getHealth(), newUnit->getHealth());
            }
        }
    }

    /**
     * @brief Get the attack value of the entity's unit.
     * @return The attack value, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    i8 getAttack() const {
        SharedPointer<Unit> unit = getUnit();
        return unit ? unit->getAttack() : 0;
    }

    /**
     * @brief Get the defense value of the entity's unit.
     * @return The defense value, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    i8 getDefense() const {
        SharedPointer<Unit> unit = getUnit();
        return unit ? unit->getDefence() : 0;
    }

    /**
     * @brief Get the evade value of the entity's unit.
     * @return The evade value, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    i8 getEvade() const {
        SharedPointer<Unit> unit = getUnit();
        return unit ? unit->getEvade() : 0;
    }

    /**
     * @brief Get the max health of the entity's unit.
     * @return The max health, or 0 if no unit is assigned.
     */
    [[nodiscard]]
    u8 getMaxHealth() const {
        HealthComponent* health = registry->getIf<HealthComponent>(id);
        return health ? health->maxHealth : 0;
    }
};

/**
 * @concept ExtendsEntity
 * @brief Concept that checks if a type extends the ExtendsEntity class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsEntity = IsBaseOfValue<Entity, T>;

END_MODULE_NAMESPACE();
