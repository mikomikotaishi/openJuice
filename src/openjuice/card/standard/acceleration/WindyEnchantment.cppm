/**
 * @file WindyEnchantment.cppm
 * @module openjuice.card.standard.acceleration.WindyEnchantment
 * @brief Implementation of the WindyEnchantment class.
 *
 * This file contains the implementation of the WindyEnchantment class, which represents the card "Windy Enchantment" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration.WindyEnchantment;

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
 * @class WindyEnchantment
 * @brief Class representing the WindyEnchantment card.
 *
 * @extends GiftCard
 * @extends StandardCard
 *
 * The WindyEnchantment class extends both GiftCard and StandardCard to represent the card "Windy Enchantment" in the game.
 */
export class WindyEnchantment final: public GiftCard, public StandardCard {
private:
    static constexpr u16 ID = 65; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::GIFT_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_GIFT_WINDYENCHANTMENT", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a WindyEnchantment object.
     */
    WindyEnchantment(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
