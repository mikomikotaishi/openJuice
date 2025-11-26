/**
 * @file ExtraordinarySpecs.cppm
 * @module openjuice.card.hyper.ExtraordinarySpecs
 * @brief Implementation of the ExtraordinarySpecs class.
 *
 * This file contains the implementation of the ExtraordinarySpecs class, which represents the card "Extraordinary Specs" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.ExtraordinarySpecs;

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
 * @class ExtraordinarySpecs
 * @brief Class representing the ExtraordinarySpecs card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The ExtraordinarySpecs class extends both BoostCard and HyperCard to represent the card "Extraordinary Specs" in the game.
 */
export class ExtraordinarySpecs final: public BoostCard, public HyperCard {
private:
    static constexpr u16 ID = 12; ///< The ID of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_SORA", "CARD_ARTIST_ERINA");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ExtraordinarySpecs object.
     */
    ExtraordinarySpecs():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
