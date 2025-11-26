/**
 * @file Component.cppm
 * @module openjuice.engine.game.IComponent
 * @brief Module file for the interface for a IComponent
 *
 * This file contains the interface of an IComponent
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs.IComponent;

import std;

using std::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @interface IComponent
 * @brief Interface for a component in the ECS system.
 */
export class IComponent {
public:
    /**
     * @brief Destroy the IComponent object
     */
    virtual ~IComponent() = default;
};

/**
 * @concept ImplementsIComponent
 * @brief Concept that checks if a type implements the IComponent interface.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ImplementsIComponent = IsBaseOfValue<IComponent, T>;

END_MODULE_NAMESPACE();
