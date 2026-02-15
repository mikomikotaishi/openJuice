/**
 * @file GiftExchange.cppm
 * @module openjuice.card.standard.base:GiftExchange
 * @brief Implementation of the GiftExchange class.
 *
 * This file contains the implementation of the GiftExchange class, which represents the card "Gift Exchange" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:GiftExchange;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class GiftExchange
 * @brief Class representing the GiftExchange card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The GiftExchange class extends both EventCard and StandardCard to represent the card "Gift Exchange" in the game.
 */
export class GiftExchange final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 19; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_EVENT_GIFTEXCHANGE", "CARD_ARTIST_TAMAKISEO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a GiftExchange object.
     */
    GiftExchange(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
