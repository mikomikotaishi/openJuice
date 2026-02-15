/**
 * @file MiosChristmasCake.cppm
 * @module openjuice.card.character:MiosChristmasCake
 * @brief Implementation of the MiosChristmasCake class.
 *
 * This file contains the implementation of the MiosChristmasCake class, which represents the card "Mio's Christmas Cake" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.character:MiosChristmasCake;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::character);

/**
 * @class MiosChristmasCake
 * @brief Class representing the MiosChristmasCake card.
 *
 * @extends BoostCard
 * @extends CharacterSpecificCard
 *
 * The MiosChristmasCake class extends both BoostCard and CharacterSpecificCard to represent the card "Mio's Christmas Cake" in the game.
 */
export class MiosChristmasCake final: public BoostCard, public CharacterSpecificCard {
public:
    static constexpr u8 ID = 1; ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::CHARACTER_SPECIFIC; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_XMASCAKE", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MiosChristmasCake object.
     */
    MiosChristmasCake():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
