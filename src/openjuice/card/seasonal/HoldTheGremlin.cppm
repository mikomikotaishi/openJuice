/**
 * @file HoldTheGremlin.cppm
 * @module openjuice.card.seasonal.HoldTheGremlin
 * @brief Implementation of the HoldTheGremlin class.
 *
 * This file contains the implementation of the HoldTheGremlin class, which represents the card "Lonely Chariot" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal.HoldTheGremlin;

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
 * @class HoldTheGremlin
 * @brief Class representing the HoldTheGremlin card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The HoldTheGremlin class extends both BoostCard and SeasonalCard to represent the card "Lonely Chariot" in the game.
 */
export class HoldTheGremlin final: public BoostCard, public SeasonalCard {
private:
    static constexpr u8 ID = 12; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_HoldTheGremlin", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HoldTheGremlin object.
     */
    HoldTheGremlin(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
