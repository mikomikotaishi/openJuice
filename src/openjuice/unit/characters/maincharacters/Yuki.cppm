/**
 * @file Yuki.cppm
 * @module openjuice.unit.characters.maincharacters:Yuki
 * @brief Implementation of the Yuki class.
 *
 * This file contains the implementation of the Yuki class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:Yuki;

import std;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Yuki
 * @brief Class representing the Yuki character.
 *
 * @extends MainCharacter
 *
 * The Yuki class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Yuki final: public MainCharacter {
public:
    static constexpr u16 ID = 14; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_YUKI", "CARD_ARTIST_HONO", "VOICEACTOR_AIYA_SAKI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Yuki class.
     */
    Yuki():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
