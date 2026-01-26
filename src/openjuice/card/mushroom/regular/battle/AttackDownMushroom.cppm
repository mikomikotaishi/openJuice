/**
 * @file AttackDownMushroom.cppm
 * @module openjuice.card.mushroom.regular.battle:AttackDownMushroom
 * @brief Implementation of the AttackDownMushroom class.
 *
 * This file contains the implementation of the AttackDownMushroom class, which is a
 * Battle Mushroom providing the BattleMushroomCard::Effect::ATTACK_DOWN effect in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.mushroom.regular.battle:AttackDownMushroom;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::BattleMushroomCard;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::battle);

/**
 * @class AttackDownMushroom
 * @brief Class representing the AttackDownMushroom card.
 *
 * @extends BattleMushroomCard
 *
 * The AttackDownMushroom class extends BattleMushroomCard to represent the card 
 * providing the BattleMushroomCard::Effect::ATTACK_DOWN effect in the game.
 */
export class AttackDownMushroom final: public BattleMushroomCard {
public:
    static constexpr u16 ID = std::util::to_underlying(BattleMushroomCard::Effect::ATTACK_DOWN); ///< The ID of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BATTLE; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    MUSHROOM_METADATA("CARD_SHROOM_ATTACKDOWN");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a AttackDownMushroom object.
     */
    AttackDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Battle, ATTACK_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
