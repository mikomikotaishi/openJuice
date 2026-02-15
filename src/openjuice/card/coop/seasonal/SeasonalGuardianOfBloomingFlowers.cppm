/**
 * @file SeasonalGuardianOfBloomingFlowers.cppm
 * @module openjuice.card.coop.seasonal:SeasonalGuardianOfBloomingFlowers
 * @brief Implementation of the SeasonalGuardianOfBloomingFlowers class.
 *
 * This file contains the implementation of the SeasonalGuardianOfBloomingFlowers class, which represents the card "Guardian of Blooming Flowers" (seasonal) in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.coop.seasonal:SeasonalGuardianOfBloomingFlowers;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::seasonal);

/**
 * @class SeasonalGuardianOfBloomingFlowers
 * @brief Class representing the SeasonalGuardianOfBloomingFlowers card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalGuardianOfBloomingFlowers class extends both BoostCard, HyperCard, and CoopCard to represent the card "Guardian of Blooming Flowers" (seasonal) in the game.
 */
export class SeasonalGuardianOfBloomingFlowers final: public BoostCard, public HyperCard, public CoopCard {
public:
    static constexpr u16 ID = 3; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_SUMMER2018_SUPPORT", "CARD_ARTIST_COFFGIRL");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SeasonalGuardianOfBloomingFlowers object.
     */
    SeasonalGuardianOfBloomingFlowers(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
