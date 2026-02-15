/**
 * @file GenericBannerCard.cppm
 * @module openjuice.card.generic:GenericBannerCard
 * @brief Implementation of the GenericBannerCard class.
 *
 * This file contains the implementation of the GenericBannerCard class, which represents a generic Banner card.
 */

module;

#include "Macros.hpp"

export module openjuice.card.generic:GenericBannerCard;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::generic);

/**
 * @class GenericBannerCard
 * @brief Class representing the GenericBannerCard card.
 *
 * @extends BannerCard
 * @extends GenericCard
 *
 * The GenericBannerCard class extends BannerCard and GenericCard, and represents a generic Banner card.
 */
export class GenericBannerCard final: public BannerCard, public GenericCard {
public:
    static constexpr u8 ID = stdx::util::to_underlying(Card::Type::BANNER); ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BANNER; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::GENERIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("", "CARD_GENERIC_BANNER");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GenericBannerCard object.
     */
    GenericBannerCard(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
