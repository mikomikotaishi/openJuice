/**
 * @file CompletionReward.cppm
 * @module openjuice.card.standard.acceleration:CompletionReward
 * @brief Implementation of the CompletionReward class.
 *
 * This file contains the implementation of the CompletionReward class, which represents the card "Completion Reward" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration:CompletionReward;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class CompletionReward
 * @brief Class representing the CompletionReward card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The CompletionReward class extends both BoostCard and StandardCard to represent the card "Completion Reward" in the game.
 */
export class CompletionReward final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 54; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BOOST_COMPLETIONREWARD", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a CompletionReward object.
     */
    CompletionReward(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
