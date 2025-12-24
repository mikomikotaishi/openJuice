/**
 * @file TacticalRetreat.cppm
 * @module openjuice.card.standard.mixedbooster:TacticalRetreat
 * @brief Implementation of the TacticalRetreat class.
 *
 * This file contains the implementation of the TacticalRetreat class, which represents the card "Tactical Retreat" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster:TacticalRetreat;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::mixedbooster);

/**
 * @class TacticalRetreat
 * @brief Class representing the TacticalRetreat card.
 *
 * @extends BattleCard
 * @extends StandardCard
 *
 * The TacticalRetreat class extends both BattleCard and StandardCard to represent the card "Tactical Retreat" in the game.
 */
export class TacticalRetreat final: public BattleCard, public StandardCard {
public:
    static constexpr u16 ID = 48; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BATTLE; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = nullopt; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BATTLE_RETREAT", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a TacticalRetreat object.
     */
    TacticalRetreat():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
