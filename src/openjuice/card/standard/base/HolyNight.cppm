/**
 * @file HolyNight.cppm
 * @module openjuice.card.standard.base:HolyNight
 * @brief Implementation of the HolyNight class.
 *
 * This file contains the implementation of the HolyNight class, which represents the card "Holy Night" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:HolyNight;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class HolyNight
 * @brief Class representing the HolyNight card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The HolyNight class extends both EventCard and StandardCard to represent the card "Holy Night" in the game.
 */
export class HolyNight final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 17; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_EVENT_HOLYNIGHT", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HolyNight object.
     */
    HolyNight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
