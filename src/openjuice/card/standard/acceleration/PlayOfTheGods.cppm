/**
 * @file PlayOfTheGods.cppm
 * @module openjuice.card.standard.acceleration:PlayOfTheGods
 * @brief Implementation of the PlayOfTheGods class.
 *
 * This file contains the implementation of the PlayOfTheGods class, which represents the card "Play of the Gods" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration:PlayOfTheGods;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class PlayOfTheGods
 * @brief Class representing the PlayOfTheGods card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The PlayOfTheGods class extends both EventCard and StandardCard to represent the card "Play of the Gods" in the game.
 */
export class PlayOfTheGods final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 61; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_PLAYOFTHEGODS", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a PlayOfTheGods object.
     */
    PlayOfTheGods(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
