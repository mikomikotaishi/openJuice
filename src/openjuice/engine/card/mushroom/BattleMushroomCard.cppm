/**
 * @file BattleMushroomCard.cppm
 * @module openjuice.engine.card.mushroom:BattleMushroomCard
 * @brief Definition of the BattleMushroomCard abstract class.
 *
 * This file contains the definition of the BattleMushroomCard abstract class, which represents a Battle-type Mushroom card in the game.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.card.mushroom:BattleMushroomCard;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.cardtypes;
import openjuice.engine.card.spawntypes;
import openjuice.engine.managers;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::meta::IsBaseOfValue;

using openjuice::engine::card::cardtypes::BattleCard;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::managers::TextManager;

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
public:
    /**
     * @enum Effect
     * @brief Enumeration for battle card mushroom types.
     * 
     * The Effect enumeration defines the types of possible mushroom cards of Battle type in the game.
     */
    enum class Effect: u8 {
        NULL_BATTLE = 1, ///< No effect (always appears)
        ATTACK_UP, ///< Gain +1/2/3 ATK during this battle
        ATTACK_DOWN, ///< Gain -1/2/3 ATK during this battle
        DEFENCE_UP, ///< Gain +1/2/3 DEF during this battle
        DEFENCE_DOWN, ///< Gain -1/2/3 DEF during this battle
        EVADE_UP, ///< Gain +1/2/3 EVD during this battle
        EVADE_DOWN, ///< Gain -1/2/3 EVD during this battle
        HEAL, ///< Gain 1/2/3 HP
        DAMAGE, ///< Take 1/2/3 damage
        ROLL_ONE, ///< Only roll 1 in this battle
        ROLL_SIX, ///< Only roll 6 in this battle
    };
private:
    static constexpr Card::Type CARD_TYPE = Card::Type::GIFT; ///< The card type of these cards
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    Effect effect; ///< The effect of the battle mushroom card.
    MushroomCard::Colour colour; ///< The colour of the card.

    /**
     * @brief Converts the mushroom type to its associated TextManager key.
     * 
     * @param type The battle mushroom type.
     * @return The key to query in TextManager.
     */
    static constexpr String typeToKey(Effect type) noexcept {
        switch (type) {
            case Effect::NULL_BATTLE:
                return "No effect.";
            case Effect::ATTACK_UP:
                return "CARD_SHROOM_ATTACKUP";
            case Effect::ATTACK_DOWN:
                return "CARD_SHROOM_ATTACKDOWN";
            case Effect::DEFENCE_UP:
                return "CARD_SHROOM_DEFENSEUP";
            case Effect::DEFENCE_DOWN:
                return "CARD_SHROOM_DEFENSEDOWN";
            case Effect::EVADE_UP:
                return "CARD_SHROOM_EVADEUP";
            case Effect::EVADE_DOWN:
                return "CARD_SHROOM_EVADEDOWN";
            case Effect::HEAL:
                return "CARD_SHROOM_HEAL";
            case Effect::DAMAGE:
                return "CARD_SHROOM_DAMAGE";
            case Effect::ROLL_ONE:
                return "CARD_SHROOM_ROLLONE";
            case Effect::ROLL_SIX:
                return "CARD_SHROOM_ROLLSIX";
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
     * @param effect The Battle mushroom effect of the card.
     */
    BattleMushroomCard(MushroomCard::Colour colour, Effect effect):
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
 * @concept ExtendsBattleMushroomCard
 * @brief Concept that checks if a type extends the BattleMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBattleMushroomCard = IsBaseOfValue<BattleMushroomCard, T>;

END_MODULE_NAMESPACE();

using openjuice::engine::card::mushroom::BattleMushroomCard;

template <>
struct Formatter<BattleMushroomCard::Effect> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(BattleMushroomCard::Effect type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case BattleMushroomCard::Effect::NULL_BATTLE:
                name = "No Effect";
                break;
            case BattleMushroomCard::Effect::ATTACK_UP:
                name = "Gain Attack";
                break;
            case BattleMushroomCard::Effect::ATTACK_DOWN:
                name = "Lose Attack";
                break;
            case BattleMushroomCard::Effect::DEFENCE_UP:
                name = "Gain Defence";
                break;
            case BattleMushroomCard::Effect::DEFENCE_DOWN:
                name = "Lose Defence";
                break;
            case BattleMushroomCard::Effect::EVADE_UP:
                name = "Gain Evade";
                break;
            case BattleMushroomCard::Effect::EVADE_DOWN:
                name = "Lose Evade";
                break;
            case BattleMushroomCard::Effect::HEAL:
                name = "Heal";
                break;
            case BattleMushroomCard::Effect::DAMAGE:
                name = "Damage";
                break;
            case BattleMushroomCard::Effect::ROLL_ONE:
                name = "Roll 1";
                break;
            case BattleMushroomCard::Effect::ROLL_SIX:
                name = "Roll 6";
                break;                
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BattleMushroomCard::Effect);
