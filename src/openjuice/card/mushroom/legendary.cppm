/**
 * @file legendary.cppm
 * @module openjuice.card.mushroom.legendary
 * @brief Import of all Legendary Mushroom Cards.
 *
 * This file imports the modules for all Legendary Mushroom Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:mushroom.legendary;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

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
private:
    MUSHROOM_METADATA("CARD_SHROOM_LEGEND_STARS")
public:
    static constexpr u16 ID = Ops::to_underlying(LegendaryMushroomCard::Effect::STARS); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

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

/**
 * @class LegendaryWinsMushroom
 * @brief Class representing the LegendaryWinsMushroom card.
 *
 * @extends LegendaryMushroomCard
 *
 * The LegendaryWinsMushroom class extends LegendaryMushroomCard to represent the card 
 * providing the LegendaryMushroomCard::Effect::WINS effect in the game.
 */
export class LegendaryWinsMushroom final: public LegendaryMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_LEGEND_WINS")
public:
    static constexpr u16 ID = Ops::to_underlying(LegendaryMushroomCard::Effect::WINS); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a LegendaryWinsMushroom object.
     */
    LegendaryWinsMushroom(LegendaryMushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Legendary, WINS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
