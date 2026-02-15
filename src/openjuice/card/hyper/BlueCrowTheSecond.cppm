/**
 * @file BlueCrowTheSecond.cppm
 * @module openjuice.card.hyper:BlueCrowTheSecond
 * @brief Implementation of the BlueCrowTheSecond class.
 *
 * This file contains the implementation of the BlueCrowTheSecond class, which represents the card "Blue Crow the Second" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper:BlueCrowTheSecond;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class BlueCrowTheSecond
 * @brief Class representing the BlueCrowTheSecond card.
 *
 * @extends BattleCard
 * @extends HyperCard
 *
 * The BlueCrowTheSecond class extends both BattleCard and HyperCard to represent the card "Blue Crow the Second" in the game.
 */
export class BlueCrowTheSecond final: public BattleCard, public HyperCard {
public:
    static constexpr u16 ID = 11; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_PEAT", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a BlueCrowTheSecond object.
     */
    BlueCrowTheSecond():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
