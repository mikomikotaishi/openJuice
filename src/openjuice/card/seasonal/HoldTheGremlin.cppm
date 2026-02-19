/**
 * @file HoldTheGremlin.cppm
 * @module openjuice.card.seasonal:HoldTheGremlin
 * @brief Implementation of the HoldTheGremlin class.
 *
 * This file contains the implementation of the HoldTheGremlin class, which represents the card "Hold the Gremlin" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal:HoldTheGremlin;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class HoldTheGremlin
 * @brief Class representing the HoldTheGremlin card.
 *
 * @extends GiftCard
 * @extends SeasonalCard
 *
 * The HoldTheGremlin class extends both GiftCard and SeasonalCard to represent the card "Hold the Gremlin" in the game.
 */
export class HoldTheGremlin final: public GiftCard, public SeasonalCard {
public:
    static constexpr u8 ID = 12; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_CHAOS_GIFT_HOTPOTATO", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a HoldTheGremlin object.
     */
    HoldTheGremlin(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
