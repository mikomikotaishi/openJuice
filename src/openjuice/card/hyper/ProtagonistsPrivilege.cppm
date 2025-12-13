/**
 * @file ProtagonistsPrivilege.cppm
 * @module openjuice.card.hyper.ProtagonistsPrivilege
 * @brief Implementation of the ProtagonistsPrivilege class.
 *
 * This file contains the implementation of the ProtagonistsPrivilege class, which represents the card "Protagonist's Privilege" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.hyper.ProtagonistsPrivilege;

import std;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::CardType;
using openjuice::engine::card::DeckPointError;
using openjuice::engine::card::Rarity;
using openjuice::engine::card::SpawnType;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::hyper);

/**
 * @class ProtagonistsPrivilege
 * @brief Class representing the ProtagonistsPrivilege card.
 *
 * @extends BoostCard
 * @extends HyperCard
 *
 * The ProtagonistsPrivilege class extends both BoostCard and HyperCard to represent the card "Protagonist's Privilege" in the game.
 */
export class ProtagonistsPrivilege final: public BoostCard, public HyperCard {
private: 
    static constexpr u16 ID = 1; ///< The ID of this specific card

    static constexpr CardType CARD_TYPE = CardType::BOOST; ///< The card type of this specific card
    static constexpr SpawnType SPAWN_TYPE = SpawnType::HYPER; ///< The spawn type of this specific card
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 20; ///< The cost of this specific card
    static constexpr u8 LEVEL = 3; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    CARD_METADATA("CARD_HYPER_KAI", "CARD_ARTIST_NERIUME");///< The key belonging to the card to query in TextManager
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a ProtagonistsPrivilege object.
     */
    ProtagonistsPrivilege():
        SET_CARD_STATS() {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
