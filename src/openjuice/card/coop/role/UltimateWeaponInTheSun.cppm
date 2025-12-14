/**
 * @file UltimateWeaponInTheSun.cppm
 * @module openjuice.card.coop.role.UltimateWeaponInTheSun
 * @brief Implementation of the UltimateWeaponInTheSun class.
 *
 * This file contains the implementation of the UltimateWeaponInTheSun class, which represents the card "Ultimate Weapon in the Sun" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.coop.role.UltimateWeaponInTheSun;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper::seasonal);

/**
 * @class UltimateWeaponInTheSun
 * @brief Class representing the UltimateWeaponInTheSun card.
 *
 * @extends BoostCard
 * @extends HyperCard
 * @extends CoopCard
 *
 * The UltimateWeaponInTheSun class extends both BoostCard, HyperCard, and SeasonalCard to represent the card "Ultimate Weapon in the Sun" in the game.
 */
export class UltimateWeaponInTheSun final: public BoostCard, public HyperCard, public CoopCard {
private:
    static constexpr u8 ID = 1; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_COOP_CLASS_ATTACKER", "CARD_ARTIST_IKUSE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a UltimateWeaponInTheSun object.
     */
    UltimateWeaponInTheSun(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
