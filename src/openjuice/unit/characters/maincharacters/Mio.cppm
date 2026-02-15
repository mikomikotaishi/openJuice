/**
 * @file Mio.cppm
 * @module openjuice.unit.characters.maincharacters:Mio
 * @brief Implementation of the Mio class.
 *
 * This file contains the implementation of the Mio class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:Mio;

import stdx;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Mio
 * @brief Class representing the Mio character.
 *
 * @extends MainCharacter
 *
 * The Mio class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Mio final: public MainCharacter {
public:
    static constexpr u16 ID = 9; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 6; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 0; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -1; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_MIO", "CARD_ARTIST_HONO", "VOICEACTOR_IZAWA_SHIORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Mio class.
     */
    Mio():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
