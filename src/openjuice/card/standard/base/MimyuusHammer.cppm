/**
 * @file MimyuusHammer.cppm
 * @module openjuice.card.standard.base:MimyuusHammer
 * @brief Implementation of the MimyuusHammer class.
 *
 * This file contains the implementation of the MimyuusHammer class, which represents the card "Mimyuu's Hammer" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:MimyuusHammer;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class MimyuusHammer
 * @brief Class representing the MimyuusHammer card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The MimyuusHammer class extends both TrapCard and StandardCard to represent the card "Mimyuu's Hammer" in the game.
 */
export class MimyuusHammer final: public TrapCard, public StandardCard {
public:
    static constexpr u16 ID = 12; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::TRAP; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_TRAP_MIMYUU", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MimyuusHammer object.
     */
    MimyuusHammer(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
