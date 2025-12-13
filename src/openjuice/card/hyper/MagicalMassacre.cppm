/**
 * @file MagicalMassacre.cppm
 * @module openjuice.card.hyper.MagicalMassacre
 * @brief Implementation of the MagicalMassacre class.
 *
 * This file contains the implementation of the MagicalMassacre class, which represents the card "Magical Massacre" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.MagicalMassacre;

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
 * @class MagicalMassacre
 * @brief Class representing the MagicalMassacre card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The MagicalMassacre class extends both EventCard and HyperCard to represent the card "Magical Massacre" in the game.
 */
export class MagicalMassacre final: public EventCard, public HyperCard {
private: 
    static constexpr u16 ID = 13; ///< The ID of this specific card

    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_TOMOMO", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MagicalMassacre object.
     */
    MagicalMassacre():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
