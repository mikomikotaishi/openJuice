/**
 * @file UnforgivingAvenger.cppm
 * @module openjuice.card.coop.role:UnforgivingAvenger
 * @brief Implementation of the UnforgivingAvenger class.
 *
 * This file contains the implementation of the UnforgivingAvenger class, which represents the card "Unforgiving Avenger" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.coop.role:UnforgivingAvenger;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::role);

/**
 * @class UnforgivingAvenger
 * @brief Class representing the UnforgivingAvenger card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The UnforgivingAvenger class extends both BoostCard, HyperCard, and SeasonalCard to represent the card "Unforgiving Avenger" in the game.
 */
export class UnforgivingAvenger final: public BoostCard, public HyperCard, public CoopCard {
public:
    static constexpr u8 ID = 4; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_COOP_CLASS_AVENGER", "CARD_ARTIST_LENDO_KHAR");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a UnforgivingAvenger object.
     */
    UnforgivingAvenger(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
