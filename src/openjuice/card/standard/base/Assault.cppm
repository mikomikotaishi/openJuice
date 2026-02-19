/**
 * @file Assault.cppm
 * @module openjuice.card.standard.base:Assault
 * @brief Implementation of the Assault class.
 *
 * This file contains the implementation of the Assault class, which represents the card "Assault" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:Assault;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class Assault
 * @brief Class representing the Assault card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Assault class extends both TrapCard and StandardCard to represent the "Assault" in the game.
 */
export class Assault final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 14; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_ASSAULT", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise an Assault object.
     */
    Assault():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {
        
    }
};

END_MODULE_NAMESPACE();
