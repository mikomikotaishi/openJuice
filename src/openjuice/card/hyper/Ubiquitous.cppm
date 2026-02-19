/**
 * @file Ubiquitous.cppm
 * @module openjuice.card.hyper:Ubiquitous
 * @brief Implementation of the Ubiquitous class.
 *
 * This file contains the implementation of the Ubiquitous class, which represents the card "Ubiquitous" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper:Ubiquitous;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class Ubiquitous
 * @brief Class representing the Ubiquitous card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The Ubiquitous class extends both BoostCard and HyperCard to represent the card "Ubiquitous" in the game.
 */
export class Ubiquitous final: public BoostCard, public HyperCard {
public:
    static constexpr u16 ID = 8; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_POPPO", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise an Ubiquitous object.
     */
    Ubiquitous():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
