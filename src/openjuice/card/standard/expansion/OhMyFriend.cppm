/**
 * @file OhMyFriend.cppm
 * @module openjuice.card.standard.expansion:OhMyFriend
 * @brief Implementation of the OhMyFriend class.
 *
 * This file contains the implementation of the OhMyFriend class, which represents the card "Oh My Friend" in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.card.standard.expansion:OhMyFriend;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;

using namespace openjuice::engine::card::cardtypes;
using namespace openjuice::engine::card::spawntypes;

BEGIN_MODULE_NAMESPACE(openjuice::card::standard::expansion);

/**
 * @class OhMyFriend
 * @brief Class representing the OhMyFriend card.
 *
 * @extends EventCard
 * @extends StandardCard
 *
 * The OhMyFriend class extends both EventCard and StandardCard to represent the card "Oh My Friend" in the game.
 */
export class OhMyFriend final: public EventCard, public StandardCard {
public:
    static constexpr u16 ID = 41; ///< The id of this specific card
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::EVENT; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::STANDARD; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = Card::Rarity::RARE; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 30; ///< The cost of this specific card
    static constexpr u8 LEVEL = 1; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = 1; ///< The limit of this specific card
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_PLAYABLE_IN_COOP); ///< The deck points of this specific card

    CARD_METADATA("CARD_EVENT_OHMYFRIEND", "CARD_ARTIST_MEGANE");
    IMPLEMENT_NOOP();
public:
    /**
     * @brief Constructor to initialise a OhMyFriend object.
     */
    OhMyFriend(): 
        SET_CARD_STATS() {}
        
    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
