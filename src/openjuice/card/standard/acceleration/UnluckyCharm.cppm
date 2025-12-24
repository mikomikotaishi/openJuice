/**
 * @file UnluckyCharm.cppm
 * @module openjuice.card.standard.acceleration:UnluckyCharm
 * @brief Implementation of the UnluckyCharm class.
 *
 * This file contains the implementation of the UnluckyCharm class, which represents the card "Unlucky Charm" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration:UnluckyCharm;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::acceleration);

/**
 * @class UnluckyCharm
 * @brief Class representing the UnluckyCharm card.
 *
 * @extends GiftCard
 * @extends StandardCard
 *
 * The UnluckyCharm class extends both GiftCard and StandardCard to represent the card "Unlucky Charm" in the game.
 */
export class UnluckyCharm final: public GiftCard, public StandardCard {
public:
    static constexpr u16 ID = 64; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::GIFT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = nullopt; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_GIFT_UNLUCKYCHARM", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a UnluckyCharm object.
     */
    UnluckyCharm():
        SET_CARD_STATS() {}

    /**
      * @brief Play the card.
      */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
