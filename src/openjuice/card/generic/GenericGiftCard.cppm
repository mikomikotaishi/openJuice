/**
 * @file GenericGiftCard.cppm
 * @module openjuice.card.generic:GenericGiftCard
 * @brief Implementation of the GenericGiftCard class.
 *
 * This file contains the implementation of the GenericGiftCard class, which represents a generic Gift card.
 */

module;

#include "Macros.hpp"

export module openjuice.card.generic:GenericGiftCard;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::generic);

/**
 * @class GenericGiftCard
 * @brief Class representing the GenericGiftCard card.
 *
 * @extends GiftCard
 * @extends GenericCard
 *
 * The GenericGiftCard class extends GiftCard and GenericCard, and represents a generic Gift card.
 */
export class GenericGiftCard final: public GiftCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::GIFT); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_GIFT");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericGiftCard object.
     */
    GenericGiftCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
