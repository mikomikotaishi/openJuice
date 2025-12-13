/**
 * @file LegendaryMushroomCard.cppm
 * @module openjuice.engine.card.mushroom.LegendaryMushroomCard
 * @brief Definition of the LegendaryMushroomCard abstract class.
 *
 * This file contains the definition of the LegendaryMushroomCard abstract class, which represents a Legendary Mushroom card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.mushroom.LegendaryMushroomCard;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.CardTypes;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.TextManager;

using std::meta::IsBaseOfValue;

namespace sys = std::sys;

using openjuice::engine::card::cardtypes::GiftCard;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;

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
private:
    static constexpr CardType CARD_TYPE = CardType::GIFT; ///< The card type of these cards
    static constexpr SpawnType SPAWN_TYPE = SpawnType::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    LegendaryMushroomType mushroomType; ///< The effect of the legendary mushroom card.
    LegendaryMushroomColour mushroomColour; ///< The colour of the card.

    /**
     * @brief Converts the mushroom type to its associated TextManager key.
     * 
     * @param type The legendary mushroom type.
     * @return The key to query in TextManager.
     */
    static constexpr String typeToKey(LegendaryMushroomType type) noexcept {
        switch (type) {
            case LegendaryMushroomType::STARS:
                return "CARD_SHROOM_LEGEND_STARS";
            case LegendaryMushroomType::WINS:
                return "CARD_SHROOM_LEGEND_WINS";
            default:
                sys::unreachable();
        }
    }

    /**
     * @brief Converts the mushroom colour to its associated TextManager key.
     * 
     * @param type The legendary mushroom colour.
     * @return The key to query in TextManager.
     */
    static constexpr String colourToKey(LegendaryMushroomColour type) noexcept {
        switch (type) {
            case LegendaryMushroomColour::LEGENDARY_RED:
                return "CARD_ARTIST_COFFGIRL";
            case LegendaryMushroomColour::PHANTOM_BLUE:
                return "CARD_ARTIST_COFFGIRL";
            default:
                sys::unreachable();
        }
    }

    /**
     * @brief Converts the legendary mushroom colour to the associated TextManager key of its artist.
     * 
     * @param type The legendary mushroom colour.
     * @return The key to query for the artist in TextManager.
     */
    static constexpr String colourToArtistKey(LegendaryMushroomColour type) noexcept {
        switch (type) {
            case LegendaryMushroomColour::LEGENDARY_RED:
                return "CARD_SHROOM_LEGENDARYRED";
            case LegendaryMushroomColour::PHANTOM_BLUE:
                return "CARD_SHROOM_PHANTOMBLUE";
            default:
                sys::unreachable();
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
     * @param type The legendary mushroom type of the card.
     */
    LegendaryMushroomCard(LegendaryMushroomColour colour, LegendaryMushroomType type):
        Card(static_cast<u16>(type), CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS), mushroomType{type}, mushroomColour{colour} {}
public:
    GETTER(LegendaryMushroomType, MushroomType, mushroomType);
    GETTER(LegendaryMushroomColour, MushroomColour, mushroomColour);

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
 * @concept LegendaryMushroomCard
 * @brief Concept that checks if a type extends the LegendaryMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsLegendaryMushroomCard = IsBaseOfValue<LegendaryMushroomCard, T>;

END_MODULE_NAMESPACE();
