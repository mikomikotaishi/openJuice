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
import openjuice.engine.localization;

using openjuice::engine::card::spawn::MushroomCard;
using openjuice::engine::card::type::BattleCard;
using openjuice::engine::card::type::BoostCard;
using openjuice::engine::card::type::GiftCard;
using openjuice::engine::localization::LocalizationService;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::mushroom);

/**
 * @class BattleMushroomCard
 * @brief Abstract class representing a Battle-type Mushroom card.
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
        DEFENSE_UP, ///< Gain +1/2/3 DEF during this battle
        DEFENSE_DOWN, ///< Gain -1/2/3 DEF during this battle
        EVADE_UP, ///< Gain +1/2/3 EVD during this battle
        EVADE_DOWN, ///< Gain -1/2/3 EVD during this battle
        HEAL, ///< Gain 1/2/3 HP
        DAMAGE, ///< Take 1/2/3 damage
        ROLL_ONE, ///< Only roll 1 in this battle
        ROLL_SIX, ///< Only roll 6 in this battle
    };
private:
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of these cards
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    Effect effect; ///< The effect of the battle mushroom card.
    MushroomCard::Color color; ///< The color of the card.
protected:
    /**
     * @brief Converts the mushroom type to its associated LocalizationService key.
     * @param type The battle mushroom type.
     * @return The key to query in LocalizationService.
     */
    [[nodiscard]]
    static constexpr String typeToKey(Effect type) noexcept {
        switch (type) {
            case Effect::NULL_BATTLE:
                // Doze maps to "No effect."
                return "CARD_BOSS_COOP_DOZE";
            case Effect::ATTACK_UP:
                return "CARD_SHROOM_ATTACKUP";
            case Effect::ATTACK_DOWN:
                return "CARD_SHROOM_ATTACKDOWN";
            case Effect::DEFENSE_UP:
                return "CARD_SHROOM_DEFENSEUP";
            case Effect::DEFENSE_DOWN:
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
        }
        Ops::unreachable();
    }

    /**
     * @brief Constructor to initialize a BattleMushroomCard object.
     * @param color The mushroom color.
     * @param effect The Battle mushroom effect of the card.
     */
    BattleMushroomCard(MushroomCard::Color color, Effect effect) noexcept:
        MushroomCard(typeToKey(effect)),
        effect{effect}, color{color} {}
public:
    [[nodiscard]]
    Effect getEffect() const noexcept {
        return effect;
    }

    [[nodiscard]]
    MushroomCard::Color getColor() const noexcept {
        return color;
    }

    /**
     * @brief Get the name of the card.
     * @return The name of the card.
     */
    [[nodiscard]]
    String getName(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardName(colorToKey(color));
        return result ? *result : "";
    }

    /**
     * @brief Get the description of the card.
     * @return The description of the card.
     */
    [[nodiscard]]
    String getDescription(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardDescription(typeToKey(effect));
        return result ? *result : "";
    }

    /**
     * @brief Get the card artist name.
     * @return The card artist name.
     */
    [[nodiscard]]
    String getArtistName(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardArtistName(colorToArtistKey(color));
        return result ? *result : "";
    }
};

/**
 * @class BoostMushroomCard
 * @brief Abstract class representing a Boost-type Mushroom card.
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
        NULL_BOOST = Ops::to_underlying(BattleMushroomCard::Effect::ROLL_SIX) + 1, ///< No effect (always appears)
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
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of these cards
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    Effect effect; ///< The effect of the boost mushroom card.
    MushroomCard::Color color; ///< The color of the card.
protected:
    /**
     * @brief Converts the mushroom type to its associated LocalizationService key.
     * @param type The boost mushroom type.
     * @return The key to query in LocalizationService.
     */
    [[nodiscard]]
    static constexpr String typeToKey(Effect type) noexcept {
        switch (type) {
            case Effect::NULL_BOOST:
                // Doze maps to "No effect."
                return "CARD_BOSS_COOP_DOZE";
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
        }
        Ops::unreachable();
    }

    /**
     * @brief Constructor to initialize a BoostMushroomCard object.
     * @param color The mushroom color.
     * @param effect The Boost mushroom effect of the card.
     */
    BoostMushroomCard(MushroomCard::Color color, Effect effect) noexcept:
        MushroomCard(typeToKey(effect)),
        effect{effect}, color{color} {}
public:
    [[nodiscard]]
    Effect getEffect() const noexcept {
        return effect;
    }

    [[nodiscard]]
    MushroomCard::Color getColor() const noexcept {
        return color;
    }

    /**
     * @brief Get the name of the card.
     * @return The name of the card.
     */
    [[nodiscard]]
    String getName(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardName(colorToKey(color));
        return result ? *result : "";
    }

    /**
     * @brief Get the description of the card.
     * @return The description of the card.
     */
    [[nodiscard]]
    String getDescription(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardDescription(typeToKey(effect));
        return result ? *result : "";
    }

    /**
     * @brief Get the card artist name.
     * @return The card artist name.
     */
    [[nodiscard]]
    String getArtistName(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardArtistName(colorToArtistKey(color));
        return result ? *result : "";
    }
};

/**
 * @class LegendaryMushroomCard
 * @brief Abstract class representing a Legendary Mushroom card.
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
     * @enum Color
     * @brief Enumeration for legendary mushroom colors.
     * 
     * The Color enumeration defines the possible colors a legendary mushroom card may have.
     */
    enum class Color: u8 {
        LEGENDARY_RED,
        PHANTOM_BLUE,
    };
private:
    static constexpr Card::Of CARD_TYPE = Card::Of::GIFT; ///< The card type of these cards
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of these cards
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of these cards
    static constexpr Optional<u16> COST = 0; ///< The cost of these cards
    static constexpr u8 LEVEL = 0; ///< The level of these cards
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of these cards per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of these cards

    Effect effect; ///< The effect of the legendary mushroom card.
    Color color; ///< The color of the card.
protected:
    /**
     * @brief Converts the mushroom type to its associated LocalizationService key.
     * @param type The legendary mushroom type.
     * @return The key to query in LocalizationService.
     */
    [[nodiscard]]
    static constexpr String typeToKey(Effect type) noexcept {
        switch (type) {
            case Effect::STARS:
                return "CARD_SHROOM_LEGEND_STARS";
            case Effect::WINS:
                return "CARD_SHROOM_LEGEND_WINS";
        }
        Ops::unreachable();
    }

    /**
     * @brief Converts the mushroom color to its associated LocalizationService key.
     * @param type The legendary mushroom color.
     * @return The key to query in LocalizationService.
     */
    [[nodiscard]]
    static constexpr String colorToKey(Color type) noexcept {
        switch (type) {
            case Color::LEGENDARY_RED:
                return "CARD_SHROOM_LEGENDARYRED";
            case Color::PHANTOM_BLUE:
                return "CARD_SHROOM_PHANTOMBLUE";
        }
        Ops::unreachable();
    }

    /**
     * @brief Converts the legendary mushroom color to the associated LocalizationService key of its artist.
     * @param type The legendary mushroom color.
     * @return The key to query for the artist in LocalizationService.
     */
    [[nodiscard]]
    static constexpr String colorToArtistKey(Color type) noexcept {
        switch (type) {
            case Color::LEGENDARY_RED:
                return "CARD_ARTIST_COFFGIRL";
            case Color::PHANTOM_BLUE:
                return "CARD_ARTIST_COFFGIRL";
        }
        Ops::unreachable();
    }

    /**
     * @brief Constructor to initialize a BoostMushroomCard object.
     * @param color The mushroom color.
     * @param effect The legendary mushroom effect of the card.
     */
    LegendaryMushroomCard(Color color, Effect effect) noexcept:
        MushroomCard(typeToKey(effect)),
        effect{effect}, color{color} {}
public:
    [[nodiscard]]
    Effect getEffect() const noexcept {
        return effect;
    }

    [[nodiscard]]
    Color getColor() const noexcept {
        return color;
    }

    /**
     * @brief Get the name of the card.
     * @return The name of the card.
     */
    [[nodiscard]]
    String getName(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardName(colorToKey(color));
        return result ? *result : "";
    }

    /**
     * @brief Get the description of the card.
     * @return The description of the card.
     */
    [[nodiscard]]
    String getDescription(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardDescription(typeToKey(effect));
        return result ? *result : "";
    }

    /**
     * @brief Get the card artist name.
     * @return The card artist name.
     */
    [[nodiscard]]
    String getArtistName(const LocalizationService& loc) const noexcept override {
        Expected<String, LocalizationService::Error> result = loc.getCardArtistName(colorToArtistKey(color));
        return result ? *result : "";
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::card::mushroom::BattleMushroomCard;
using openjuice::engine::card::mushroom::BoostMushroomCard;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;

namespace stdx::fmt {
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
                case BattleMushroomCard::Effect::DEFENSE_UP:
                    name = "Gain Defense";
                    break;
                case BattleMushroomCard::Effect::DEFENSE_DOWN:
                    name = "Lose Defense";
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
            }
            return format_to(ctx.out(), "{}", name);
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
            }
            return format_to(ctx.out(), "{}", name);
        }
    };

    template <>
    struct Formatter<LegendaryMushroomCard::Color> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(LegendaryMushroomCard::Color type, FormatContext& ctx) {
            StringView name;
            switch (type) {
                case LegendaryMushroomCard::Color::LEGENDARY_RED:
                    name = "Legendary Red Mushroom";
                    break;
                case LegendaryMushroomCard::Color::PHANTOM_BLUE:
                    name = "Phantom Blue Mushroom";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
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
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(BattleMushroomCard::Effect);
SPECIALIZE_FORMATTER(BoostMushroomCard::Effect);
SPECIALIZE_FORMATTER(LegendaryMushroomCard::Color);
SPECIALIZE_FORMATTER(LegendaryMushroomCard::Effect);
