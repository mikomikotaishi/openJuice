/**
 * @file SealedMemories.cppm
 * @module openjuice.card.standard.mixedbooster.SealedMemories
 * @brief Implementation of the SealedMemories class.
 *
 * This file contains the implementation of the SealedMemories class, which represents the card "Sealed Memories" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.mixedbooster.SealedMemories;

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
 * @class SealedMemories
 * @brief Class representing the SealedMemories card.
 *
 * @extends TrapCard
 * @extends StandardCard
 *
 * The SealedMemories class extends both TrapCard and StandardCard to represent the card "Sealed Memories" in the game.
 */
export class SealedMemories final: public TrapCard, public StandardCard {
private:
    static constexpr u16 ID = 51; ///< The id of this specific card

    static constexpr CardType CARD_TYPE = CardType::TRAP; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = Rarity::UNCOMMON; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 3; ///< The limit of this specific card
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_TRAP_SEALEDMEMORIES", "CARD_ARTIST_HONO");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a SealedMemories object.
     */
    SealedMemories(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
