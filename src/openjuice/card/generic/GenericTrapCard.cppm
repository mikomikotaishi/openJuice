/**
 * @file GenericTrapCard.cppm
 * @module openjuice.card.generic:GenericTrapCard
 * @brief Implementation of the GenericTrapCard class.
 *
 * This file contains the implementation of the GenericTrapCard class, which represents a generic Trap card.
 */

module;

#include "Macros.hpp"

export module openjuice.card.generic:GenericTrapCard;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::generic);

/**
 * @class GenericTrapCard
 * @brief Class representing the GenericTrapCard card.
 *
 * @extends TrapCard
 * @extends GenericCard
 *
 * The GenericTrapCard class extends TrapCard and GenericCard, and represents a generic Trap card.
 */
export class GenericTrapCard final: public TrapCard, public GenericCard {
public:
    static constexpr u8 ID = std::util::to_underlying(CardType::TRAP); ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::TRAP; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_TRAP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericTrapCard object.
     */
    GenericTrapCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
