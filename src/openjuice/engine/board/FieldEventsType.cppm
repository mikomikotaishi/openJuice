/**
 * @file FieldEventsType.cppm
 * @module openjuice.engine.board.FieldEventsType
 * @brief Definition of the FieldEventsType enum class.
 *
 * This file contains the definition of the FieldEventsType enum class, which represents field event types.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.board.FieldEventsType;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @enum FieldEventsType
 * @brief Enumeration for card types.
 * 
 * The FieldEventsType enumeration defines the types of cards in the game.
 */
export enum class FieldEventsType: u8 {
    // Placeholders
    NONE, ///< Empty
    DEFAULT, ///< Default field event for a map
    RANDOM, ///< Random non-duplicate field 

    // Standard
    AIR_RAID, ///< All takes 1 damage at beginning of Chapter (every 5 chapters)
    AMPLIFY, ///< All units randomly receive a bonus stat for 2 Chapters (every 6 chapters)
    BACKTRACK, ///< All units move in the reverse definition for the rest of the Chapter (every 8 chapters)
    BOMBER, ///< Places a bomb on a random panel that explodes within 1-4 Chapters, dealing 2 points of damage within 3 panels of a cross-shaped area (every 2 chapters)
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
    BOSS_ENCOUNTER, 
    TERROR,
    CHAOS_BATTLEFIELD,
    STARVATION,
    OVERINDULGENCE,
    CONVERGENCE
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::FieldEventsType;

template <>
struct Formatter<FieldEventsType> {
    static constexpr const char* parse(FormatParseContext& ctx) {
        return ctx.begin();
    }

    static FormatContext::Iterator format(FieldEventsType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            // Placeholders
            case FieldEventsType::NONE:
                name = "None"; 
                break;
            case FieldEventsType::DEFAULT: 
                name = "Default"; 
                break;
            case FieldEventsType::RANDOM: 
                name = "Random"; 
                break;
            
            // Standard
            case FieldEventsType::AIR_RAID: 
                name = "Air Raid"; 
                break;
            case FieldEventsType::AMPLIFY: 
                name = "Amplify"; 
                break;
            case FieldEventsType::BACKTRACK: 
                name = "Backtrack"; 
                break;
            case FieldEventsType::BOMBER: 
                name = "Bomber"; 
                break;
            case FieldEventsType::CHARITY: 
                name = "Charity"; 
                break;
            case FieldEventsType::CONFUSION: 
                name = "Confusion"; 
                break;
            case FieldEventsType::FISH_A_FISH: 
                name = "Fish-a-Fish"; 
                break;
            case FieldEventsType::FREEZE: 
                name = "Freeze"; 
                break;
            case FieldEventsType::GOO: 
                name = "Goo"; 
                break;
            case FieldEventsType::HOME_ROULETTE: 
                name = "Home Roulette"; 
                break;
            case FieldEventsType::MINELAYER: 
                name = "Minelayer"; 
                break;
            case FieldEventsType::MIRACLE: 
                name = "Miracle"; 
                break;
            case FieldEventsType::MYSTERY: 
                name = "Mystery"; 
                break;
            case FieldEventsType::PLAYGROUND: 
                name = "Playground"; 
                break;
            case FieldEventsType::RANDOM_WARP: 
                name = "Random Warp"; 
                break;
            case FieldEventsType::REGENERATION: 
                name = "Regeneration"; 
                break;
            case FieldEventsType::SPORES: 
                name = "Spores"; 
                break;
            case FieldEventsType::SPRINT: 
                name = "Sprint"; 
                break;
            case FieldEventsType::TREASURE: 
                name = "Treasure"; 
                break;
            
            // Automatic
            case FieldEventsType::BOSS_ENCOUNTER: 
                name = "Boss Encounter"; 
                break;
            case FieldEventsType::TERROR: 
                name = "Terror"; 
                break;
            case FieldEventsType::CHAOS_BATTLEFIELD: 
                name = "Chaos Battlefield"; 
                break;
            case FieldEventsType::STARVATION: 
                name = "Starvation"; 
                break;
            case FieldEventsType::OVERINDULGENCE: 
                name = "Overindulgence"; 
                break;
            case FieldEventsType::CONVERGENCE: 
                name = "Convergence"; 
                break;
                
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(FieldEventsType);
