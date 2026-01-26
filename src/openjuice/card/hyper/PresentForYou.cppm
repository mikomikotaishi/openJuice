/**
 * @file PresentForYou.cppm
 * @module openjuice.card.hyper:PresentForYou
 * @brief Implementation of the PresentForYou class.
 *
 * This file contains the implementation of the PresentForYou class, which represents the card "Present for You" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper:PresentForYou;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class PresentForYou
 * @brief Class representing the PresentForYou card.
 *
 * @extends EventCard
 * @extends HyperCard
 *
 * The PresentForYou class extends both EventCard and HyperCard to represent the card "Present for You" in the game.
 */
export class PresentForYou final: public EventCard, public HyperCard {
public:
    static constexpr u16 ID = 5; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_ARU", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a PresentForYou object.
     */
    PresentForYou():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
