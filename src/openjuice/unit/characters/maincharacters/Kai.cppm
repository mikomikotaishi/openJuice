/**
 * @file Kai.cppm
 * @module openjuice.unit.characters.maincharacters:Kai
 * @brief Implementation of the Kai class.
 *
 * This file contains the implementation of the Kai class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:Kai;

import std;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Kai
 * @brief Class representing the Kai character.
 *
 * @extends MainCharacter
 *
 * The Kai class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Kai final: public MainCharacter {
public:
    static constexpr u16 ID = 1; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 0; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_KAI", "CARD_ARTIST_HONO", "VOICEACTOR_MATSUURA_YOSHIYUKI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Kai class.
     */
    Kai():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
