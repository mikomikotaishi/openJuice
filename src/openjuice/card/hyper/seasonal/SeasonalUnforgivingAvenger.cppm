/**
 * @file SeasonalUnforgivingAvenger.cppm
 * @module openjuice.card.hyper.seasonal.SeasonalUnforgivingAvenger
 * @brief Implementation of the SeasonalUnforgivingAvenger class.
 *
 * This file contains the implementation of the SeasonalUnforgivingAvenger class, which represents the card "Chaos Protect" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.seasonal.SeasonalUnforgivingAvenger;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper::seasonal);

/**
 * @class SeasonalUnforgivingAvenger
 * @brief Class representing the SeasonalUnforgivingAvenger card.
 *
 * @extends BattleCard
 * @extends HyperCard
 * @extends SeasonalCard
 *
 * The SeasonalUnforgivingAvenger class extends both BoostCard and SeasonalCard to represent the card "Unforgiving Avenger" (seasonal) in the game.
 */
export class SeasonalUnforgivingAvenger final: public BattleCard, public HyperCard, public SeasonalCard {
private:
    static constexpr u16 ID = 2004; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BATTLE_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = DeckPointError::NOT_STANDARD_CARD; ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_SUMMER2018_AVENGER", "CARD_ARTIST_LENDO_KHAR");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SeasonalUnforgivingAvenger object.
     */
    SeasonalUnforgivingAvenger(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
