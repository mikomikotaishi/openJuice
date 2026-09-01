/**
 * @file FieldEvent.cppm
 * @module openjuice.engine.board:FieldEvent
 * @brief Definition of the FieldEvent class.
 *
 * This file contains the definition of the FieldEvent class, which represents field event types.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board:FieldEvent;

import stdx;

import openjuice.engine.util;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class FieldEvent
 * @brief Class representing field event types.
 */
export class FieldEvent {
public:
    /**
     * @enum Of
     * @brief Enumeration for card types.
     *
     * The Of enumeration defines the types of cards in the game.
     */
    enum class Of: u8 {
        // Standard
        AIR_RAID, ///< All takes 1 damage at beginning of Chapter (every 5 chapters)
        AMPLIFY, ///< All units randomly receive a bonus stat for 2 Chapters (every 6 chapters)
        BACKTRACK, ///< All units move in the reverse definition for the rest of the Chapter (every 8 chapters)
        BOMBER, ///< Places a bomb on a random panel that explodes within 1-4 Chapters, dealing 2 points of damage within 3 panels of a cross-shaped area (every 2 chapters)
        CAKES, ///< All players receive Mio's False Cake, either used as 1 damage missile or grants random effect (every 6 chapters)
        CHARITY, ///< All players draw 1 card at the beginning of Chapter (every 5 chapters)
        CONFUSION, ///< All player's cards are rearranged and put face-down, unreadable to both the owner and other players, for the rest of the chapter (every 7 chapters)
        FISH_A_FISH, ///< Activates the fishing minigame (every 9 chapters)
        FREEZE, ///< Sets a third of the board's panels into Ice panels for the duration of the Chapter, except for Home panels (every 5 chapters)
        GOO, ///< Sets a third of the board's panels into Goo panels for the duration of the Chapter, except for Home panels or Ice panels (every 5 chapters)
        HOME_ROULETTE, ///< All Home panels randomly switch places at beginning of the Chapter (every 9 chapters)
        MINELAYER, ///< Randomly places one of Dangerous Pudding, Bad Pudding, Mimyuu's Hammer (trap cards) on a random panel (every 3 chapters)
        MIRACLE, ///< All Bonus, Drop, Encounter, Draw, Move, WarpMove, Heal, Damage panels become 2x panels for the rest of the Chapter (every 5 chapters)
        MYSTERY, ///< Any of the listed field effects may occur (every 5 chapters)
        PLAYGROUND, ///< Random Minigame panels spawn around the board, triggering a minigame (except on Home panels), for the rest of the Chapter (every 5 chapters)
        RANDOM_WARP, ///< All units are randomly warped to randomly chosen panels at the start of the Chapter (every 5 chapters)
        REGENERATION, ///< All units recover 1 HP at the beginning of the Chapter (every 5 chapters)
        SPORES, ///< Several mushrooms are placed on random panels, giving a Mushroom card (every 3 chapters)
        SPRINT, ///< All units roll double dice for movement, for the duration of the Chapter (every 6 chapters)
        TREASURE, ///< A Red or Blue chest is placed on a random panel (up to board size limit), giving the contents (every chapter)

        // Automatic
        BOSS_ENCOUNTER, ///< All Encounter panels on the map are replaced with Boss panels, until Boss is defeated (triggered when norma level 4 achieved for the first time by any player)
        TERROR, ///< Random Boss panels spawn around the board. Increases as game progresses. Does not affect Home, Warp, or Warp Move panels (on co-op mode: every 2 chapters before chapter 40, every chapter after chapter 40)
        CHAOS_BATTLEFIELD, ///< All panels become Player Encounter panels, disables Home panel stop options, until end of Chapter (every 10 chapters)
        STARVATION, ///< All players gain amount of stars equal to current HP, then every player's HP becomes 1 (on chapter 1, then every 8 chapters)
        OVERINDULGENCE, ///< All Bonus and Drop panels become Heal panels, lasting for 3 Chapters (every 6 chapters)
        CONVERGENCE, ///< Current field changes to another random field (every 6 chapters)
    };

    /**
     * @enum Trigger
     * @brief Enumeration for trigger types.
     *
     * The Trigger enumeration defines how the field event is triggered in the game.
     */
    enum class Trigger: u8 {
        NONE, ///< Empty
        DEFAULT, ///< Default field event for a map
        RANDOM, ///< Random non-duplicate field
    };

    /**
     * @struct Data
     * @brief Struct aggregating key information about field events.
     */
    struct [[nodiscard]] Data {
        Trigger trigger; ///< The trigger type for the field event.
        Of type; ///< The field event type.
    };
private:
    Data data; ///< The data for the field event.
public:
    /**
     * @brief Construct a new FieldEvent object.
     * @param data The data for the field event.
     */
    constexpr FieldEvent(Data data):
        data{data} {}

    /**
     * @brief Construct a new FieldEvent object.
     * @param trigger The trigger type for the field event.
     * @param type The type of the field event.
     */
    constexpr FieldEvent(Trigger trigger, Of type):
        data{trigger, type} {}

    [[nodiscard]]
    constexpr Data getData() const noexcept {
        return data;
    }

    [[nodiscard]]
    constexpr Trigger getTrigger() const noexcept {
        return data.trigger;
    }

    [[nodiscard]]
    constexpr Of getType() const noexcept {
        return data.type;
    }

    /**
     * @brief Parse a board's TOML event string into a Data slot.
     * @param name The event string from a board's `events` array.
     * @return The corresponding Data slot.
     */
    [[nodiscard]]
    static constexpr Data fromString(StringView name) noexcept {
        switch (engine::util::hashString(name)) {
            case ""_hash:
            case "None"_hash:
                return Data {
                    .trigger = Trigger::NONE, 
                    .type = Of::AIR_RAID
                };
            case "Random"_hash:
                return Data {
                    .trigger = Trigger::RANDOM,
                    .type = Of::AIR_RAID
                };

            // Standard
            case "Air Raid"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::AIR_RAID
                };
            case "Amplify"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::AMPLIFY
                };
            case "Backtrack"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::BACKTRACK
                };
            case "Bomber"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::BOMBER
                };
            case "Cakes"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::CAKES
                };
            case "Charity"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::CHARITY
                };
            case "Confusion"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::CONFUSION
                };
            case "Fish-a-Fish"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::FISH_A_FISH
                };
            case "Freeze"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::FREEZE
                };
            case "Goo"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::GOO
                };
            case "Home Roulette"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::HOME_ROULETTE
                };
            case "Minelayer"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::MINELAYER
                };
            case "Miracle"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::MIRACLE
                };
            case "Mystery"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::MYSTERY
                };
            case "Playground"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::PLAYGROUND
                };
            case "Random Warp"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::RANDOM_WARP
                };
            case "Regeneration"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::REGENERATION
                };
            case "Spores"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::SPORES
                };
            case "Sprint"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::SPRINT
                };
            case "Treasure"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::TREASURE
                };

            // Automatic
            case "Boss Encounter"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::BOSS_ENCOUNTER
                };
            case "Terror"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::TERROR
                };
            case "Chaos Battlefield"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::CHAOS_BATTLEFIELD
                };
            case "Starvation"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::STARVATION
                };
            case "Overindulgence"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::OVERINDULGENCE
                };
            case "Convergence"_hash:
                return Data {
                    .trigger = Trigger::DEFAULT,
                    .type = Of::CONVERGENCE
                };

            default:
                return Data {
                    .trigger = Trigger::NONE,
                    .type = Of::AIR_RAID
                };
        }
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::FieldEvent;

namespace stdx::fmt {
    template <>
    struct Formatter<FieldEvent::Of> {
        static constexpr const char* parse(FormatParseContext& ctx) {
            return ctx.begin();
        }

        static FormatContext::iterator format(FieldEvent::Of type, FormatContext& ctx) {
            StringView name;
            switch (type) {
                // Standard
                case FieldEvent::Of::AIR_RAID:
                    name = "Air Raid"; 
                    break;
                case FieldEvent::Of::AMPLIFY:
                    name = "Amplify"; 
                    break;
                case FieldEvent::Of::BACKTRACK:
                    name = "Backtrack"; 
                    break;
                case FieldEvent::Of::BOMBER:
                    name = "Bomber"; 
                    break;
                case FieldEvent::Of::CAKES:
                    name = "Cakes";
                    break;
                case FieldEvent::Of::CHARITY:
                    name = "Charity"; 
                    break;
                case FieldEvent::Of::CONFUSION:
                    name = "Confusion"; 
                    break;
                case FieldEvent::Of::FISH_A_FISH:
                    name = "Fish-a-Fish"; 
                    break;
                case FieldEvent::Of::FREEZE:
                    name = "Freeze"; 
                    break;
                case FieldEvent::Of::GOO:
                    name = "Goo"; 
                    break;
                case FieldEvent::Of::HOME_ROULETTE:
                    name = "Home Roulette"; 
                    break;
                case FieldEvent::Of::MINELAYER:
                    name = "Minelayer"; 
                    break;
                case FieldEvent::Of::MIRACLE:
                    name = "Miracle"; 
                    break;
                case FieldEvent::Of::MYSTERY:
                    name = "Mystery"; 
                    break;
                case FieldEvent::Of::PLAYGROUND:
                    name = "Playground"; 
                    break;
                case FieldEvent::Of::RANDOM_WARP:
                    name = "Random Warp"; 
                    break;
                case FieldEvent::Of::REGENERATION:
                    name = "Regeneration"; 
                    break;
                case FieldEvent::Of::SPORES:
                    name = "Spores"; 
                    break;
                case FieldEvent::Of::SPRINT:
                    name = "Sprint"; 
                    break;
                case FieldEvent::Of::TREASURE:
                    name = "Treasure"; 
                    break;
                
                // Automatic
                case FieldEvent::Of::BOSS_ENCOUNTER:
                    name = "Boss Encounter"; 
                    break;
                case FieldEvent::Of::TERROR:
                    name = "Terror"; 
                    break;
                case FieldEvent::Of::CHAOS_BATTLEFIELD:
                    name = "Chaos Battlefield"; 
                    break;
                case FieldEvent::Of::STARVATION:
                    name = "Starvation"; 
                    break;
                case FieldEvent::Of::OVERINDULGENCE:
                    name = "Overindulgence"; 
                    break;
                case FieldEvent::Of::CONVERGENCE:
                    name = "Convergence"; 
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(FieldEvent::Of);
