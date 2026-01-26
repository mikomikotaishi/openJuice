/**
 * @file LegendaryMushroomCard.cppm
 * @module openjuice.engine.card.mushroom:LegendaryMushroomCard
 * @brief Definition of the LegendaryMushroomCard abstract class.
 *
 * This file contains the definition of the LegendaryMushroomCard abstract class, which represents a Legendary Mushroom card in the game.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.mushroom:LegendaryMushroomCard;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.cardtypes;
import openjuice.engine.card.spawntypes;
import openjuice.engine.managers;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::meta::IsBaseOfValue;

using openjuice::engine::card::cardtypes::GiftCard;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::managers::TextManager;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::mushroom);

/**
 * @class LegendaryMushroomCard
 * @brief Abstract class representing a Legendary Mushroom card.
 *
 * @extends GiftCard
 * @extends MushroomCard
 * 
 * The BoostMushroomCard abstract class extends the Card abstract class and represents a Legendary Mushroom card with specific attributes.
 */
export class LegendaryMushroomCard: public GiftCard, public MushroomCard {
public:
    /**
     * @enum Effect
     * @brief Enumeration for legendary mushroom types.
     * 
     * The Effect enumeration defines the types of possible Legendary mushroom cards in the game.
     */
    enum class Effect: u8 {
        STARS = 1, ///< Gain +Lvl stars from all sources, winner (player) steals this card upon battle KO
        WINS, ///< Gain +1 win from all sources, winner (player) steals this card upon battle KO
    };

    /**
     * @enum Colour
     * @brief Enumeration for legendary mushroom colours.
     * 
     * The Colour enumeration defines the possible colours a legendary mushroom card may have.
     */
    enum class Colour: u8 {
        LEGENDARY_RED,
        PHANTOM_BLUE,
    };
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of these cards
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    Effect effect; ///< The effect of the legendary mushroom card.
    Colour colour; ///< The colour of the card.

    /**
     * @brief Converts the mushroom type to its associated TextManager key.
     * 
     * @param type The legendary mushroom type.
     * @return The key to query in TextManager.
     */
    static constexpr String typeToKey(Effect type) noexcept {
        switch (type) {
            case Effect::STARS:
                return "CARD_SHROOM_LEGEND_STARS";
            case Effect::WINS:
                return "CARD_SHROOM_LEGEND_WINS";
            default:
                std::sys::unreachable();
        }
    }

    /**
     * @brief Converts the mushroom colour to its associated TextManager key.
     * 
     * @param type The legendary mushroom colour.
     * @return The key to query in TextManager.
     */
    static constexpr String colourToKey(Colour type) noexcept {
        switch (type) {
            case Colour::LEGENDARY_RED:
                return "CARD_ARTIST_COFFGIRL";
            case Colour::PHANTOM_BLUE:
                return "CARD_ARTIST_COFFGIRL";
            default:
                std::sys::unreachable();
        }
    }

    /**
     * @brief Converts the legendary mushroom colour to the associated TextManager key of its artist.
     * 
     * @param type The legendary mushroom colour.
     * @return The key to query for the artist in TextManager.
     */
    static constexpr String colourToArtistKey(Colour type) noexcept {
        switch (type) {
            case Colour::LEGENDARY_RED:
                return "CARD_SHROOM_LEGENDARYRED";
            case Colour::PHANTOM_BLUE:
                return "CARD_SHROOM_PHANTOMBLUE";
            default:
                std::sys::unreachable();
        }
    }
protected:
    /**
     * @brief Default constructor for BoostMushroomCard.
     */
    LegendaryMushroomCard() = default;

    /**
     * @brief Constructor to initialise a BoostMushroomCard object.
     *
     * @param colour The mushroom colour.
     * @param effect The legendary mushroom effect of the card.
     */
    LegendaryMushroomCard(Colour colour, Effect effect):
        Card(static_cast<u16>(effect), CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS), effect{effect}, colour{colour} {}
public:
    GETTER(Effect, Effect, effect);
    GETTER(Colour, Colour, colour);

    /**
     * @brief Get the name of the card.
     *
     * @return The name of the card.
     */
    [[nodiscard]]
    String getName() const noexcept override {
        Expected<String, TextManager::Error> result = TextManager::getInstance().getCardName(colourToKey(colour));
        return result ? *result : "";
    }

    /**
     * @brief Get the description of the card.
     *
     * @return The description of the card.
     */
    [[nodiscard]]
    String getDescription() const noexcept override {
        Expected<String, TextManager::Error> result = TextManager::getInstance().getCardDescription(typeToKey(effect));
        return result ? *result : "";
    }

    /**
     * @brief Get the card artist name.
     *
     * @return The card artist name.
     */
    [[nodiscard]]
    String getArtistName() const noexcept override {
        Expected<String, TextManager::Error> result = TextManager::getInstance().getCardArtistName(colourToArtistKey(colour));
        return result ? *result : "";
    }
};

/**
 * @concept LegendaryMushroomCard
 * @brief Concept that checks if a type extends the LegendaryMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsLegendaryMushroomCard = IsBaseOfValue<LegendaryMushroomCard, T>;

END_MODULE_NAMESPACE();

using openjuice::engine::card::mushroom::LegendaryMushroomCard;

template <>
struct Formatter<LegendaryMushroomCard::Colour> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(LegendaryMushroomCard::Colour type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case LegendaryMushroomCard::Colour::LEGENDARY_RED:
                name = "Legendary Red Mushroom";
                break;
            case LegendaryMushroomCard::Colour::PHANTOM_BLUE:
                name = "Phantom Blue Mushroom";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<LegendaryMushroomCard::Effect> {
    static constexpr const char* parse(FormatParseContext& ctx) {
        return ctx.begin();
    }

    static FormatContext::Iterator format(LegendaryMushroomCard::Effect type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case LegendaryMushroomCard::Effect::STARS:
                name = "Gain +Lvl stars from all sources";
                break;
            case LegendaryMushroomCard::Effect::WINS:
                name = "Gain +1 win from all sources";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(LegendaryMushroomCard::Colour);
SPECIALISE_FORMATTER(LegendaryMushroomCard::Effect);
