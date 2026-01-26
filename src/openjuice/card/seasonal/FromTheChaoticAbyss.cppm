/**
 * @file FromTheChaoticAbyss.cppm
 * @module openjuice.card.seasonal:FromTheChaoticAbyss
 * @brief Implementation of the FromTheChaoticAbyss class.
 *
 * This file contains the implementation of the FromTheChaoticAbyss class, which represents the card "From the Chaotic Abyss" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal:FromTheChaoticAbyss;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class FromTheChaoticAbyss
 * @brief Class representing the FromTheChaoticAbyss card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The FromTheChaoticAbyss class extends both EventCard and SeasonalCard to represent the card "From the Chaotic Abyss" in the game.
 */
export class FromTheChaoticAbyss final: public EventCard, public SeasonalCard {
public:
    static constexpr u8 ID = 8; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_CHAOS_ABYSS", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a FromTheChaoticAbyss object.
     */
    FromTheChaoticAbyss(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
