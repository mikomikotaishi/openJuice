/**
 * @file QP.cppm
 * @module openjuice.unit.characters.maincharacters.QP
 * @brief Implementation of the QP class.
 *
 * This file contains the implementation of the QP class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters.QP;

import std;

import openjuice.engine.unit.MainCharacter;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class QP
 * @brief Class representing the QP character.
 *
 * @extends MainCharacter
 *
 * The QP class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class QP final: public MainCharacter {
private:
    static constexpr u16 ID = 3; ///< ID of this specific character
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::TWO; ///< Difficulty of this specific character
    
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 0; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = 0; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_QP", "CARD_ARTIST_HONO", "VOICEACTOR_SATO_AZUSA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the QP class.
     */
    QP():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
