/**
 * @file SweetBattle.cppm
 * @module openjuice.card.seasonal:SweetBattle
 * @brief Implementation of the SweetBattle class.
 *
 * This file contains the implementation of the SweetBattle class, which represents the card "Sweet Battle" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal:SweetBattle;

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
 * @class SweetBattle
 * @brief Class representing the SweetBattle card.
 *
 * @extends GiftCard
 * @extends SeasonalCard
 *
 * The SweetBattle class extends both GiftCard and SeasonalCard to represent the card "Sweet Battle" in the game.
 */
export class SweetBattle final: public GiftCard, public SeasonalCard {
public:
    static constexpr u8 ID = 1; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::GIFT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_GIFT_VALENTINESDAY2018", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SweetBattle object.
     */
    SweetBattle(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
