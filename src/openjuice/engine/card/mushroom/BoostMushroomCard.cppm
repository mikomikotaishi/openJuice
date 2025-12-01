/**
 * @file BoostMushroomCard.cppm
 * @module openjuice.engine.card.mushroom.BoostMushroomCard
 * @brief Definition of the BoostMushroomCard abstract class.
 *
 * This file contains the definition of the BoostMushroomCard abstract class, which represents a Boost-type Mushroom card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.mushroom.BoostMushroomCard;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.CardTypes;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.TextManager;

using std::meta::IsBaseOfValue;

namespace sys = std::sys;

using openjuice::engine::card::cardtypes::BoostCard;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::mushroom);

/**
 * @class BoostMushroomCard
 * @brief Abstract class representing a Boost-type Mushroom card.
 *
 * @extends BoostCard
 * @extends MushroomCard
 * 
 * The BoostMushroomCard abstract class extends the Card abstract class and represents a Boost-type Mushroom card with specific attributes.
 */
export class BoostMushroomCard: public BoostCard, public MushroomCard {
private:
    static constexpr CardType CARD_TYPE = CardType::GIFT_CARD; ///< The card type of these cards
    static constexpr SpawnType SPAWN_TYPE = SpawnType::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    BoostMushroomType mushroomType; ///< The effect of the boost mushroom card.
    MushroomColour mushroomColour; ///< The colour of the card.

    /**
     * @brief Converts the mushroom type to its associated TextManager key.
     * 
     * @param type The boost mushroom type.
     * @return The key to query in TextManager.
     */
    static constexpr String typeToKey(BoostMushroomType type) noexcept {
        switch (type) {
            case BoostMushroomType::NULL_BOOST:
                return "No effect.";
            case BoostMushroomType::MOVE_UP:
                return "CARD_SHROOM_MOVEUP";
            case BoostMushroomType::MOVE_DOWN:
                return "CARD_SHROOM_MOVEDOWN";
            case BoostMushroomType::GAIN_STARS:
                return "CARD_SHROOM_GAINSTARS";
            case BoostMushroomType::LOSE_STARS:
                return "CARD_SHROOM_LOSESTARS";
            case BoostMushroomType::HEALTH_UP:
                return "CARD_SHROOM_HEALTHUP";
            case BoostMushroomType::HEALTH_DOWN:
                return "CARD_SHROOM_HEALTHDOWN";
            case BoostMushroomType::FROSTWALKER:
                return "CARD_SHROOM_FROSTWALKER";
            case BoostMushroomType::WARP:
                return "CARD_SHROOM_WARP";
            case BoostMushroomType::CONFUSION:
                return "CARD_SHROOM_CONFUSION";
            case BoostMushroomType::DRAW:
                return "CARD_SHROOM_DRAW";
            case BoostMushroomType::DISCARD:
                return "CARD_SHROOM_DISCARD";
            case BoostMushroomType::WIN:
                return "CARD_SHROOM_WIN";
            default:
                sys::unreachable();
        }
    }


    /**
     * @brief Converts the mushroom colour to its associated TextManager key.
     * 
     * @param type The mushroom colour.
     * @return The key to query in TextManager.
     */
    static constexpr String colourToKey(MushroomColour type) noexcept {
        switch (type) {
            case MushroomColour::BLUE:
                return "CARD_SHROOM_BLUE";
            case MushroomColour::BROWN:
                return "CARD_SHROOM_BROWN";
            case MushroomColour::GREEN:
                return "CARD_SHROOM_GREEN";
            case MushroomColour::ORANGE:
                return "CARD_SHROOM_ORANGE";
            case MushroomColour::PINK:
                return "CARD_SHROOM_PINK";
            case MushroomColour::PURPLE:
                return "CARD_SHROOM_PURPLE";
            case MushroomColour::RAINBOW:
                return "CARD_SHROOM_RAINBOW";
            case MushroomColour::RED:
                return "CARD_SHROOM_RED";
            case MushroomColour::WHITE:
                return "CARD_SHROOM_WHITE";
            case MushroomColour::YELLOW:
                return "CARD_SHROOM_YELLOW";
            default:
                sys::unreachable();
        }
    }

    /**
     * @brief Converts the mushroom colour to the associated TextManager key of its artist.
     * 
     * @param type The mushroom colour.
     * @return The key to query for the artist in TextManager.
     */
    static constexpr String colourToArtistKey(MushroomColour type) noexcept {
        switch (type) {
            case MushroomColour::BLUE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::BROWN:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::GREEN:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::ORANGE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::PINK:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::PURPLE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::RAINBOW:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::RED:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::WHITE:
                return "CARD_ARTIST_COFFGIRL";
            case MushroomColour::YELLOW:
                return "CARD_ARTIST_COFFGIRL";
            default:
                sys::unreachable();
        }
    }
protected:
    /**
     * @brief Default constructor for BoostMushroomCard.
     */
    BoostMushroomCard() = default;

    /**
     * @brief Constructor to initialise a BoostMushroomCard object.
     *
     * @param colour The mushroom colour.
     * @param type The Boost mushroom type of the card.
     */
    BoostMushroomCard(MushroomColour colour, BoostMushroomType type):
        Card(static_cast<u16>(type), CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS), mushroomType{type}, mushroomColour{colour} {}
public:
    GETTER(BoostMushroomType, MushroomType, mushroomType);
    GETTER(MushroomColour, MushroomColour, mushroomColour);

    /**
     * @brief Get the name of the card.
     *
     * @return The name of the card.
     */
    [[nodiscard]]
    String getName() const override {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardName(colourToKey(mushroomColour));
        return String(result ? *result : "");
    }

    /**
     * @brief Get the description of the card.
     *
     * @return The description of the card.
     */
    [[nodiscard]]
    String getDescription() const override {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardDescription(typeToKey(mushroomType));
        return String(result ? *result : "");
    }

    /**
     * @brief Get the card artist name.
     *
     * @return The card artist name.
     */
    [[nodiscard]]
    String getArtistName() const override {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardArtistName(colourToArtistKey(mushroomColour));
        return String(result ? *result : "");
    }
};

/**
 * @concept ExtendsBoostMushroomCard
 * @brief Concept that checks if a type extends the BoostMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBoostMushroomCard = IsBaseOfValue<BoostMushroomCard, T>;

END_MODULE_NAMESPACE();
