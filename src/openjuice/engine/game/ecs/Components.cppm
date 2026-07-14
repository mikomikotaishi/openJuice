/**
 * @file Components.cppm
 * @module openjuice.engine.game.ecs:Components
 * @brief Module of ECS components.
 *
 * This file contains the definitions for all ECS components.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs:Components;

import stdx;

import openjuice.engine.card;
import openjuice.engine.unit;

using stdx::collections::BitSet;
using stdx::collections::Vector;
using stdx::mem::SharedPointer;

using openjuice::engine::card::Card;
using openjuice::engine::card::spawn::MushroomCard;
using openjuice::engine::unit::Unit;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @namespace components
 * @brief Namespace of Components for the ECS system.
 */
export namespace components {
    /**
     * @enum DefenseChoice
     * @brief Enumeration for defense choices
     */
    enum class DefenseChoice: u8 {
        DEFEND, ///< Defend choice
        EVADE ///< Evade choice
    };

    /**
     * @struct HealthComponent
     * @brief Component for Health system
     */
    struct HealthComponent {
        u8 currentHealth;
        u8 maxHealth;
    };

    /**
     * @struct StarComponent
     * @brief Component for Stars system
     */
    struct StarComponent {
        u16 stars = 0;
    };

    /**
     * @struct PlayerComponent
     * @brief Component for Player system
     */
    struct PlayerComponent {
        u8 wins = 0;
        u8 norma = 1;
    };

    /**
     * @struct UnitComponent
     * @brief Component for Unit system
     */
    struct UnitComponent {
        SharedPointer<Unit> unit;
    };

    /**
     * @struct BattleStateComponent
     * @brief Component for tracking battle state
     */
    struct BattleStateComponent {
        SharedPointer<Card> activeBattleCard = nullptr;
        DefenseChoice defenseChoice = DefenseChoice::DEFEND;
    };

    /**
     * @struct BattleCardComponent
     * @brief Component for battle card
     */
    struct BattleCardComponent {
        i8 attackModifier = 0;
        i8 defenseModifier = 0;
        i8 evadeModifier = 0;
        u8 extraDice = 0;
    };

    /**
     * @struct HandComponent
     * @brief Component for Hand system
     */
    struct HandComponent {
        Vector<SharedPointer<Card>> cards;
    };

    /**
     * @struct MushroomComponent
     * @brief Component for tracking used mushrooms
     */
    struct MushroomComponent {
        // Consists of (in this order):
        // Blue, Brown, Green, Orange, Pink, Purple, Rainbow, Red, White, Yellow
        BitSet<MushroomCard::NUM_MUSHROOMS> usedMushrooms; ///< The Mushrooms that have been used by the player.

        // Consists of (in this order):
        // Legendary Red, Phantom Blue
        BitSet<MushroomCard::NUM_LEGENDARY_MUSHROOMS> usedLegendaryMushrooms; ///< The Legendary Mushrooms that have been used by the player.
        
        void reset() {
            usedMushrooms.reset();
            usedLegendaryMushrooms.reset();
        }
    };

    /**
     * @struct PlayerTag
     * @brief Tag for Player
     */
    struct PlayerTag {
        PlayerTag() = default;
    };

    /**
     * @struct MobTag
     * @brief Tag for Mob
     */
    struct MobTag {
        MobTag() = default;
    };
}

END_MODULE_NAMESPACE();
