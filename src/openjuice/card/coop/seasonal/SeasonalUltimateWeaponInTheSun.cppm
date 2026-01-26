/**
 * @file SeasonalUltimateWeaponInTheSun.cppm
 * @module openjuice.card.coop.seasonal:SeasonalUltimateWeaponInTheSun
 * @brief Implementation of the SeasonalUltimateWeaponInTheSun class.
 *
 * This file contains the implementation of the SeasonalUltimateWeaponInTheSun class, which represents the card "Ultimate Weapon in the Sun" (seasonal) in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.coop.seasonal:SeasonalUltimateWeaponInTheSun;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::coop::seasonal);

/**
 * @class SeasonalUltimateWeaponInTheSun
 * @brief Class representing the SeasonalUltimateWeaponInTheSun card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The SeasonalUltimateWeaponInTheSun class extends both BoostCard, HyperCard, and CoopCard to represent the card "Chaos Protect" in the game.
 */
export class SeasonalUltimateWeaponInTheSun final: public BoostCard, public HyperCard, public CoopCard {
public:
    static constexpr u16 ID = 1; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 5; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_SUMMER2018_ATTACKER", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SeasonalUltimateWeaponInTheSun object.
     */
    SeasonalUltimateWeaponInTheSun(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
