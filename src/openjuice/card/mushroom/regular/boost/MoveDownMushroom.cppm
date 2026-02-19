/**
 * @file MoveDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost:MoveDownMushroom
 * @brief Implementation of the MoveDownMushroom class.
 *
 * This file contains the implementation of the MoveDownMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomCard::Effect::MOVE_DOWN effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost:MoveDownMushroom;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class MoveDownMushroom
 * @brief Class representing the MoveDownMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The MoveDownMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::MOVE_DOWN effect in the game.
 */
export class MoveDownMushroom final: public BoostMushroomCard {
public:
    static constexpr u16 ID = stdx::util::to_underlying(BoostMushroomCard::Effect::MOVE_DOWN); ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_MOVEDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a MoveDownMushroom object.
     */
    MoveDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, MOVE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
