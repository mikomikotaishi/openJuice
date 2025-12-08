/**
 * @file Card.cppm
 * @module openjuice.engine.card.Card
 * @brief Definition of the Card abstract class and related enums.
 *
 * This file contains the definition of the Card abstract class and related enums, which represent different types of cards in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.Card;

import std;

export import :CardType;
export import :DeckPointError;
export import :MushroomType;
export import :Rarity;
export import :SpawnType;

import openjuice.engine.managers.TextManager;
import openjuice.engine.util.Interfaces;

using std::meta::IsBaseOfValue;

using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;
using openjuice::engine::util::interfaces::IFinalOnly;
using openjuice::engine::util::interfaces::IKeyQueryable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @class Card
 * @brief Abstract class representing a card.
 * 
 * The Card abstract class represents a card in the game with the following attributes: type, rarity, ID, and level.
 *
 * @implements IFinalOnly
 * @implements IKeyQueryable
 */
export class Card: public IFinalOnly, public IKeyQueryable {
private:
    const Expected<u8, DeckPointError> deckPoints; ///< The deck points of the card
    const Optional<Rarity> rarity; ///< The rarity of the card.
    const Optional<u16> cost; ///< The cost to play the card (nullopt if not constant)
    const Optional<u8> limitPerDeck; ///< The limit of the card per deck (nullopt if not a standard card)
    const u16 id; ///< The ID of the card.
    const CardType cardType; ///< The card type of the card.
    const SpawnType spawnType; ///< The spawn type of the card.
    const u8 level; ///< The level of the card.
protected:
    static constexpr StringView CARD_KEY = ""; ///< The key belonging to the card to query in TextManager
    static constexpr StringView ARTIST_KEY = ""; ///< The key belonging to the name of the artist to query in TextManager

    /**
     * @brief Default constructor to initialise a Card object.
     */
    Card():
        deckPoints{0}, rarity{nullopt}, cost{nullopt}, limitPerDeck{0},
        id{0}, cardType{static_cast<CardType>(0)}, spawnType{static_cast<SpawnType>(0)}, level{0} {}

    /**
     * @brief Virtual default destructor.
     */
    virtual ~Card() = default;
public:
    /**
     * @brief Constructor to initialise a Card object.
     *
     * @param id The ID of the card.
     * @param cardType The card type of the card.
     * @param spawnType The spawn type of the card.
     * @param rarity The rarity of the card.
     * @param cost The cost of the card.
     * @param level The level of the card.
     * @param limit The limit of the card per deck.
     * @param deckPoints The deck points of the card.
     */
    Card(u16 id, CardType cardType, SpawnType spawnType, Optional<Rarity> rarity, Optional<u16> cost, u8 level, Optional<u8> limit, Expected<u8, DeckPointError> deckPoints):
        deckPoints{std::util::move(deckPoints)}, rarity{rarity}, cost{cost}, limitPerDeck{limit},
        id{id}, cardType{cardType}, spawnType{spawnType}, level{level} {}

    GETTER(u16, Id, id);
    GETTER(CardType, CardType, cardType);
    GETTER(SpawnType, SpawnType, spawnType);
    GETTER(Optional<Rarity>, Rarity, rarity);
    GETTER(Optional<u16>, Cost, cost);
    GETTER(u8, Level, level);
    GETTER(Optional<u8>, LimitPerDeck, limitPerDeck);

    /**
     * @brief Get the deck points of the card.
     * @return The deck points of the card.
     *
     * Returns a signed integer:
     * DeckPointError::NOT_PLAYABLE_IN_COOP if the card cannot be played in co-op, DeckPointError::NOT_STANDARD_CARD if the card is not a Standard card, 
     * non-negative otherwise.
     */
    [[nodiscard]]
    Expected<u8, DeckPointError> getDeckPoints() const noexcept {
        return deckPoints;
    }

    /**
     * @brief Play the card.
     * 
     * This is a pure virtual function that must be implemented by derived classes.
     */
    virtual void play() const = 0;

    /**
     * @brief Get the name of the card.
     * @return The name of the card.
     */
    [[nodiscard]]
    virtual String getName() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardName(CARD_KEY);
        return String(result ? *result : "");
    }

    /**
     * @brief Get the description of the card.
     * @return The description of the card.
     */
    [[nodiscard]]
    virtual String getDescription() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardDescription(CARD_KEY);
        return String(result ? *result : "");
    }

    /**
     * @brief Get the flavour text of the card.
     * @return The flavour text of the card.
     */
    [[nodiscard]]
    String getFlavour() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardFlavour(CARD_KEY);
        return String(result ? *result : "");
    }

    /**
     * @brief Get the card artist name.
     * @return The card artist name.
     */
    [[nodiscard]]
    virtual String getArtistName() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardArtistName(ARTIST_KEY);
        return String(result ? *result : "");
    }
};

/**
 * @concept ExtendsCard
 * @brief Concept that checks if a type extends the Card class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsCard = IsBaseOfValue<Card, T>;

END_MODULE_NAMESPACE();
