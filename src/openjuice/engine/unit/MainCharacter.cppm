/**
 * @file MainCharacter.cppm
 * @module openjuice.engine.unit:MainCharacter
 * @brief Definition of the MainCharacter abstract class.
 *
 * This file contains the definition of the MainCharacter abstract class, which represents a main character unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit:MainCharacter;

import stdx;

import :Playable;

using stdx::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @class MainCharacter
 * @brief Abstract class representing a character unit.
 * 
 * @extends Unit
 *
 * The MainCharacter abstract class extends the Playable abstract class and represents a main character unit with a specific recovery attribute.
 */
export class MainCharacter: public Playable {
public:
    /**
     * @enum Difficulty
     * @brief Enumeration for character difficulty stars.
     *
     * The Difficulty enumeration defines the number of stars of difficulty
     * a character is rated.
     */
    enum class Difficulty: u8 {
        ONE = 1, ///< Difficulty of level 1
        TWO = 2, ///< Difficulty of level 2
        THREE = 3, ///< Difficulty of level 3
        FOUR = 4, ///< Difficulty of level 4
        FIVE = 5, ///< Difficulty of level 5
    };
private:
    const Difficulty difficulty; ///< The character difficulty of the main character.
public:
    /**
     * @brief Constructor to initialise a MainCharacter object.
     *
     * @param id The ID of the main character.
     * @param difficulty The difficulty of the main character.
     * @param health The health of the main character.
     * @param attack The attack value of the main character.
     * @param defence The defence value of the main character.
     * @param evade The evade value of the main character.
     * @param recovery The recovery value of the main character.
     */
    MainCharacter(u16 id, Difficulty difficulty, u8 health, i8 attack, i8 defence, i8 evade, u8 recovery):
        Playable(id, health, attack, defence, evade, recovery), difficulty{difficulty} {}

    Difficulty getDifficulty() const noexcept {
        return difficulty;
    }
};

END_MODULE_NAMESPACE();
