/**
 * @file MariePoppo.cppm
 * @module openjuice.unit.characters.maincharacters.MariePoppo
 * @brief Implementation of the MariePoppo class.
 *
 * This file contains the implementation of the MariePoppo class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.MariePoppo;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class MariePoppo
 * @brief Class representing the MariePoppo character.
 *
 * @extends MainCharacter
 *
 * The MariePoppo class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class MariePoppo final: public MainCharacter {
private:
    static constexpr u16 ID = 8; ///< ID of this specific character
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::FOUR; ///< Difficulty of this specific character
    
    static constexpr u8 HEALTH = 7; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_POPPO", "CARD_ARTIST_HONO", "VOICEACTOR_MARUYAMA_MIKI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the MariePoppo class.
     */
    MariePoppo():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
