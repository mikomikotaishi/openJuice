/**
 * @file Aru.cppm
 * @module openjuice.unit.characters.maincharacters.Aru
 * @brief Implementation of the Aru class.
 *
 * This file contains the implementation of the Aru class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.Aru;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Aru
 * @brief Class representing the Aru character.
 *
 * @extends MainCharacter
 *
 * The Aru class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Aru final: public MainCharacter {
private:
    static constexpr u16 ID = 5; ///< ID of this specific character
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::THREE; ///< Difficulty of this specific character
    
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 2; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_ARU", "CARD_ARTIST_HONO", "VOICEACTOR_MOTOMIYA_KANA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Aru class.
     */
    Aru():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
