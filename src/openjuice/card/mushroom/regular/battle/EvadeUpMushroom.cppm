/**
 * @file EvadeUpMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle:EvadeUpMushroom
 * @brief Implementation of the EvadeUpMushroom class.
 *
 * This file contains the implementation of the EvadeUpMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomCard::Effect::EVADE_UP effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle:EvadeUpMushroom;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class EvadeUpMushroom
 * @brief Class representing the EvadeUpMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The EvadeUpMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::EVADE_UP effect in the game.
 */
export class EvadeUpMushroom final: public BattleMushroomCard {
public:
    static constexpr u16 ID = stdx::util::to_underlying(BattleMushroomCard::Effect::EVADE_UP); ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_EVADEUP");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a EvadeUpMushroom object.
     */
    EvadeUpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, EVADE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
