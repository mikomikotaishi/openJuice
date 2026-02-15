/**
 * @file MioFestive.cppm
 * @module openjuice.unit.characters.maincharacters:MioFestive
 * @brief Implementation of the MioFestive class.
 *
 * This file contains the implementation of the MioFestive class, which represents a character in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.maincharacters:MioFestive;

import stdx;

import openjuice.engine.unit;

using openjuice::engine::unit::CharacterDifficulty;
using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::maincharacters);

/**
 * @class MioFestive
 * @brief Class representing the MioFestive character.
 *
 * @extends MainCharacter
 *
 * The MioFestive class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class MioFestive final: public MainCharacter {
public:
    static constexpr u16 ID = 10; ///< ID of this specific character
private:
    static constexpr CharacterDifficulty DIFFICULTY = CharacterDifficulty::TWO; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific character
    static constexpr i8 DEFENCE = -2; ///< Defence stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    UNIT_METADATA("CARD_UNIT_MIOFESTIVE", "CARD_ARTIST_YULAY_DEVLET", "VOICEACTOR_IZAWA_SHIORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor for the MioFestive class.
     */
    MioFestive():
        SET_MAIN_CHARACTER_STATS() {}
};

END_MODULE_NAMESPACE();
