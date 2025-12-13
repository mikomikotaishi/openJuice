/**
 * @file Pudding.cppm
 * @module openjuice.card.standard.base.Pudding
 * @brief Implementation of the Pudding class.
 *
 * This file contains the implementation of the Pudding class, which represents the card "Pudding" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base.Pudding;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class Pudding
 * @brief Class representing the Pudding card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The Pudding class extends both BoostCard and StandardCard to represent the card "Pudding" in the game.
 */
export class Pudding final: public BoostCard, public StandardCard {
private:
    static constexpr u16 ID = 6; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 5; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_PUDDING", "CARD_ARTIST_TAMAKISEO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Pudding object.
     */
    Pudding(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
