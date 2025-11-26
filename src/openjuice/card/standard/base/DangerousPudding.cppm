/**
 * @file DangerousPudding.cppm
 * @module openjuice.card.standard.base.DangerousPudding
 * @brief Implementation of the DangerousPudding class.
 *
 * This file contains the implementation of the DangerousPudding class, which represents the card "Dangerous Pudding" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.base.DangerousPudding;

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
 * @class DangerousPudding
 * @brief Class representing the DangerousPudding card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The DangerousPudding class extends both TrapCard and StandardCard to represent the card "Dangerous Pudding" in the game.
 */
export class DangerousPudding final: public TrapCard, public StandardCard {
private:
    static constexpr u16 ID = 13; ///< The ID of this specific card

    static constexpr CardType CARD_TYPE = CardType::TRAP_CARD; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::COMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = 0; ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_DANGEROUSPUDDING", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a DangerousPudding object.
     */
    DangerousPudding():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const final {

    }
};

END_MODULE_NAMESPACE();
