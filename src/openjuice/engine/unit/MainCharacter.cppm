/**
 * @file MainCharacter.cppm
 * @module openjuice.engine.unit.MainCharacter
 * @brief Definition of the MainCharacter abstract class.
 *
 * This file contains the definition of the MainCharacter abstract class, which represents a main character unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit.MainCharacter;

import std;

import openjuice.engine.unit.Playable;

using std::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @enum CharacterDifficulty
 * @brief Enumeration for character difficulty stars.
 *
 * The CharacterDifficulty enumeration defines the number of stars of difficulty
 * a character is rated.
 */
export enum class CharacterDifficulty: u8 {
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5
};

/**
 * @class MainCharacter
 * @brief Abstract class representing a character unit.
 * 
 * @extends Unit
 *
 * The MainCharacter abstract class extends the Playable abstract class and represents a main character unit with a specific recovery attribute.
 */
export class MainCharacter: public Playable {
private:
    const CharacterDifficulty difficulty; ///< The character difficulty of the main character.
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
    MainCharacter(u16 id, CharacterDifficulty difficulty, u8 health, i8 attack, i8 defence, i8 evade, u8 recovery):
        Playable(id, health, attack, defence, evade, recovery), difficulty{difficulty} {}

    /**
     * @brief Get the difficulty value of the playable.
     * @return The difficulty value of the playable.
     */
    [[nodiscard]]
    CharacterDifficulty getDifficulty() const noexcept {
        return difficulty;
    }
};

/**
 * @concept ExtendsMainCharacter
 * @brief Concept that checks if a type extends the MainCharacter class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsMainCharacter = IsBaseOfValue<MainCharacter, T>;

END_MODULE_NAMESPACE();
