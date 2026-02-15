/**
 * @file LittleWar.cppm
 * @module openjuice.card.standard.base:LittleWar
 * @brief Implementation of the LittleWar class.
 *
 * This file contains the implementation of the LittleWar class, which represents the card "Little War" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:LittleWar;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class LittleWar
 * @brief Class representing the LittleWar card.
 *
 * @extends EventCard
 * @extends @StandardCard
 *
 * The LittleWar class extends both EventCard and StandardCard to represent the card "Little War" in the game.
 */
export class LittleWar final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 20; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 50; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_EVENT_LITTLEWAR", "CARD_ARTIST_TORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LittleWar object.
     */
    LittleWar(): SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
