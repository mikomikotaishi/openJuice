/**
 * @file SnowballReflector.cppm
 * @module openjuice.card.seasonal.SnowballReflector
 * @brief Implementation of the SnowballReflector class.
 *
 * This file contains the implementation of the SnowballReflector class, which represents the card "Snowball Reflector" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal.SnowballReflector;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class SnowballReflector
 * @brief Class representing the SnowballReflector card.
 *
 * @extends BattleCard
 * @extends SeasonalCard
 *
 * The SnowballReflector class extends both BattleCard and SeasonalCard to represent the card "Snowball Reflector" in the game.
 */
export class SnowballReflector final: public BattleCard, public SeasonalCard {
public:
    static constexpr u8 ID = 2; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_XMAS2018_SNOWBALLREFLECTOR", "CARD_ARTIST_COFFGIRL");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SnowballReflector object.
     */
    SnowballReflector(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
