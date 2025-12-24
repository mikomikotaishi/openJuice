/**
 * @file IFinalOnly.cppm
 * @module openjuice.engine.util:IFinalOnly
 * @brief Definition of the IFinalOnly marker interface.
 *
 * This file contains the definition of the IFinalOnly marker interface, which denotes that only final classes should be concrete.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:IFinalOnly;

import std;

using std::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @interface IFinalOnly
 * @brief Marker interface for creating IFinalOnly objects.
 * 
 * The IFinalOnly marker interface is used to denote that only final classes should be concrete. Final classes should implement the method noop() as a private method with an empty body.
 */
export class IFinalOnly {
private:
    /**
     * @brief No-operation function, should only be implemented by final classes.
     */
    [[maybe_unused]]
    virtual void noop() const noexcept = 0;
protected:
    /**
     * @brief Protected default constructor to prevent direct instantiation.
     */
    IFinalOnly() = default;
};

/**
 * @concept ImplementsIFinalOnly
 * @brief Concept that checks if a type implements the IFinalOnly interface.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ImplementsIFinalOnly = IsBaseOfValue<IFinalOnly, T>;

END_MODULE_NAMESPACE();
