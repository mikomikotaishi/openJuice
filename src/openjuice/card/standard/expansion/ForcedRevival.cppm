/**
 * @file ForcedRevival.cppm
 * @module openjuice.card.standard.expansion.ForcedRevival
 * @brief Implementation of the ForcedRevival class.
 *
 * This file contains the implementation of the ForcedRevival class, which represents the card "Forced Revival" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion.ForcedRevival;

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

// TODO: Implement co-op stats

/**
 * @class ForcedRevival
 * @brief Class representing the ForcedRevival card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The ForcedRevival class extends both EventCard and StandardCard to represent the card "Forced Revival" in the game.
 */
export class ForcedRevival final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 40; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_FORCEDREVIVAL", "CARD_ARTIST_KITSUNE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ForcedRevival object.
     */
    ForcedRevival(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
