/**
 * @file character.cppm
 * @module openjuice.card.character
 * @brief Import of all Character-specific Cards.
 *
 * This file imports the modules for all Character-specific Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:character;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::character);

/**
 * @class MiosChristmasCake
 * @brief Class representing the MiosChristmasCake card.
 *
 * @extends BoostCard
 * @extends CharacterSpecificCard
 *
 * The MiosChristmasCake class extends both BoostCard and CharacterSpecificCard to represent the card "Mio's Christmas Cake" in the game.
 */
export class MiosChristmasCake final: public BoostCard, public CharacterSpecificCard {
public:
    static constexpr u8 ID = 1; ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::CHARACTER_SPECIFIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card
private:
    CARD_METADATA("CARD_BOOST_XMASCAKE", "CARD_ARTIST_JUNPYON")
public:
    /**
     * @brief Constructor to initialise a MiosChristmasCake object.
     */
    MiosChristmasCake():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class Freight
 * @brief Class representing the Freight card.
 *
 * @extends BattleCard
 * @extends CharacterSpecificCard
 *
 * The Freight class extends both BattleCard and CharacterSpecificCard to represent the card "Freight" in the game.
 */
export class Freight final: public BattleCard, public CharacterSpecificCard {
public:
    static constexpr u8 ID = 2; ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::CHARACTER_SPECIFIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card
private:
    CARD_METADATA("CARD_BATTLE_FREIGHT", "CARD_ARTIST_JUNPYON")
public:
    /**
     * @brief Constructor to initialise a Freight object.
     */
    Freight():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class RedAndBlue
 * @brief Class representing the RedAndBlue card.
 *
 * @extends GiftCard
 * @extends CharacterSpecificCard
 *
 * The ChristmasInferno class extends both GiftCard and CharacterSpecificCard to represent the card "Red & Blue" in the game.
 */
export class RedAndBlue final: public GiftCard, public CharacterSpecificCard {
public:
    static constexpr u8 ID = 3; ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::CHARACTER_SPECIFIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card
private:
    CARD_METADATA("CARD_GIFT_REDBLUE", "CARD_ARTIST_HONO")
public:
    /**
     * @brief Constructor to initialise a RedAndBlue object.
     */
    RedAndBlue():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
