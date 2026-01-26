/**
 * @file ForTheFutureOfTheToyStore.cppm
 * @module openjuice.card.standard.expansion:ForTheFutureOfTheToyStore
 * @brief Implementation of the ForTheFutureOfTheToyStore class.
 *
 * This file contains the implementation of the ForTheFutureOfTheToyStore class, which represents the card "For the Future of the Toy Store" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:ForTheFutureOfTheToyStore;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class ForTheFutureOfTheToyStore
 * @brief Class representing the ForTheFutureOfTheToyStore card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The ForTheFutureOfTheToyStore class extends both TrapCard and StandardCard to represent the card "For the Future of the Toy Store" in the game.
 */
export class ForTheFutureOfTheToyStore final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 35; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_TOYSTORE", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ForTheFutureOfTheToyStore object.
     */
    ForTheFutureOfTheToyStore(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
