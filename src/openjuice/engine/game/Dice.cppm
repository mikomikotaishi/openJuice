/**
 * @file Dice.cppm
 * @module openjuice.engine.game.Dice
 * @brief Thread-safe singleton dice system with roll history using RAII.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.Dice;

import stdx;

import openjuice.engine.util;

using stdx::collections::Deque;
using stdx::collections::Vector;
using stdx::random::RandomDevice;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;

using openjuice::engine::util::Constants;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game);

/**
 * @class Dice
 * @brief Thread-safe class for dice rolling with history tracking
 */
export class Dice {
public:
    static constexpr usize DICEROLL_HISTORY_CAPACITY = Constants::DICEROLL_HISTORY_CAPACITY; ///< Maximum number of dice rolls stored.

    /**
     * @enum Sides
     * @brief Represents the number of sides on a die.
     */
    enum class Sides: u8 {
        SIX = 6, ///< Six-sided die
        EIGHT = 8, ///< Eight-sided die
    };

    /**
     * @class Roll
     * @brief Contains information on the number of sides rolled by the dice and the result.
     */
    struct [[nodiscard]] Roll final {
        Sides sides; ///< The number of sides on the die
        u8 result; ///< The result of the roll
    };
private:
    Random<> rng; ///< Random number generator for dice rolls
    Deque<Roll> history; ///< The history of all dice rolls
    mutable Mutex mutex; /// A mutex for the dice roll history

    void recordRoll(Sides sides, u8 result) {
        ScopedLock<Mutex> lock(mutex);
        history.push_back(Roll {
            .sides = sides,
            .result = result
        });
        if (history.size() > DICEROLL_HISTORY_CAPACITY) {
            history.pop_front();
        }
    }
public:
    explicit Dice(Random<>::Seed seed = {}):
        rng{seed} {}

    /**
     * @brief Roll a 6-sided die
     * @return A random number between 1 and 6
     */
    [[nodiscard]]
    u8 roll(Sides sides) {
        u8 result = [this, sides] -> u8 {
            switch (sides) {
                case Sides::SIX:
                    return static_cast<u8>(rng.next(1, 6));
                case Sides::EIGHT:
                    return static_cast<u8>(rng.next(1, 8));
            }
            Ops::unreachable();
        }();
        recordRoll(sides, result);
        return result;
    }

    /**
     * @brief Get the roll history (thread-safe)
     * @return Vector of roll records (sides, result)
     */
    [[nodiscard]]
    Vector<Roll> getHistory() const {
        ScopedLock<Mutex> lock(mutex);
        return Vector<Roll>(history.begin(), history.end());
    }

    /**
     * @brief Get statistics for a specific die
     * @param sides Number of sides on the die
     * @return Pair of (total rolls, average result)
     */
    [[nodiscard]]
    Pair<usize, f32> getStats(Sides sides) const noexcept {
        ScopedLock<Mutex> lock(mutex);
        usize count = 0;
        f32 sum = 0.0f;

        for (const Roll& record: history) {
            if (record.sides == sides) {
                ++count;
                sum += static_cast<f32>(record.result);
            }
        }

        return {count, count > 0 ? sum / static_cast<f32>(count) : 0.0f};
    }

    /**
     * @brief Clear the roll history
     */
    void clearHistory() noexcept {
        ScopedLock<Mutex> lock(mutex);
        history.clear();
    }
};

END_MODULE_NAMESPACE();
