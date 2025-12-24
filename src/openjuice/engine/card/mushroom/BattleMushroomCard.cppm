/**
 * @file BattleMushroomCard.cppm
 * @module openjuice.engine.card.mushroom:BattleMushroomCard
 * @brief Definition of the BattleMushroomCard abstract class.
 *
 * This file contains the definition of the BattleMushroomCard abstract class, which represents a Battle-type Mushroom card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.mushroom:BattleMushroomCard;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.cardtypes;
import openjuice.engine.card.spawntypes;
import openjuice.engine.managers;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::cardtypes::BattleCard;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::mushroom);

/**
 * @class BattleMushroomCard
 * @brief Abstract class representing a Battle-type Mushroom card.
 *
 * @extends BattleCard
 * @extends MushroomCard
 * 
 * The BattleMushroomCard abstract class extends the Card abstract class and represents a Battle-type Mushroom card with specific attributes.
 */
export class BattleMushroomCard: public BattleCard, public MushroomCard {
private:
    static constexpr CardType CARD_TYPE = CardType::GIFT; ///< The card type of these cards
    static constexpr SpawnType SPAWN_TYPE = SpawnType::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, DeckPointError> DECK_POINTS = Unexpected(DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    BattleMushroomType mushroomType; ///< The effect of the battle mushroom card.
    MushroomColour mushroomColour; ///< The colour of the card.

    /**
     * @brief Converts the mushroom type to its associated TextManager key.
     * 
     * @param type The battle mushroom type.
     * @return The key to query in TextManager.
     */
    static constexpr String typeToKey(BattleMushroomType type) noexcept {
        switch (type) {
            case BattleMushroomType::NULL_BATTLE:
                return "No effect.";
            case BattleMushroomType::ATTACK_UP:
                return "CARD_SHROOM_ATTACKUP";
            case BattleMushroomType::ATTACK_DOWN:
                return "CARD_SHROOM_ATTACKDOWN";
            case BattleMushroomType::DEFENCE_UP:
                return "CARD_SHROOM_DEFENSEUP";
            case BattleMushroomType::DEFENCE_DOWN:
                return "CARD_SHROOM_DEFENSEDOWN";
            case BattleMushroomType::EVADE_UP:
                return "CARD_SHROOM_EVADEUP";
            case BattleMushroomType::EVADE_DOWN:
                return "CARD_SHROOM_EVADEDOWN";
            case BattleMushroomType::HEAL:
                return "CARD_SHROOM_HEAL";
            case BattleMushroomType::DAMAGE:
                return "CARD_SHROOM_DAMAGE";
            case BattleMushroomType::ROLL_ONE:
                return "CARD_SHROOM_ROLLONE";
            case BattleMushroomType::ROLL_SIX:
                return "CARD_SHROOM_ROLLSIX";
            default:
                std::sys::unreachable();
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
                std::sys::unreachable();
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
                std::sys::unreachable();
        }
    }
protected:
    /**
     * @brief Default constructor for BattleMushroomCard.
     */
    BattleMushroomCard() = default;

    /**
     * @brief Constructor to initialise a BattleMushroomCard object.
     *
     * @param colour The mushroom colour.
     * @param type The Battle mushroom type of the card.
     */
    BattleMushroomCard(MushroomColour colour, BattleMushroomType type):
        Card(static_cast<u16>(type), CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS), mushroomType{type}, mushroomColour{colour} {}
public:
    GETTER(BattleMushroomType, MushroomType, mushroomType);
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
 * @concept ExtendsBattleMushroomCard
 * @brief Concept that checks if a type extends the BattleMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBattleMushroomCard = IsBaseOfValue<BattleMushroomCard, T>;

END_MODULE_NAMESPACE();
