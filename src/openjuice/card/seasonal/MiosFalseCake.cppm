/**
 * @file MiosFalseCake.cppm
 * @module openjuice.card.seasonal.MiosFalseCake
 * @brief Implementation of the MiosFalseCake class.
 *
 * This file contains the implementation of the MiosFalseCake class, which represents the card "Mio's False Cake" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.seasonal.MiosFalseCake;

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
 * @class MiosFalseCake
 * @brief Class representing the MiosFalseCake card.
 *
 * @extends BoostCard
 * @extends SeasonalCard
 *
 * The MiosFalseCake class extends both BoostCard and SeasonalCard to represent the card "Mio's False Cake" in the game.
 */
export class MiosFalseCake final: public BoostCard, public SeasonalCard {
public:
    static constexpr u8 ID = 4; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::SEASONAL; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_WINTER2022_FALSECAKE", "CARD_ARTIST_YULAY_DEVLET");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MiosFalseCake object.
     */
    MiosFalseCake(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
