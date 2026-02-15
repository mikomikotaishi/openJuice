/**
 * @file Exchange.cppm
 * @module openjuice.card.standard.expansion:Exchange
 * @brief Implementation of the Exchange class.
 *
 * This file contains the implementation of the Exchange class, which represents the card "Exchange" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:Exchange;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class Exchange
 * @brief Class representing the Exchange card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Exchange class extends both TrapCard and StandardCard to represent the card "Exchange" in the game.
 */
export class Exchange final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 33; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_EXCHANGE", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Exchange object.
     */
    Exchange(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
