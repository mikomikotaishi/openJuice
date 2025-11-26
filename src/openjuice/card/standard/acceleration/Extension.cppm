/**
 * @file Extension.cppm
 * @module openjuice.card.standard.acceleration.Extension
 * @brief Implementation of the Extension class.
 *
 * This file contains the implementation of the Extension class, which represents the card "Extension" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.acceleration.Extension;

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
 * @class Extension
 * @brief Class representing the Extension card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The Extension class extends both BattleCard and StandardCard to represent the card "Extension" in the game.
 */
export class Extension final: public BattleCard, public StandardCard {
private:
    static constexpr u16 ID = 57; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BATTLE_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card
    
    CARD_METADATA("CARD_BATTLE_EXTENSION", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a Extension object.
     */
    Extension(): 
        SET_CARD_STATS() {}
    
    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
