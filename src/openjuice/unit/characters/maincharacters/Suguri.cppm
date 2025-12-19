/**
 * @file Suguri.cppm
 * @module openjuice.unit.characters.maincharacters.Suguri
 * @brief Implementation of the Suguri class.
 *
 * This file contains the implementation of the Suguri class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.Suguri;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Suguri
 * @brief Class representing the Suguri character.
 *
 * @extends MainCharacter
 *
 * The Suguri class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Suguri final: public MainCharacter {
public:
    static constexpr u16 ID = 4; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::THREE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 2; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_SUGURI", "CARD_ARTIST_HONO", "VOICEACTOR_YOSHIDA_SEIKO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Suguri class.
     */
    Suguri():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
