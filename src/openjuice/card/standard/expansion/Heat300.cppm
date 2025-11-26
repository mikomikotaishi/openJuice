/**
 * @file Heat300.cppm
 * @module openjuice.card.standard.expansion.Heat300
 * @brief Implementation of the Heat300 class.
 *
 * This file contains the implementation of the Heat300 class, which represents the card "Heat 300%" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion.Heat300;

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
 * @class Heat300
 * @brief Class representing the Heat300 card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The Heat300 class extends both TrapCard and StandardCard to represent the card "Heat 300%" in the game.
 */
export class Heat300 final: public TrapCard, public StandardCard {
private:
    static constexpr u16 ID = 31; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::TRAP_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_HEAT300", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Heat300 object.
     */
    Heat300(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
