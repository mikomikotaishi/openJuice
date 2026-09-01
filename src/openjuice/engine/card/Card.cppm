/**
 * @file Card.cppm
 * @module openjuice.engine.card:Card
 * @brief Definition of the Card abstract class and related enums.
 *
 * This file contains the definition of the Card abstract class and related enums, which represent different types of cards in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.Card;

import stdx;

import openjuice.engine.localization;

using openjuice::engine::localization::LocalizationService;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card);

/**
 * @class Card
 * @brief Abstract class representing a card.
 * 
 * The Card abstract class represents a card in the game with the following attributes: type, rarity, ID, and level.
 */
export class [[nodiscard]] Card {
public:
    /**
     * @struct Metadata
     * @brief 
     */
    struct Metadata {
        StringView cardKey; ///< The localization key of the card.
        StringView artistKey; ///< The localization key of the card's artist.
    };

    /**
     * @enum Of
     * @brief Enumeration for card types.
     */
    enum class Of: u8 {
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
    const Of cardType; ///< The card type of the card.
    const Spawn spawnType; ///< The spawn type of the card.
    const u8 level; ///< The level of the card.
protected:
    const Metadata metadata;

    /**
     * @brief Virtual default destructor.
     */
    virtual ~Card() = default;
public:
    /**
     * @brief Constructor to initialize a Card object.
     * @param id The ID of the card.
     * @param cardType The card type of the card.
     * @param spawnType The spawn type of the card.
     * @param rarity The rarity of the card.
     * @param cost The cost of the card.
     * @param level The level of the card.
     * @param limit The limit of the card per deck.
     * @param deckPoints The deck points of the card.
     * @param metadata The card metadata.
     */
    Card(u16 id, Of cardType, Spawn spawnType, Optional<Rarity> rarity, Optional<u16> cost, u8 level, Optional<u8> limit, Expected<u8, DeckPointError> deckPoints, Metadata metadata):
        deckPoints{Ops::move(deckPoints)}, rarity{rarity}, cost{cost}, limitPerDeck{limit},
        id{id}, cardType{cardType}, spawnType{spawnType}, level{level}, metadata{metadata} {}

    [[nodiscard]]
    u16 getId() const noexcept {
        return id;
    }

    [[nodiscard]]
    Of getType() const noexcept {
        return cardType;
    }

    [[nodiscard]]
    Spawn getSpawn() const noexcept {
        return spawnType;
    }

    [[nodiscard]]
    Optional<Rarity> getRarity() const noexcept {
        return rarity;
    }

    [[nodiscard]]
    Optional<u16> getCost() const noexcept {
        return cost;
    }

    [[nodiscard]]
    u8 getLevel() const noexcept {
        return level;
    }

    [[nodiscard]]
    Optional<u8> getLimitPerDeck() const noexcept {
        return limitPerDeck;
    }

    /**
     * @brief Get the deck points of the card.
     * @return The deck points of the card.
     *
     * Returns a signed integer:
     * DeckPointError::NOT_PLAYABLE_IN_COOP if the card cannot be played in co-op,
     * DeckPointError::NOT_STANDARD_CARD if the card is not a Standard card, 
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
    virtual String getName(const LocalizationService& loc) const noexcept {
        return loc
            .getCardName(metadata.cardKey)
            .value_or("");
    }

    /**
     * @brief Get the description of the card.
     * @return The description of the card.
     */
    [[nodiscard]]
    virtual String getDescription(const LocalizationService& loc) const noexcept {
        return loc
            .getCardDescription(metadata.cardKey)
            .value_or("");
    }

    /**
     * @brief Get the flavour text of the card.
     * @return The flavour text of the card.
     */
    [[nodiscard]]
    String getFlavour(const LocalizationService& loc) const noexcept {
        return loc
            .getCardFlavour(metadata.cardKey)
            .value_or("");
    }

    /**
     * @brief Get the card artist name.
     * @return The card artist name.
     */
    [[nodiscard]]
    virtual String getArtistName(const LocalizationService& loc) const noexcept {
        return loc
            .getCardArtistName(metadata.artistKey)
            .value_or("");
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::Card;

namespace stdx::fmt {
    template <>
    struct Formatter<Card::Of> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(Card::Of type, FormatContext& ctx) {
            StringView name;
            switch (type) {
                case Card::Of::BATTLE:
                    name = "Battle";
                    break;
                case Card::Of::BOOST:
                    name = "Boost";
                    break;
                case Card::Of::TRAP:
                    name = "Trap";
                    break;
                case Card::Of::EVENT:
                    name = "Event";
                    break;
                case Card::Of::GIFT:
                    name = "Gift";
                    break;
                case Card::Of::BANNER:
                    name = "Banner";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };

    template <>
    struct Formatter<Card::Spawn> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(Card::Spawn type, FormatContext& ctx) {
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
            }
            return format_to(ctx.out(), "{}", name);
        }
    };

    template <>
    struct Formatter<Card::Rarity> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(Card::Rarity type, FormatContext& ctx) {
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
            }
            return format_to(ctx.out(), "{}", name);
        }
    };

    template <>
    struct Formatter<Card::DeckPointError> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(Card::DeckPointError err, FormatContext& ctx) {
            StringView name;
            switch (err) {
                case Card::DeckPointError::NOT_PLAYABLE_IN_COOP:
                    name = "Not playable in co-op";
                    break;
                case Card::DeckPointError::NOT_STANDARD_CARD:
                    name = "Not standard card";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(Card::Of);
SPECIALIZE_FORMATTER(Card::Spawn);
SPECIALIZE_FORMATTER(Card::Rarity);
SPECIALIZE_FORMATTER(Card::DeckPointError);
