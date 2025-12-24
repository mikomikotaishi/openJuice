/**
 * @file Tomomo.cppm
 * @module openjuice.unit.characters.maincharacters:Tomomo
 * @brief Implementation of the Tomomo class.
 *
 * This file contains the implementation of the Tomomo class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:Tomomo;

import std;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class Tomomo
 * @brief Class representing the Tomomo character.
 *
 * @extends MainCharacter
 *
 * The Tomomo class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Tomomo final: public MainCharacter {
public:
    static constexpr u16 ID = 13; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 0; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 6; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_TOMOMO", "CARD_ARTIST_HONO", "VOICEACTOR_ARANAMI_KAZUSA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the Tomomo class.
     */
    Tomomo():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
