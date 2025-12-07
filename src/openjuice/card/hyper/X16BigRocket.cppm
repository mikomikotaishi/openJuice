/**
 * @file X16BigRocket.cppm
 * @module openjuice.card.hyper.X16BigRocket
 * @brief Implementation of the X16BigRocket class.
 *
 * This file contains the implementation of the X16BigRocket class, which represents the card "x16 Big Rocket" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.X16BigRocket;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::Rarity;
using openjuice::engine::card::SpawnType;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class X16BigRocket
 * @brief Class representing the X16BigRocket card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The X16BigRocket class extends both BoostCard and HyperCard to represent the card "x16 Big Rocket" in the game.
 */
export class X16BigRocket final: public BoostCard, public HyperCard {
private:
    static constexpr u16 ID = 2; ///< The ID of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = nullopt; ///< The cost of this specific card (deduct level * 10 stars from player)
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_MARC", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise an X16BigRocket object.
     */
    X16BigRocket():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
