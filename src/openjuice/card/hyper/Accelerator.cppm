/**
 * @file Accelerator.cppm
 * @module openjuice.card.hyper.Accelerator
 * @brief Implementation of the Accelerator class.
 *
 * This file contains the implementation of the Accelerator class, which represents the card "Accelerator" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.Accelerator;

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
 * @class Accelerator
 * @brief Class representing the Accelerator card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The Accelerator class extends both BoostCard and HyperCard to represent the card "Accelerator" in the game.
 */
export class Accelerator final: public BoostCard, public HyperCard {
public:
    static constexpr u16 ID = 4; ///< The ID of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_SUGURI", "CARD_ARTIST_MIZUKISEO");
    IMPLEMENT_NOOP();  
public:
    /**
     * @brief Constructor to initialise an Accelerator object.
     */
    Accelerator():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
