/**
 * @file GamePhase.cppm
 * @module openjuice.engine.game.Game:GamePhase
 * @brief Definition of the GamePhase enum class.
 *
 * This file contains the definition of the GamePhase enum class, which represents phases of the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.Game:GamePhase;

import stdx;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game);

/**
 * @enum GamePhase
 * @brief Enumeration of game phases
 */
export enum class GamePhase: u8 {
    SETUP, ///< Initial game setup 
    PLAYER_TURN, ///< Player taking their turn
    BATTLE_PHASE, ///< Battle in progress
    CHAPTER_PHASE, ///< Chapter event in progress
    END_GAME, ///< Game completed
    PAUSED, ///< Game paused
};

END_MODULE_NAMESPACE();

using openjuice::engine::game::GamePhase;

template <>
struct Formatter<GamePhase> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(GamePhase phase, FormatContext& ctx) {
        StringView name;
        switch (phase) {
            case GamePhase::SETUP:
                name = "Setup"; 
                break;
            case GamePhase::PLAYER_TURN:
                name = "Player Turn"; 
                break;
            case GamePhase::BATTLE_PHASE:
                name = "Battle"; 
                break;
            case GamePhase::CHAPTER_PHASE:
                name = "Chapter Event"; 
                break;
            case GamePhase::END_GAME:
                name = "End Game"; 
                break;
            case GamePhase::PAUSED:
                name = "Paused"; 
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(GamePhase);
