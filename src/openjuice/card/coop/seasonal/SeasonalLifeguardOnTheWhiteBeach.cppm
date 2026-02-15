/**
 * @file SeasonalLifeguardOnTheWhiteBeach.cppm
 * @module openjuice.card.coop.seasonal:SeasonalLifeguardOnTheWhiteBeach
 * @brief Implementation of the SeasonalLifeguardOnTheWhiteBeach class.
 *
 * This file contains the implementation of the SeasonalLifeguardOnTheWhiteBeach class, which represents the card "Lifegurad on the White Beach" (seasonal) in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.coop.seasonal:SeasonalLifeguardOnTheWhiteBeach;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::seasonal);

/**
 * @class SeasonalLifeguardOnTheWhiteBeach
 * @brief Class representing the SeasonalLifeguardOnTheWhiteBeach card.
 *
 * @extends EventCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalLifeguardOnTheWhiteBeach class extends both EventCard, HyperCard, and CoopCard to represent the card "Lifeguard on the White Beach" (seasonal) in the game.
 */
export class SeasonalLifeguardOnTheWhiteBeach final: public EventCard, public HyperCard, public CoopCard {
public:
    static constexpr u16 ID = 2; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_SUMMER2018_DEFENDER", "CARD_ARTIST_HEXUN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SeasonalLifeguardOnTheWhiteBeach object.
     */
    SeasonalLifeguardOnTheWhiteBeach(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
