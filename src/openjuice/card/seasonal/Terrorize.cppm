/**
 * @file Terrorize.cppm
 * @module openjuice.card.seasonal:Terrorize
 * @brief Implementation of the Terrorize class.
 *
 * This file contains the implementation of the Terrorize class, which represents the card "Terrorize" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal:Terrorize;

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
 * @class Terrorize
 * @brief Class representing the Terrorize card.
 *
 * @extends GiftCard
 * @extends HyperCard
 * @extends SeasonalCard
 *
 * The Terrorize class extends both GiftCard and SeasonalCard to represent the card "Terrorize" in the game.
 */
export class Terrorize final: public BoostCard, public HyperCard, public SeasonalCard {
public:
    static constexpr u8 ID = 13; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_CHAOS_GIFT_HOTPOTATO", "CARD_CHAOS_BDTT_HYPER");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Terrorize object.
     */
    Terrorize(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
