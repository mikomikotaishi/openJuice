/**
 * @file LifeguardOnTheWhiteBeach.cppm
 * @module openjuice.card.coop.role:LifeguardOnTheWhiteBeach
 * @brief Implementation of the LifeguardOnTheWhiteBeach class.
 *
 * This file contains the implementation of the LifeguardOnTheWhiteBeach class, which represents the card "Lifeguard on the White Beach" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.coop.role:LifeguardOnTheWhiteBeach;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::role);

/**
 * @class LifeguardOnTheWhiteBeach
 * @brief Class representing the LifeguardOnTheWhiteBeach card.
 *
 * @extends EventCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The LifeguardOnTheWhiteBeach class extends both EventCard, HyperCard, and SeasonalCard to represent the card "Lifeguard on the White Beach" in the game.
 */
export class LifeguardOnTheWhiteBeach final: public EventCard, public HyperCard, public CoopCard {
public:
    static constexpr u8 ID = 2; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_COOP_CLASS_GUARDIAN", "CARD_ARTIST_HEXUN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LifeguardOnTheWhiteBeach object.
     */
    LifeguardOnTheWhiteBeach(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
