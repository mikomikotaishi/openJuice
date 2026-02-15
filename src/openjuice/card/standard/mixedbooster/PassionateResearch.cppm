/**
 * @file PassionateResearch.cppm
 * @module openjuice.card.standard.mixedbooster:PassionateResearch
 * @brief Implementation of the PassionateResearch class.
 *
 * This file contains the implementation of the PassionateResearch class, which represents the card "Passionate Research" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster:PassionateResearch;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::mixedbooster);

/**
 * @class PassionateResearch
 * @brief Class representing the PassionateResearch card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The PassionateResearch class extends both BoostCard and StandardCard to represent the card "Passionate Research" in the game.
 */
export class PassionateResearch final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 45; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_PASSIONATE", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a PassionateResearch object.
     */
    PassionateResearch(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
