/**
 * @file HyperMode.cppm
 * @module openjuice.card.hyper:HyperMode
 * @brief Implementation of the HyperMode class.
 *
 * This file contains the implementation of the HyperMode class, which represents the card "Hyper Mode" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper:HyperMode;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class HyperMode
 * @brief Class representing the HyperMode card.
 *
 * @extends BattleCard
 * @extends HyperCard
 *
 * The HyperMode class extends both BattleCard and HyperCard to represent the card "Hyper Mode" in the game.
 */
export class HyperMode final: public BattleCard, public HyperCard {
public:
    static constexpr u16 ID = 3; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_QP", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HyperMode object.
     */
    HyperMode():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
