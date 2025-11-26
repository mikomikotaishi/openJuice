/**
 * @file ForTheFutureOfTheToyStore.cppm
 * @module openjuice.card.standard.expansion.ForTheFutureOfTheToyStore
 * @brief Implementation of the ForTheFutureOfTheToyStore class.
 *
 * This file contains the implementation of the ForTheFutureOfTheToyStore class, which represents the card "For the Future of the Toy Store" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion.ForTheFutureOfTheToyStore;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

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
private:
    static constexpr u16 ID = 35; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::TRAP_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

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
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
