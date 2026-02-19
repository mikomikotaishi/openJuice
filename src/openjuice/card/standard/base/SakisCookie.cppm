/**
 * @file SakisCookie.cppm
 * @module openjuice.card.standard.base:SakisCookie
 * @brief Implementation of the SakisCookie class.
 *
 * This file contains the implementation of the SakisCookie class, which represents the card "Saki's Cookie" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base:SakisCookie;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class SakisCookie
 * @brief Class representing the SakisCookie card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The SakisCookie class extends both BoostCard and StandardCard to represent the card "Saki's Cookie" in the game.
 */
export class SakisCookie final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 2; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 3; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BOOST_COOKIE", "CARD_ARTIST_TORI");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SakisCookie object.
     */
    SakisCookie(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
