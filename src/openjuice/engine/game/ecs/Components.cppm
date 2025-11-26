/**
 * @file Components.cppm
 * @module openjuice.engine.game.ecs.Components
 * @brief Module of ECS components.
 *
 * This file contains the definitions for all ECS components.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs.Components;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.game.ecs.IComponent;
import openjuice.engine.unit.Unit;

using std::collections::BitSet;
using std::collections::Vector;
using std::mem::SharedPointer;

namespace util = std::util;

using openjuice::engine::card::Card;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::unit::Unit;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @namespace components
 * @brief Namespace of Components for the ECS system.
 */
export namespace components {
    /**
     * @enum DefenceChoice
     * @brief Enumeration for defence choices
     */
    enum class DefenceChoice: u8 {
        DEFEND, ///< Defend choice
        EVADE ///< Evade choice
    };

    /**
     * @struct HealthComponent
     * @brief Component for Health system
     *
     * @implements IComponent
     */
    struct HealthComponent {
        u8 currentHealth;
        u8 maxHealth;

        /**
         * @brief Construct a new Health Component object
         * 
         * @param currentHealth 
         * @param maxHealth 
         */
        HealthComponent(u8 currentHealth, u8 maxHealth):
            currentHealth{currentHealth}, maxHealth{maxHealth} {}
    };

    /**
     * @struct StarComponent
     * @brief Component for Stars system
     *
     * @implements IComponent
     */
    struct StarComponent: public IComponent {
        u16 stars = 0;

        /**
         * @brief Construct a new Star Component object
         * 
         * @param initialStars 
         */
        explicit StarComponent(u16 initialStars):
            stars{initialStars} {}
        
        StarComponent() = default;
    };

    /**
     * @struct PlayerComponent
     * @brief Component for Player system
     *
     * @implements IComponent
     */
    struct PlayerComponent: public IComponent {
        u8 wins = 0;
        u8 norma = 1;

        /**
         * @brief Construct a new Player Component object
         * 
         * @param initialWins 
         * @param initialNorma 
         */
        explicit PlayerComponent(u8 initialWins, u8 initialNorma):
            wins{initialWins}, norma{initialNorma} {}
        
        PlayerComponent() = default;
    };

    /**
     * @struct UnitComponent
     * @brief Component for Unit system
     *
     * @implements IComponent
     */
    struct UnitComponent: public IComponent {
        SharedPointer<Unit> unit;

        /**
         * @brief Construct a new Unit Component object
         * 
         * @param unitPointer 
         */
        explicit UnitComponent(SharedPointer<Unit> unitPointer):
            unit{util::move(unitPointer)} {}
        
        UnitComponent() = default;
    };

    /**
     * @struct BattleStateComponent
     * @brief Component for tracking battle state
     * 
     * @implements IComponent
     */
    struct BattleStateComponent: public IComponent {
        DefenceChoice defenceChoice = DefenceChoice::DEFEND;
        SharedPointer<Card> activeBattleCard;

        /**
         * @brief Construct a new Battle State Component object
         * 
         * @param choice 
         */
        explicit BattleStateComponent(DefenceChoice choice):
            defenceChoice{choice}, activeBattleCard{nullptr} {}
        
        BattleStateComponent() = default;
    };

    /**
     * @struct BattleCardComponent
     * @brief Component for battle card
     *
     * @implements IComponent
     */
    struct BattleCardComponent: public IComponent {
        i8 attackModifier = 0;
        i8 defenceModifier = 0;
        i8 evadeModifier = 0;
        u8 extraDice = 0;

        /**
         * @brief Construct a new Battle Card Component object
         * 
         * @param attack 
         * @param defence 
         * @param evade 
         * @param dice 
         */
        explicit BattleCardComponent(i8 attack, i8 defence, i8 evade, u8 dice):
            attackModifier{attack}, defenceModifier{defence}, evadeModifier{evade}, extraDice{dice} {}
        
        BattleCardComponent() = default;
    };

    /**
     * @struct HandComponent
     * @brief Component for Hand system
     *
     * @implements IComponent
     */
    struct HandComponent: public IComponent {
        Vector<SharedPointer<Card>> cards;
        
        HandComponent() = default;
    };

    /**
     * @struct MushroomComponent
     * @brief Component for tracking used mushrooms
     *
     * @implements IComponent
     */
    struct MushroomComponent: public IComponent {
        // Consists of (in this order):
        // Blue, Brown, Green, Orange, Pink, Purple, Rainbow, Red, White, Yellow
        BitSet<MushroomCard::NUM_MUSHROOMS> usedMushrooms; ///< The Mushrooms that have been used by the player.

        // Consists of (in this order):
        // Legendary Red, Phantom Blue
        BitSet<MushroomCard::NUM_LEGENDARY_MUSHROOMS> usedLegendaryMushrooms; ///< The Legendary Mushrooms that have been used by the player.
        
        MushroomComponent() = default;
        
        void reset() {
            usedMushrooms.reset();
            usedLegendaryMushrooms.reset();
        }
    };

    /**
     * @interface PlayerTag
     * @brief Tag for Player
     *
     * @extends IComponent
     */
    struct PlayerTag: public IComponent {
        PlayerTag() = default;
    };

    /**
     * @interface MobTag
     * @brief Tag for Mob
     *
     * @extends IComponent
     */
    struct MobTag: public IComponent {
        MobTag() = default;
    };
}

END_MODULE_NAMESPACE();
