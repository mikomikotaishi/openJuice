/**
 * @file ChaosProtect.cppm
 * @module openjuice.card.seasonal.ChaosProtect
 * @brief Implementation of the ChaosProtect class.
 *
 * This file contains the implementation of the ChaosProtect class, which represents the card "Chaos Protect" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal.ChaosProtect;

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
 * @class ChaosProtect
 * @brief Class representing the ChaosProtect card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The ChaosProtect class extends both BoostCard and SeasonalCard to represent the card "Chaos Protect" in the game.
 */
export class ChaosProtect final: public BoostCard, public SeasonalCard {
private:
    static constexpr u8 ID = 7; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_ChaosProtect", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ChaosProtect object.
     */
    ChaosProtect(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
