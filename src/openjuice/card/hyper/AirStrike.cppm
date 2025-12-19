/**
 * @file AirStrike.cppm
 * @module openjuice.card.hyper.AirStrike
 * @brief Implementation of the AirStrike class.
 *
 * This file contains the implementation of the AirStrike class, which represents the card "Air Strike" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.AirStrike;

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
 * @class AirStrike
 * @brief Class representing the AirStrike card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The AirStrike class extends both EventCard and HyperCard to represent the card "Air Strike" in the game.
 */
export class AirStrike final: public EventCard, public HyperCard {
public:
    static constexpr u16 ID = 6; ///< The ID of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_FERNET", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a AirStrike object.
     */
    AirStrike():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
