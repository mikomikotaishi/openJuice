/**
 * @file ChaoticRampage.cppm
 * @module openjuice.card.seasonal.ChaoticRampage
 * @brief Implementation of the ChaoticRampage class.
 *
 * This file contains the implementation of the ChaoticRampage class, which represents the card "Chaotic Rampage" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal.ChaoticRampage;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::seasonal);

/**
 * @class ChaoticRampage
 * @brief Class representing the ChaoticRampage card.
 *
 * @extends EventCard
 * @extends SeasonalCard
 *
 * The ChaoticRampage class extends both EventCard and SeasonalCard to represent the card "Chaotic Rampage" in the game.
 */
export class ChaoticRampage final: public EventCard, public SeasonalCard {
public:
    static constexpr u8 ID = 9; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_CHAOS_RAMPAGE", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ChaoticRampage object.
     */
    ChaoticRampage(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
