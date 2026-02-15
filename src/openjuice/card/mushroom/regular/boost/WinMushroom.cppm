/**
 * @file WinMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost:WinMushroom
 * @brief Implementation of the WinMushroom class.
 *
 * This file contains the implementation of the WinMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomCard::Effect::WIN effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost:WinMushroom;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class WinMushroom
 * @brief Class representing the WinMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The WinMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::WIN effect in the game.
 */
export class WinMushroom final: public BoostMushroomCard {
public:
    static constexpr u16 ID = stdx::util::to_underlying(BoostMushroomCard::Effect::WIN); ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_WIN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a WinMushroom object.
     */
    WinMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, WIN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
