/**
 * @file mushroom.cppm
 * @module openjuice.engine.card.mushroom
 * @brief Import of all types of Mushroom Cards.
 *
 * This file imports the modules for all types of Mushroom Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.mushroom;

import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.type;
import openjuice.engine.card.spawn;
import openjuice.engine.managers;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::meta::IsBaseOfValue;

using openjuice::engine::card::spawn::MushroomCard;
using openjuice::engine::card::type::BattleCard;
using openjuice::engine::card::type::BoostCard;
using openjuice::engine::card::type::GiftCard;
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
                System::unreachable();
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
        NULL_BOOST = stdx::util::to_underlying(BattleMushroomCard::Effect::ROLL_SIX) + 1, ///< No effect (always appears)
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
                System::unreachable();
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
                System::unreachable();
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
                System::unreachable();
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
                System::unreachable();
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
 * @concept ExtendsBattleMushroomCard
 * @brief Concept that checks if a type extends the BattleMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBattleMushroomCard = IsBaseOfValue<BattleMushroomCard, T>;

/**
 * @concept ExtendsBoostMushroomCard
 * @brief Concept that checks if a type extends the BoostMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsBoostMushroomCard = IsBaseOfValue<BoostMushroomCard, T>;

/**
 * @concept LegendaryMushroomCard
 * @brief Concept that checks if a type extends the LegendaryMushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsLegendaryMushroomCard = IsBaseOfValue<LegendaryMushroomCard, T>;

END_MODULE_NAMESPACE();

using openjuice::engine::card::mushroom::BattleMushroomCard;
using openjuice::engine::card::mushroom::BoostMushroomCard;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;

template <>
struct Formatter<BattleMushroomCard::Effect> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(BattleMushroomCard::Effect type, FormatContext& ctx) {
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
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<BoostMushroomCard::Effect> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(BoostMushroomCard::Effect type, FormatContext& ctx) {
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
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<LegendaryMushroomCard::Colour> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(LegendaryMushroomCard::Colour type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case LegendaryMushroomCard::Colour::LEGENDARY_RED:
                name = "Legendary Red Mushroom";
                break;
            case LegendaryMushroomCard::Colour::PHANTOM_BLUE:
                name = "Phantom Blue Mushroom";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

template <>
struct Formatter<LegendaryMushroomCard::Effect> {
    static constexpr const char* parse(FormatParseContext& ctx) {
        return ctx.begin();
    }

    static FormatContext::iterator format(LegendaryMushroomCard::Effect type, FormatContext& ctx) {
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

SPECIALISE_FORMATTER(BattleMushroomCard::Effect);
SPECIALISE_FORMATTER(BoostMushroomCard::Effect);
SPECIALISE_FORMATTER(LegendaryMushroomCard::Colour);
SPECIALISE_FORMATTER(LegendaryMushroomCard::Effect);
