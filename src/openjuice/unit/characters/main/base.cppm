/**
 * @file base.cppm
 * @module openjuice.unit.characters.main:base
 * @brief Import of all base characters.
 *
 * This file imports the modules for all base characters.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.characters.main:base;

import stdx;

import openjuice.engine.unit;

using openjuice::engine::unit::MainCharacter;

BEGIN_MODULE_NAMESPACE(openjuice::unit::characters::main::base);

/**
 * @class Kai
 * @brief Class representing the Kai character.
 * @extends MainCharacter
 *
 * The Kai class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Kai final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_KAI",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_MATSUURA_YOSHIYUKI",
    };
public:
    static constexpr u16 ID = 1; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 0; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Kai class.
     */
    Kai():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Marc
 * @brief Class representing the Marc character.
 * @extends MainCharacter
 *
 * The Marc class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Marc final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_MARC",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_TAKAI_MAIKA",
    };
public:
    static constexpr u16 ID = 2; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::TWO; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Marc class.
     */
    Marc():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class QP
 * @brief Class representing the QP character.
 * @extends MainCharacter
 *
 * The QP class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class QP final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_QP",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_SATO_AZUSA",
    };
public:
    static constexpr u16 ID = 3; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::TWO; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 0; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 0; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the QP class.
     */
    QP():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Suguri
 * @brief Class representing the Suguri character.
 * @extends MainCharacter
 *
 * The Suguri class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Suguri final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_SUGURI",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_YOSHIDA_SEIKO",
    };
public:
    static constexpr u16 ID = 4; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::THREE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 2; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Suguri class.
     */
    Suguri():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Aru
 * @brief Class representing the Aru character.
 * @extends MainCharacter
 *
 * The Aru class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Aru final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_ARU",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_MOTOMIYA_KANA",
    };
public:
    static constexpr u16 ID = 5; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::THREE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 2; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Aru class.
     */
    Aru():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Fernet
 * @brief Class representing the Fernet character.
 * @extends MainCharacter
 *
 * The Fernet class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Fernet final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_FERNET",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_ARUNAMI_KAZUSA",
    };
public:
    static constexpr u16 ID = 6; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 6; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 2; ///< Defense stat of this specific character
    static constexpr i8 EVADE = -2; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Fernet class.
     */
    Fernet():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Hime
 * @brief Class representing the Hime character.
 * @extends MainCharacter
 *
 * The Hime class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Hime final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_HIME",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_MOTOMIYA_KANA",
    };
public:
    static constexpr u16 ID = 7; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::THREE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Hime class.
     */
    Hime():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class MariePoppo
 * @brief Class representing the MariePoppo character.
 * @extends MainCharacter
 *
 * The MariePoppo class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class MariePoppo final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_POPPO",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_MARUYAMA_MIKI",
    };
public:
    static constexpr u16 ID = 8; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::FOUR; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 7; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the MariePoppo class.
     */
    MariePoppo():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Mio
 * @brief Class representing the Mio character.
 * @extends MainCharacter
 *
 * The Mio class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Mio final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_MIO",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_IZAWA_SHIORI",
    };
public:
    static constexpr u16 ID = 9; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 6; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 0; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Mio class.
     */
    Mio():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class MioFestive
 * @brief Class representing the MioFestive character.
 * @extends MainCharacter
 *
 * The MioFestive class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class MioFestive final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_MIOFESTIVE",
        .artistKey = "CARD_ARTIST_YULAY_DEVLET",
        .voiceActorKey = "VOICEACTOR_IZAWA_SHIORI",
    };
public:
    static constexpr u16 ID = 10; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::TWO; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -2; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the MioFestive class.
     */
    MioFestive():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Peat
 * @brief Class representing the Peat character.
 * @extends MainCharacter
 *
 * The Peat class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Peat final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_PEAT",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_KOUSAKA_ATSUSHI",
    };
public:
    static constexpr u16 ID = 11; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 3; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 4; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Peat class.
     */
    Peat():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Sora
 * @brief Class representing the Sora character.
 * @extends MainCharacter
 *
 * The Sora class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Sora final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_SORA",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_MARUYAMA_MIKI",
    };
public:
    static constexpr u16 ID = 12; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = -1; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 0; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Sora class.
     */
    Sora():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Tomomo
 * @brief Class representing the Tomomo character.
 * @extends MainCharacter
 *
 * The Tomomo class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Tomomo final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_TOMOMO",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_ARANAMI_KAZUSA",
    };
public:
    static constexpr u16 ID = 13; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 4; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = 0; ///< Defense stat of this specific character
    static constexpr i8 EVADE = 0; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 6; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Tomomo class.
     */
    Tomomo():
        SET_MAIN_CHARACTER_STATS() {}
};

/**
 * @class Yuki
 * @brief Class representing the Yuki character.
 * @extends MainCharacter
 *
 * The Yuki class is a final class that inherits from MainCharacter and represents a specific character in the game.
 */
export class Yuki final: public MainCharacter {
private:
    static constexpr Metadata METADATA = {
        .unitKey = "CARD_UNIT_YUKI",
        .artistKey = "CARD_ARTIST_HONO",
        .voiceActorKey = "VOICEACTOR_AIYA_SAKI",
    };
public:
    static constexpr u16 ID = 14; ///< ID of this specific character
    static constexpr MainCharacter::Difficulty DIFFICULTY = MainCharacter::Difficulty::ONE; ///< Difficulty of this specific character
    static constexpr u8 HEALTH = 5; ///< Health stat of this specific character
    static constexpr i8 ATTACK = 2; ///< Attack stat of this specific character
    static constexpr i8 DEFENSE = -1; ///< Defense stat of this specific character
    static constexpr i8 EVADE = -1; ///< Evade stat of this specific character
    static constexpr u8 RECOVERY = 5; ///< Recovery stat of this specific character

    /**
     * @brief Constructor for the Yuki class.
     */
    Yuki():
        SET_MAIN_CHARACTER_STATS() {}
};

// Chicken (15)
// RoboBall (16)
// Seagull (17)
// StoreManager (18)
// ShifuRobot (19)
// FlyingCastle (20)

END_MODULE_NAMESPACE();
