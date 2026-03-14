/**
 * @file RandomNumberGenerator.cppm
 * @module openjuice.engine.util:RandomNumberGenerator
 * @brief Implementation of the RandomNumberGenerator class.
 *
 * This file contains the implementation of the RandomNumberGenerator class, which is used to generate random numbers.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:RandomNumberGenerator;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @class RandomNumberGenerator
 * @brief Class for generating random numbers.
 *
 * The RandomNumberGenerator class is a singleton class that generates random numbers.
 */
export class RandomNumberGenerator final {
private:
    static thread_local inline Random rand = Random(); ///< Mersenne Twister random number generator.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    RandomNumberGenerator() = default;
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    RandomNumberGenerator(const RandomNumberGenerator&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;

    /**
     * @brief Generate a random integer within a specified range.
     *
     * @param min The minimum value.
     * @param max The maximum value.
     * @return A random integer between min and max.
     */
    [[nodiscard]]
    static i32 getRandomInteger(i32 min, i32 max) noexcept {
        return rand.next(min, max);
    }

    /**
     * @brief Generate a random real number within a specified range.
     *
     * @param min The minimum value.
     * @param max The maximum value.
     * @return A random real number between min and max.
     */
    [[nodiscard]]
    static f64 getRandomReal(f64 min, f64 max) noexcept {
        return rand.next(min, max);
    }
};

END_MODULE_NAMESPACE();
