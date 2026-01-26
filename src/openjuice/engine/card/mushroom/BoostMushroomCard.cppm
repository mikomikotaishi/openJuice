/**
 * @file BoostMushroomCard.cppm
 * @module openjuice.engine.card.mushroom:BoostMushroomCard
 * @brief Definition of the BoostMushroomCard abstract class.
 *
 * This file contains the definition of the BoostMushroomCard abstract class, which represents a Boost-type Mushroom card in the game.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.mushroom:BoostMushroomCard;

import std;

import :BattleMushroomCard;

import openjuice.engine.card.Card;
import openjuice.engine.card.cardtypes;
import openjuice.engine.card.spawntypes;
import openjuice.engine.managers;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::meta::IsBaseOfValue;

using openjuice::engine::card::cardtypes::BoostCard;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::managers::TextManager;

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
public:
    /**
    * @enum Effect
    * @brief Enumeration for boost card mushroom types.
    * 
    * The Effect enumeration defines the types of possible mushroom cards of Boost type in the game.
    */
    enum class Effect: u8 {
        NULL_BOOST = std::util::to_underlying(BattleMushroomCard::Effect::ROLL_SIX) + 1, ///< No effect (always appears)
        MOVE_UP, ///< Gain +1/2/3 MOV on next roll
        MOVE_DOWN, ///< Gain -1/2/3 MOV on next roll
        GAIN_STARS, ///< Gain Lvl x 1/2/3/4/5 stars
        LOSE_STARS, ///< Lose Lvl x 1/2/3/4/5 stars
        HEALTH_UP, ///< Gain 1/2/3 HP
        HEALTH_DOWN, ///< Lose 1/2/3 HP
        FROSTWALKER, ///< Gain Frostwalker for 1/2/3 chapter(s)
        WARP, ///< Warp to a random panel
        CONFUSION, ///< For 1/2/3 chapters, all cards are reversed (player cannot see their cards, but other players can)
        DRAW, ///< Draw 2 cards
        DISCARD, ///< Discard a random card
        WIN, ///< Gain 1 win
    };
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of these cards
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    Effect effect; ///< The effect of the boost mushroom card.
    MushroomCard::Colour colour; ///< The colour of the card.

    /**
     * @brief Converts the mushroom type to its associated TextManager key.
     * 
     * @param type The boost mushroom type.
     * @return The key to query in TextManager.
     */
    static constexpr String typeToKey(Effect type) noexcept {
        switch (type) {
            case Effect::NULL_BOOST:
                return "No effect.";
            case Effect::MOVE_UP:
                return "CARD_SHROOM_MOVEUP";
            case Effect::MOVE_DOWN:
                return "CARD_SHROOM_MOVEDOWN";
            case Effect::GAIN_STARS:
                return "CARD_SHROOM_GAINSTARS";
            case Effect::LOSE_STARS:
                return "CARD_SHROOM_LOSESTARS";
            case Effect::HEALTH_UP:
                return "CARD_SHROOM_HEALTHUP";
            case Effect::HEALTH_DOWN:
                return "CARD_SHROOM_HEALTHDOWN";
            case Effect::FROSTWALKER:
                return "CARD_SHROOM_FROSTWALKER";
            case Effect::WARP:
                return "CARD_SHROOM_WARP";
            case Effect::CONFUSION:
                return "CARD_SHROOM_CONFUSION";
            case Effect::DRAW:
                return "CARD_SHROOM_DRAW";
            case Effect::DISCARD:
                return "CARD_SHROOM_DISCARD";
            case Effect::WIN:
                return "CARD_SHROOM_WIN";
            default:
                std::sys::unreachable();
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
     * @param effect The Boost mushroom effect of the card.
     */
    BoostMushroomCard(MushroomCard::Colour colour, Effect effect):
        Card(static_cast<u16>(effect), CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS), effect{effect}, colour{colour} {}
public:
    GETTER(Effect, Effect, effect);
    GETTER(MushroomCard::Colour, Colour, colour);

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
 * @concept ExtendsBoostMushroomCard
 * @brief Concept that checks if a type extends the BoostMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBoostMushroomCard = IsBaseOfValue<BoostMushroomCard, T>;

END_MODULE_NAMESPACE();

using openjuice::engine::card::mushroom::BoostMushroomCard;

template <>
struct Formatter<BoostMushroomCard::Effect> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(BoostMushroomCard::Effect type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case BoostMushroomCard::Effect::NULL_BOOST:
                name = "No Effect";
                break;
            case BoostMushroomCard::Effect::MOVE_UP:
                name = "Gain Movement";
                break;
            case BoostMushroomCard::Effect::MOVE_DOWN:
                name = "Lose Movement";
                break;
            case BoostMushroomCard::Effect::GAIN_STARS:
                name = "Gain Stars";
                break;
            case BoostMushroomCard::Effect::LOSE_STARS:
                name = "Lose Stars";
                break;
            case BoostMushroomCard::Effect::HEALTH_UP:
                name = "Gain HP";
                break;
            case BoostMushroomCard::Effect::HEALTH_DOWN:
                name = "Lose HP";
                break;
            case BoostMushroomCard::Effect::FROSTWALKER:
                name = "Frostwalker";
                break;
            case BoostMushroomCard::Effect::WARP:
                name = "Warp";
                break;
            case BoostMushroomCard::Effect::CONFUSION:
                name = "Confusion";
                break;
            case BoostMushroomCard::Effect::DRAW:
                name = "Draw Cards";
                break;
            case BoostMushroomCard::Effect::DISCARD:
                name = "Discard Card";
                break;
            case BoostMushroomCard::Effect::WIN:
                name = "Gain Win";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BoostMushroomCard::Effect);
