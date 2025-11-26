/**
 * @file IKeyQueryable.cppm
 * @module openjuice.engine.util.Interfaces:IKeyQueryable
 * @brief Definition of the IKeyQueryable marker interface.
 *
 * This file contains the definition of the IKeyQueryable marker interface, which denotes that a class queries a key from the TextManager class.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Interfaces:IKeyQueryable;

import std;

using std::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util::interfaces);

/**
 * @interface IKeyQueryable
 * @brief Marker interface for creating IKeyQueryable objects.
 * 
 * The IKeyQueryable marker interface is used to denote that a class will query some key from the TextManager class.
 */
export class IKeyQueryable {
protected:
    /**
     * @brief Protected default constructor to prevent direct instantiation.
     */
    IKeyQueryable() = default;
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~IKeyQueryable() = default;
};

/**
 * @concept ImplementsIKeyQueryable
 * @brief Concept that checks if a type implements the IKeyQueryable interface.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ImplementsIKeyQueryable = IsBaseOfValue<IKeyQueryable, T>;

END_MODULE_NAMESPACE();
