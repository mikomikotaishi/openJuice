/**
 * @file Card.cppm
 * @module openjuice.engine.card:Card
 * @brief Definition of the Card abstract class and related enums.
 *
 * This file contains the definition of the Card abstract class and related enums, which represent different types of cards in the game.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.Card;

import stdx;

import openjuice.engine.managers;
import openjuice.engine.util;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::meta::IsBaseOfValue;

using openjuice::engine::managers::TextManager;
using openjuice::engine::util::IFinalOnly;
using openjuice::engine::util::IKeyQueryable;

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
export class [[nodiscard]] Card: public IFinalOnly, public IKeyQueryable {
public:
    /**
     * @enum Type
     * @brief Enumeration for card types.
     * 
     * The Card::Type enumeration defines the types of cards in the game.
     */
    enum class Type: u8 {
        BATTLE, ///< Battle card type.
        BOOST, ///< Boost card type.
        TRAP, ///< Trap card type.
        EVENT, ///< Event card type.
        GIFT, ///< Gift card type.
        BANNER, ///< Banner card type.
    };

    /**
     * @enum Spawn
     * @brief Enumeration for card spawn types.
     * 
     * The Spawn enumeration defines the spawn types of cards in the game.
     */
    enum class Spawn: u8 {
        STANDARD, ///< Standard spawn type.
        HYPER, ///< Hyper spawn type.
        CHARACTER_SPECIFIC, ///< Character-specific spawn type.
        SEASONAL, ///< Seasonal spawn type.
        MUSHROOM, ///< Mushroom spawn type.
        COOP, ///< Co-op spawn type.
        BOSS, ///< Boss spawn type.
        BOUNTY_HUNT, ///< Bounty Hunt spawn type.
        GENERIC, ///< Generic (placeholder) spawn type.
    };

    /**
     * @enum Rarity
     * @brief Enumeration for card rarities.
     * 
     * The Rarity enumeration defines the rarities of cards in the game.
     */
    enum class Rarity: u8 {
        NONE, ///< No rarity (for hyper cards).
        COMMON, ///< Common rarity.
        UNCOMMON, ///< Uncommon rarity.
        RARE, ///< Rare rarity.
    };

    /**
     * @enum DeckPointError
     * @brief Enumeration for deck point errors.
     * 
     * The DeckPointError enumeration defines the types of errors in retrieving deck points of a card.
     */
    enum class DeckPointError: u8 {
        NOT_PLAYABLE_IN_COOP, ///< Card cannot be played in Co-op mode
        NOT_STANDARD_CARD, ///< Card is not a Standard-type card
    };
private:
    const Expected<u8, DeckPointError> deckPoints; ///< The deck points of the card
    const Optional<Rarity> rarity; ///< The rarity of the card.
    const Optional<u16> cost; ///< The cost to play the card (nullopt if not constant)
    const Optional<u8> limitPerDeck; ///< The limit of the card per deck (nullopt if not a standard card)
    const u16 id; ///< The ID of the card.
    const Type cardType; ///< The card type of the card.
    const Spawn spawnType; ///< The spawn type of the card.
    const u8 level; ///< The level of the card.
protected:
    static constexpr StringView CARD_KEY = ""; ///< The key belonging to the card to query in TextManager
    static constexpr StringView ARTIST_KEY = ""; ///< The key belonging to the name of the artist to query in TextManager

    /**
     * @brief Default constructor to initialise a Card object.
     */
    Card():
        deckPoints{0}, rarity{nullopt}, cost{nullopt}, limitPerDeck{0},
        id{0}, cardType{static_cast<Card::Type>(0)}, spawnType{static_cast<Spawn>(0)}, level{0} {}

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
    Card(u16 id, Type cardType, Spawn spawnType, Optional<Rarity> rarity, Optional<u16> cost, u8 level, Optional<u8> limit, Expected<u8, DeckPointError> deckPoints):
        deckPoints{stdx::util::move(deckPoints)}, rarity{rarity}, cost{cost}, limitPerDeck{limit},
        id{id}, cardType{cardType}, spawnType{spawnType}, level{level} {}

    GETTER(u16, Id, id);
    GETTER(Type, Type, cardType);
    GETTER(Spawn, Spawn, spawnType);
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
    virtual String getName() const noexcept {
        return TextManager::getInstance()
            .getCardName(CARD_KEY)
            .value_or("");
    }

    /**
     * @brief Get the description of the card.
     * @return The description of the card.
     */
    [[nodiscard]]
    virtual String getDescription() const noexcept {
        return TextManager::getInstance()
            .getCardDescription(CARD_KEY)
            .value_or("");
    }

    /**
     * @brief Get the flavour text of the card.
     * @return The flavour text of the card.
     */
    [[nodiscard]]
    String getFlavour() const noexcept {
        return TextManager::getInstance()
            .getCardFlavour(CARD_KEY)
            .value_or("");
    }

    /**
     * @brief Get the card artist name.
     * @return The card artist name.
     */
    [[nodiscard]]
    virtual String getArtistName() const noexcept {
        return TextManager::getInstance()
            .getCardArtistName(ARTIST_KEY)
            .value_or("");
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

using openjuice::engine::card::Card;

template <>
struct Formatter<Card::Type> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Card::Type type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case Card::Type::BATTLE:
                name = "Battle";
                break;
            case Card::Type::BOOST:
                name = "Boost";
                break;
            case Card::Type::TRAP:
                name = "Trap";
                break;
            case Card::Type::EVENT:
                name = "Event";
                break;
            case Card::Type::GIFT:
                name = "Gift";
                break;
            case Card::Type::BANNER:
                name = "Banner";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<Card::Spawn> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Card::Spawn type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case Card::Spawn::STANDARD:
                name = "Standard";
                break;
            case Card::Spawn::HYPER:
                name = "Hyper";
                break;
            case Card::Spawn::CHARACTER_SPECIFIC:
                name = "Character-specific";
                break;
            case Card::Spawn::SEASONAL:
                name = "Seasonal";
                break;
            case Card::Spawn::MUSHROOM:
                name = "Mushroom";
                break;
            case Card::Spawn::COOP:
                name = "Co-op";
                break;
            case Card::Spawn::BOSS:
                name = "Boss";
                break;
            case Card::Spawn::BOUNTY_HUNT:
                name = "Bounty Hunt";
                break;
            case Card::Spawn::GENERIC:
                name = "Generic";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<Card::Rarity> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Card::Rarity type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case Card::Rarity::NONE:
                name = "None";
                break;
            case Card::Rarity::COMMON:
                name = "Common";
                break;
            case Card::Rarity::UNCOMMON:
                name = "Uncommon";
                break;
            case Card::Rarity::RARE:
                name = "Rare";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<Card::DeckPointError> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Card::DeckPointError err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case Card::DeckPointError::NOT_PLAYABLE_IN_COOP:
                name = "Not playable in co-op";
                break;
            case Card::DeckPointError::NOT_STANDARD_CARD:
                name = "Not standard card";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(Card::Type);
SPECIALISE_FORMATTER(Card::Spawn);
SPECIALISE_FORMATTER(Card::Rarity);
SPECIALISE_FORMATTER(Card::DeckPointError);
