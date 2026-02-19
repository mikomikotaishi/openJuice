/**
 * @file ChaosRoulette.cppm
 * @module openjuice.card.seasonal:ChaosRoulette
 * @brief Implementation of the ChaosRoulette class.
 *
 * This file contains the implementation of the ChaosRoulette class, which represents the card "Chaos Roulette" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal:ChaosRoulette;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class ChaosRoulette
 * @brief Class representing the ChaosRoulette card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The ChaosRoulette class extends both BoostCard and SeasonalCard to represent the card "Chaos Roulette" in the game.
 */
export class ChaosRoulette final: public BoostCard, public SeasonalCard {
public:
    static constexpr u8 ID = 10; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_CHAOS_ROULETTE", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ChaosRoulette object.
     */
    ChaosRoulette(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
