/**
 * @file StarBlastingLight.cppm
 * @module openjuice.card.standard.acceleration:StarBlastingLight
 * @brief Implementation of the StarBlastingLight class.
 *
 * This file contains the implementation of the StarBlastingLight class, which represents the card "Star-Blasting Light" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration:StarBlastingLight;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class StarBlastingLight
 * @brief Class representing the StarBlastingLight card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The StarBlastingLight class extends both EventCard and StandardCard to represent the card "Star-Blasting Light" in the game.
 */
export class StarBlastingLight final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 63; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 50; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_STARBLAZINGLIGHT", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a StarBlastingLight object.
     */
    StarBlastingLight(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
