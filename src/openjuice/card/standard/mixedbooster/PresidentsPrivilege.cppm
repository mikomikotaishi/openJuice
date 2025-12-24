/**
 * @file PresidentsPrivilege.cppm
 * @module openjuice.card.standard.mixedbooster:PresidentsPrivilege
 * @brief Implementation of the PresidentsPrivilege class.
 *
 * This file contains the implementation of the PresidentsPrivilege class, which represents the card "President's Privilege" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster:PresidentsPrivilege;

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
 * @class PresidentsPrivilege
 * @brief Class representing the PresidentsPrivilege card.
 *
 * @extends BoostCard
 * @extends StandardCard
 *
 * The PresidentsPrivilege class extends both BoostCard and StandardCard to represent the card "President's Privilege" in the game.
 */
export class PresidentsPrivilege final: public BoostCard, public StandardCard {
public:
    static constexpr u16 ID = 46; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 10; ///< The cost of this specific card
    static constexpr u8 LEVEL = 4; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 2; ///< The deck points of this specific card

    CARD_METADATA("CARD_BOOST_PRESIDENT", "CARD_ARTIST_JUNPYON");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a PresidentsPrivilege object.
     */
    PresidentsPrivilege(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
