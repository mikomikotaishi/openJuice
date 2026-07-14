/**
 * @file spawn.cppm
 * @module openjuice.engine.card.spawn
 * @brief Import of card spawn type module partitions.
 *
 * This file imports the module partitions for different card types.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.spawn;

import stdx;

import openjuice.engine.card.Card;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawn);

/**
 * @class BossCard
 * @brief Abstract class representing a Boss card.
 * @extends Card
 * 
 * The BossCard abstract class extends the Card abstract class and represents a Boss card with specific attributes.
 */
export class BossCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BossCard.
     */
    BossCard() = default;
};

/**
 * @class BountyHuntCard
 * @brief Abstract class representing a Bounty Hunt card.
 * @extends Card
 * 
 * The BountyHuntCard abstract class extends the Card abstract class and represents a Bounty Hunt card with specific attributes.
 */
export class BountyHuntCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for BountyHuntCard.
     */
    BountyHuntCard() = default;
};

/**
 * @class CharacterSpecificCard
 * @brief Abstract class representing a Hyper card.
 * @extends Card
 * 
 * The CharacterSpecificCard abstract class extends the Card abstract class and represents a Hyper card with specific attributes.
 */
export class CharacterSpecificCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for CharacterSpecificCard.
     */
    CharacterSpecificCard() = default;
};

/**
 * @class CoopCard
 * @brief Abstract class representing a Co-op card.
 * @extends Card
 * 
 * The CoopCard abstract class extends the Card abstract class and represents a Co-op card with specific attributes.
 */
export class CoopCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for CoopCard.
     */
    CoopCard() = default;
};

/**
 * @class GenericCard
 * @brief Abstract class representing a Generic (placeholder) card.
 * @extends Card
 * 
 * The GenericCard abstract class extends the Card abstract class and represents a Generic (placeholder) card.
 */
export class GenericCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for GenericCard.
     */
    GenericCard() = default;
};

/**
 * @class HyperCard
 * @brief Abstract class representing a Hyper card.
 * @extends Card
 * 
 * The HyperCard abstract class extends the Card abstract class and represents a Hyper card with specific attributes.
 */
export class HyperCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for HyperCard.
     */
    HyperCard() = default;
};

/**
 * @class MushroomCard
 * @brief Abstract class representing a Mushroom card.
 * @extends Card
 * 
 * The MushroomCard abstract class extends the Card abstract class and represents a Mushroom card with specific attributes.
 */
export class MushroomCard: virtual public Card {
public:
    static constexpr u8 NUM_MUSHROOMS = 10; ///< The number of mushroom cards in the game
    static constexpr u8 NUM_LEGENDARY_MUSHROOMS = 2; ///< The number of legendary mushroom cards in the game

    /**
     * @enum Color
     * @brief Enumeration for mushroom colors.
     * 
     * The Color enumeration defines the possible colors a mushroom card may have.
     */
    enum class Color: u8 {
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
    static constexpr char EFFECT_KEY[] = "CARD_SHROOM_BLUE"; ///< The key belonging to the effect to query in LocalizationService

    /**
     * @brief Default constructor for MushroomCard.
     */
    MushroomCard() = default;

    /**
     * @brief Converts the mushroom color to its associated LocalizationService key.
     * @param type The mushroom color.
     * @return The key to query in LocalizationService.
     */
    static constexpr String colorToKey(MushroomCard::Color type) noexcept {
        switch (type) {
            case MushroomCard::Color::BLUE:
                return "CARD_SHROOM_BLUE";
            case MushroomCard::Color::BROWN:
                return "CARD_SHROOM_BROWN";
            case MushroomCard::Color::GREEN:
                return "CARD_SHROOM_GREEN";
            case MushroomCard::Color::ORANGE:
                return "CARD_SHROOM_ORANGE";
            case MushroomCard::Color::PINK:
                return "CARD_SHROOM_PINK";
            case MushroomCard::Color::PURPLE:
                return "CARD_SHROOM_PURPLE";
            case MushroomCard::Color::RAINBOW:
                return "CARD_SHROOM_RAINBOW";
            case MushroomCard::Color::RED:
                return "CARD_SHROOM_RED";
            case MushroomCard::Color::WHITE:
                return "CARD_SHROOM_WHITE";
            case MushroomCard::Color::YELLOW:
                return "CARD_SHROOM_YELLOW";
        }
        Ops::unreachable();
    }

    /**
     * @brief Converts the mushroom color to the associated LocalizationService key of its artist.
     * @param type The mushroom color.
     * @return The key to query for the artist in LocalizationService.
     */
    static constexpr String colorToArtistKey(MushroomCard::Color type) noexcept {
        switch (type) {
            case MushroomCard::Color::BLUE:
            case MushroomCard::Color::BROWN:
            case MushroomCard::Color::GREEN:
            case MushroomCard::Color::ORANGE:
            case MushroomCard::Color::PINK:
            case MushroomCard::Color::PURPLE:
            case MushroomCard::Color::RAINBOW:
            case MushroomCard::Color::RED:
            case MushroomCard::Color::WHITE:
            case MushroomCard::Color::YELLOW:
                return "CARD_ARTIST_COFFGIRL";
        }
        Ops::unreachable();
    }
};

/**
 * @class SeasonalCard
 * @brief Abstract class representing a Seasonal card.
 * @extends Card
 * 
 * The SeasonalCard abstract class extends the Card abstract class and represents a Seasonal card with specific attributes.
 */
export class SeasonalCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for SeasonalCard.
     */
    SeasonalCard() = default;
};

/**
 * @class StandardCard
 * @brief Abstract class representing a Standard card.
 * @extends Card
 * 
 * The StandardCard abstract class extends the Card abstract class and represents a Standard card with specific attributes.
 */
export class StandardCard: virtual public Card {
protected:
    /**
     * @brief Default constructor for StandardCard.
     */
    StandardCard() = default;
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::spawn::MushroomCard;

template <>
struct Formatter<MushroomCard::Color> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(MushroomCard::Color type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case MushroomCard::Color::BLUE:
                name = "Blue Mushroom";
                break;
            case MushroomCard::Color::BROWN:
                name = "Brown Mushroom";
                break;
            case MushroomCard::Color::GREEN:
                name = "Green Mushroom";
                break;
            case MushroomCard::Color::ORANGE:
                name = "Orange Mushroom";
                break;
            case MushroomCard::Color::PINK:
                name = "Pink Mushroom";
                break;
            case MushroomCard::Color::PURPLE:
                name = "Purple Mushroom";
                break;
            case MushroomCard::Color::RAINBOW:
                name = "Rainbow Mushroom";
                break;
            case MushroomCard::Color::RED:
                name = "Red Mushroom";
                break;
            case MushroomCard::Color::WHITE:
                name = "White Mushroom";
                break;
            case MushroomCard::Color::YELLOW:
                name = "Yellow Mushroom";
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALIZE_FORMATTER(MushroomCard::Color);
