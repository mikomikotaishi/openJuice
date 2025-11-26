/**
 * @file Hime.cppm
 * @module openjuice.unit.characters.maincharacters.Hime
 * @brief Implementation of the Hime class.
 *
 * This file contains the implementation of the Hime class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.Hime;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Hime
 * @brief Class representing the Hime character.
 *
 * @extends MainCharacter
 *
 * The Hime class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Hime final: public MainCharacter {
private:
    static constexpr u16 ID = 7; ///< ID of this specific character
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::THREE; ///< Difficulty of this specific character
    
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_HIME", "CARD_ARTIST_HONO", "VOICEACTOR_MOTOMIYA_KANA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Hime class.
     */
    Hime():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
