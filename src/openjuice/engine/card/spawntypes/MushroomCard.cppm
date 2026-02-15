/**
 * @file MushroomCard.cppm
 * @module openjuice.engine.card.spawntypes:MushroomCard
 * @brief Definition of the MushroomCard abstract class.
 *
 * This file contains the definition of the MushroomCard abstract class, which represents a Mushroom card in the game.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.spawntypes:MushroomCard;

import stdx;

import openjuice.engine.card.Card;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class MushroomCard
 * @brief Abstract class representing a Mushroom card.
 *
 * @extends Card
 * 
 * The MushroomCard abstract class extends the Card abstract class and represents a Mushroom card with specific attributes.
 */
export class MushroomCard: virtual public Card {
public:
    static constexpr u8 NUM_MUSHROOMS = 10; ///< The number of mushroom cards in the game
    static constexpr u8 NUM_LEGENDARY_MUSHROOMS = 2; ///< The number of legendary mushroom cards in the game

    /**
     * @enum Colour
     * @brief Enumeration for mushroom colours.
     * 
     * The Colour enumeration defines the possible colours a mushroom card may have.
     */
    enum class Colour: u8 {
        BLUE,
        BROWN,
        GREEN,
        ORANGE,
        PINK,
        PURPLE,
        RAINBOW,
        RED,
        WHITE,
        YELLOW,
    };
protected:
    // Uses "CARD_SHROOM_BLUE" because all (regular) mushroom cards have the same description.
    static constexpr char EFFECT_KEY[] = "CARD_SHROOM_BLUE"; ///< The key belonging to the effect to query in TextManager

    /**
     * @brief Default constructor for MushroomCard.
     */
    MushroomCard() = default;

    /**
     * @brief Converts the mushroom colour to its associated TextManager key.
     * 
     * @param type The mushroom colour.
     * @return The key to query in TextManager.
     */
    static constexpr String colourToKey(MushroomCard::Colour type) noexcept {
        switch (type) {
            case MushroomCard::Colour::BLUE:
                return "CARD_SHROOM_BLUE";
            case MushroomCard::Colour::BROWN:
                return "CARD_SHROOM_BROWN";
            case MushroomCard::Colour::GREEN:
                return "CARD_SHROOM_GREEN";
            case MushroomCard::Colour::ORANGE:
                return "CARD_SHROOM_ORANGE";
            case MushroomCard::Colour::PINK:
                return "CARD_SHROOM_PINK";
            case MushroomCard::Colour::PURPLE:
                return "CARD_SHROOM_PURPLE";
            case MushroomCard::Colour::RAINBOW:
                return "CARD_SHROOM_RAINBOW";
            case MushroomCard::Colour::RED:
                return "CARD_SHROOM_RED";
            case MushroomCard::Colour::WHITE:
                return "CARD_SHROOM_WHITE";
            case MushroomCard::Colour::YELLOW:
                return "CARD_SHROOM_YELLOW";
            default:
                stdx::sys::unreachable();
        }
    }

    /**
     * @brief Converts the mushroom colour to the associated TextManager key of its artist.
     * 
     * @param type The mushroom colour.
     * @return The key to query for the artist in TextManager.
     */
    static constexpr String colourToArtistKey(MushroomCard::Colour type) noexcept {
        switch (type) {
            case MushroomCard::Colour::BLUE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::BROWN:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::GREEN:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::ORANGE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::PINK:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::PURPLE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::RAINBOW:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::RED:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::WHITE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomCard::Colour::YELLOW:
                return "CARD_ARTIST_COFFGIRL";
            default:
                stdx::sys::unreachable();
        }
    }
};

/**
 * @concept ExtendsMushroomCard
 * @brief Concept that checks if a type extends the MushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsMushroomCard = IsBaseOfValue<MushroomCard, T>;

END_MODULE_NAMESPACE();

using openjuice::engine::card::spawntypes::MushroomCard;

template <>
struct Formatter<MushroomCard::Colour> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(MushroomCard::Colour type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case MushroomCard::Colour::BLUE:
                name = "Blue Mushroom";
                break;
            case MushroomCard::Colour::BROWN:
                name = "Brown Mushroom";
                break;
            case MushroomCard::Colour::GREEN:
                name = "Green Mushroom";
                break;
            case MushroomCard::Colour::ORANGE:
                name = "Orange Mushroom";
                break;
            case MushroomCard::Colour::PINK:
                name = "Pink Mushroom";
                break;
            case MushroomCard::Colour::PURPLE:
                name = "Purple Mushroom";
                break;
            case MushroomCard::Colour::RAINBOW:
                name = "Rainbow Mushroom";
                break;
            case MushroomCard::Colour::RED:
                name = "Red Mushroom";
                break;
            case MushroomCard::Colour::WHITE:
                name = "White Mushroom";
                break;
            case MushroomCard::Colour::YELLOW:
                name = "Yellow Mushroom";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(MushroomCard::Colour);
