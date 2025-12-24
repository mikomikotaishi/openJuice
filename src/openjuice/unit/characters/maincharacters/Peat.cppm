/**
 * @file Peat.cppm
 * @module openjuice.unit.characters.maincharacters:Peat
 * @brief Implementation of the Peat class.
 *
 * This file contains the implementation of the Peat class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:Peat;

import std;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Peat
 * @brief Class representing the Peat character.
 *
 * @extends MainCharacter
 *
 * The Peat class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Peat final: public MainCharacter {
public:
    static constexpr u16 ID = 11; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 4; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_PEAT", "CARD_ARTIST_HONO", "VOICEACTOR_KOUSAKA_ATSUSHI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Peat class.
     */
    Peat():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
