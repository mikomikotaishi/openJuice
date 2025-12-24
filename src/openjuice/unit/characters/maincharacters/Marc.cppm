/**
 * @file Marc.cppm
 * @module openjuice.unit.characters.maincharacters:Marc
 * @brief Implementation of the Marc class.
 *
 * This file contains the implementation of the Marc class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:Marc;

import std;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Marc
 * @brief Class representing the Marc character.
 *
 * @extends MainCharacter
 *
 * The Marc class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Marc final: public MainCharacter {
public:
    static constexpr u16 ID = 2; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::TWO; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_MARC", "CARD_ARTIST_HONO", "VOICEACTOR_TAKAI_MAIKA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Marc class.
     */
    Marc():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
