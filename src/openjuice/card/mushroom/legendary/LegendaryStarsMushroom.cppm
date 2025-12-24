/**
 * @file LegendaryStarsMushroom.cppm
 * @module openjuice.card.mushroom.legendary:LegendaryStarsMushroom
 * @brief Implementation of the LegendaryStarsMushroom class.
 *
 * This file contains the implementation of the LegendaryStarsMushroom class, which is a
 * Legendary Mushroom providing the LegendaryMushroomType::Stars effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.legendary:LegendaryStarsMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::LegendaryMushroomColour;
using openjuice::engine::card::LegendaryMushroomType;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;
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
 * providing the LegendaryMushroomType::STARS effect in the game.
 */
export class LegendaryStarsMushroom final: public LegendaryMushroomCard {
public:
    static constexpr u16 ID = std::util::to_underlying(LegendaryMushroomType::STARS); ///< The ID of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::GIFT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_LEGEND_STARS");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a LegendaryStarsMushroom object.
     */
    LegendaryStarsMushroom(LegendaryMushroomColour colour):
        SET_MUSHROOM_STATS(Legendary, STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
