/**
 * @file LegendaryStarsMushroom.cppm
 * @module openjuice.card.mushroom.legendary:LegendaryStarsMushroom
 * @brief Implementation of the LegendaryStarsMushroom class.
 *
 * This file contains the implementation of the LegendaryStarsMushroom class, which is a
 * Legendary Mushroom providing the LegendaryMushroomCard::Effect::STARS effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.legendary:LegendaryStarsMushroom;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::legendary);

/**
 * @class LegendaryStarsMushroom
 * @brief Class representing the LegendaryStarsMushroom card.
 *
 * @extends LegendaryMushroomCard
 *
 * The LegendaryStarsMushroom class extends LegendaryMushroomCard to represent the card 
 * providing the LegendaryMushroomCard::Effect::STARS effect in the game.
 */
export class LegendaryStarsMushroom final: public LegendaryMushroomCard {
public:
    static constexpr u16 ID = stdx::util::to_underlying(LegendaryMushroomCard::Effect::STARS); ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_LEGEND_STARS");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LegendaryStarsMushroom object.
     */
    LegendaryStarsMushroom(LegendaryMushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Legendary, STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
