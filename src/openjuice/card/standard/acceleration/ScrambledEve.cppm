/**
 * @file ScrambledEve.cppm
 * @module openjuice.card.standard.acceleration:ScrambledEve
 * @brief Implementation of the ScrambledEve class.
 *
 * This file contains the implementation of the ScrambledEve class, which represents the card "Scrambled Eve" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration:ScrambledEve;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class ScrambledEve
 * @brief Class representing the ScrambledEve card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The ScrambledEve class extends both EventCard and StandardCard to represent the card "Scrambled Eve" in the game.
 */
export class ScrambledEve final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 62; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card
    
    CARD_METADATA("CARD_EVENT_SCRAMBLEDEVE", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ScrambledEve object.
     */
    ScrambledEve(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
