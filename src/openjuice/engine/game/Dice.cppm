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
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;

using openjuice::engine::util::Constants;
using openjuice::engine::util::RandomNumberGenerator;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game);

/**
 * @class Dice
 * @brief Thread-safe singleton class for dice rolling with history tracking
 */
export class Dice {
public:
    static constexpr usize DICEROLL_HISTORY_CAPACITY = Constants::DICEROLL_HISTORY_CAPACITY; ///< Maximum number of dice rolls stored.
private:
    /**
     * @class RollRecord
     * @brief Contains information on the number of sides rolled by the dice and the result.
     */
    class [[nodiscard]] RollRecord final {
    private:
        const u8 sides; ///< The number of sides on the die
        const u8 result; ///< The result of the roll
    public:
        [[nodiscard]]
        u8 getSides() const noexcept {
            return sides;
        }

        [[nodiscard]]
        u8 getResult() const noexcept {
            return result;
        }

        /**
         * @brief Constructor to initialise a RollRecord object.
         *
         * @param sides The number of sides on the die.
         * @param result The result of the roll.
         */
        constexpr RollRecord(u8 sides, u8 result):
            sides{sides}, result{result} {}

        /**
         * @brief Default destructor for RollRecord
         */
        ~RollRecord() = default;
    };

    Deque<RollRecord> rollHistory; ///< The history of all dice rolls
    mutable Mutex historyMutex; /// A mutex for the dice roll history

    void recordRoll(u8 sides, u8 result) {
        ScopedLock<Mutex> lock(historyMutex);
        rollHistory.emplace_back(sides, result);
        if (rollHistory.size() > DICEROLL_HISTORY_CAPACITY) {
            rollHistory.pop_front();
        }
    }

    Dice() = default;
public:
    /**
     * @brief Get the singleton instance (thread-safe using Meyer's singleton)
     *
     * @return Reference to the singleton Dice instance
     */
    [[nodiscard]]
    static Dice& getInstance() noexcept {
        static Dice instance;
        return instance;
    }

    /**
     * @brief Roll a 6-sided die
     *
     * @return A random number between 1 and 6
     */
    [[nodiscard]]
    u8 rollDice6() {
        u8 result = static_cast<u8>(RandomNumberGenerator::getRandomInteger(1, 6));
        recordRoll(6, result);
        return result;
    }

    /**
     * @brief Roll an 8-sided die
     *
     * @return A random number between 0 and 7
     */
    [[nodiscard]]
    u8 rollDice8() {
        u8 result = static_cast<u8>(RandomNumberGenerator::getRandomInteger(0, 7));
        recordRoll(8, result);
        return result;
    }

    /**
     * @brief Get the roll history (thread-safe)
     *
     * @return Vector of roll records (sides, result)
     */
    [[nodiscard]]
    Vector<Pair<u8, u8>> getHistory() const {
        ScopedLock<Mutex> lock(historyMutex);
        Vector<Pair<u8, u8>> history;
        history.reserve(rollHistory.size());

        for (const RollRecord& record: rollHistory) {
            history.emplace_back(record.getSides(), record.getResult());
        }

        return history;
    }

    /**
     * @brief Get statistics for a specific die
     *
     * @param sides Number of sides on the die
     * @return Pair of (total rolls, average result)
     */
    [[nodiscard]]
    Pair<usize, f32> getStats(u8 sides) const noexcept {
        ScopedLock<Mutex> lock(historyMutex);
        usize count = 0;
        f32 sum = 0.0f;

        for (const RollRecord& record: rollHistory) {
            if (record.getSides() == sides) {
                ++count;
                sum += static_cast<f32>(record.getResult());
            }
        }

        return {count, count > 0 ? sum / static_cast<f32>(count) : 0.0f};
    }

    /**
     * @brief Clear the roll history
     */
    void clearHistory() noexcept {
        ScopedLock<Mutex> lock(historyMutex);
        rollHistory.clear();
    }
};

END_MODULE_NAMESPACE();
