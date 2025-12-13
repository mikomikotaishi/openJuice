/**
 * @file GrownupSnowballFight.cppm
 * @module openjuice.card.seasonal.GrownupSnowballFight
 * @brief Implementation of the GrownupSnowballFight class.
 *
 * This file contains the implementation of the GrownupSnowballFight class, which represents the card "Grown-up Snowball Fight" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal.GrownupSnowballFight;

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
 * @class GrownupSnowballFight
 * @brief Class representing the GrownupSnowballFight card.
 *
 * @extends BattleCard
 * @extends SeasonalCard
 *
 * The GrownupSnowballFight class extends both BattleCard and SeasonalCard to represent the card "Grown-up Snowball Fight" in the game.
 */
export class GrownupSnowballFight final: public BattleCard, public SeasonalCard {
private:
    static constexpr u8 ID = 3; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_XMAS2018_GROWNUPSNOWBALLFIGHT", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GrownupSnowballFight object.
     */
    GrownupSnowballFight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
