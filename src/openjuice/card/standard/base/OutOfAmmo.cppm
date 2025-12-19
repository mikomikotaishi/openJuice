/**
 * @file OutOfAmmo.cppm
 * @module openjuice.card.standard.base.OutOfAmmo
 * @brief Implementation of the OutOfAmmo class.
 *
 * This file contains the implementation of the OutOfAmmo class, which represents the card "Out of Ammo" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base.OutOfAmmo;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::SpawnType;
using openjuice::engine::card::Rarity;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::base);

/**
 * @class OutOfAmmo
 * @brief Class representing the OutOfAmmo card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The OutOfAmmo class extends both EventCard and StandardCard to represent the card "Out of Ammo" in the game.
 */
export class OutOfAmmo final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 18; ///< The id of this specific card
private:
    static constexpr CardType CARD_TYPE = CardType::EVENT; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 5; ///< The cost of this specific card
    static constexpr u8 LEVEL = 2; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_OUTOFAMMO", "CARD_ARTIST_NERIUME");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise an OutOfAmmo object.
     */
    OutOfAmmo(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
