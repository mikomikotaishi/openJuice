/**
 * @file Sora.cppm
 * @module openjuice.unit.characters.maincharacters.Sora
 * @brief Implementation of the Sora class.
 *
 * This file contains the implementation of the Sora class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.Sora;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Sora
 * @brief Class representing the Sora character.
 *
 * @extends MainCharacter
 *
 * The Sora class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Sora final: public MainCharacter {
public:
    static constexpr u16 ID = 12; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 0; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_SORA", "CARD_ARTIST_HONO", "VOICEACTOR_MARUYAMA_MIKI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Sora class.
     */
    Sora():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
