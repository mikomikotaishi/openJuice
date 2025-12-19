/**
 * @file ConfusionMushroom.cppm
 * @module openjuice.card.mushroom.regular.boost.ConfusionMushroom
 * @brief Implementation of the ConfusionMushroom class.
 *
 * This file contains the implementation of the ConfusionMushroom class, which is a
 * Boost Mushroom providing the BoostMushroomType::Confusion effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.boost.ConfusionMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::BoostMushroomType;
using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class ConfusionMushroom
 * @brief Class representing the ConfusionMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The ConfusionMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomType::CONFUSION effect in the game.
 */
export class ConfusionMushroom final: public BoostMushroomCard {
public:
    static constexpr u16 ID = std::util::to_underlying(BoostMushroomType::CONFUSION); ///< The ID of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_CONFUSION");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ConfusionMushroom object.
     */
    ConfusionMushroom(MushroomColour colour):
        SET_MUSHROOM_STATS(Boost, CONFUSION) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
