/**
 * @file ChaoticLaunch.cppm
 * @module openjuice.card.seasonal:ChaoticLaunch
 * @brief Implementation of the ChaoticLaunch class.
 *
 * This file contains the implementation of the ChaoticLaunch class, which represents the card "Chaotic Launch" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal:ChaoticLaunch;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class ChaoticLaunch
 * @brief Class representing the ChaoticLaunch card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The ChaoticLaunch class extends both EventCard and SeasonalCard to represent the card "Chaotic Launch" in the game.
 */
export class ChaoticLaunch final: public EventCard, public SeasonalCard {
public:
    static constexpr u8 ID = 5; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_CHAOS_LAUNCH", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ChaoticLaunch object.
     */
    ChaoticLaunch(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
