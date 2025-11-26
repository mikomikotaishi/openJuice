/**
 * @file Fernet.cppm
 * @module openjuice.unit.characters.maincharacters.Fernet
 * @brief Implementation of the Fernet class.
 *
 * This file contains the implementation of the Fernet class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.Fernet;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Fernet
 * @brief Class representing the Fernet character.
 *
 * @extends MainCharacter
 *
 * The Fernet class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Fernet final: public MainCharacter {
private:
    static constexpr u16 ID = 6; ///< ID of this specific character
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    
    static constexpr u8 HEALTH = 6; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 2; ///< Defence stat of this specific character
    static constexpr i8 EVADE = -2; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_FERNET", "CARD_ARTIST_HONO", "VOICEACTOR_ARUNAMI_KAZUSA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Fernet class.
     */
    Fernet():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
