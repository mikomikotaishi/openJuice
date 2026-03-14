/**
 * @file Systems.cppm
 * @module openjuice.engine.game.ecs.Systems
 * @brief Module of ECS systems.
 *
 * This file contains the definitions for all ECS systems.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs:Systems;

#define SYSTEMS_DEPRECATION_MESSAGE "Outdated ECS system handling, use openjuice::engine::game::ecs::Registry instead"

import stdx;

import :Components;
import :Registry;

import openjuice.engine.card.Card;
import openjuice.engine.game.Dice;

using stdx::mem::SharedPointer;

using openjuice::engine::card::Card;

using namespace openjuice::engine::game::ecs::components;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

#if 0
/**
 * @namespace ecs::systems
 * @brief Namespace of Systems for the ECS system.
 */
export namespace systems {
    /**
     * @class DamageSystem
     * @brief System for Damage
     * 
     * @implements ISystem
     */
    class [[deprecated(SYSTEMS_DEPRECATION_MESSAGE)]] DamageSystem: public ISystem {
    private:
        static inline const SharedPointer<Coordinator> COORDINATOR = Coordinator::getInstance(); //< The coordinator instance

        /**
         * @brief 
         * 
         * @param deadEntity 
         * @param killer 
         *
         * @throws NullPointerException if there is an error obtaining a component
         */
        void handleDeath(EntityId deadEntity, EntityId killer) throws (NullPointerException) {
            SharedPointer<StarComponent> deadStars = COORDINATOR->getComponent<StarComponent>(deadEntity);
            SharedPointer<StarComponent> killerStars = COORDINATOR->getComponent<StarComponent>(killer);

            if (!deadStars) {
                throw NullPointerException("Error obtaining dead unit stars component!");
            }
            if (!killerStars) {
                throw NullPointerException("Error obtaining killer stars component!");
            }

            if (deadStars && killerStars) {
                u16 transferAmount = deadStars->stars / 2;
                killerStars->stars += transferAmount;
            }

            SharedPointer<PlayerComponent> killerPlayer = COORDINATOR->getComponent<PlayerComponent>(killer);
            if (killerPlayer) {
                killerPlayer->wins += COORDINATOR->getComponent<PlayerTag>(deadEntity) ? 2 : 1;
            }
        }
    public:
        /**
         * @brief Construct a new Damage System object
         */
        DamageSystem() = default;

        /**
         * @brief Destroy the Damage System object
         */
        virtual ~DamageSystem() = default;
    
        /**
         * @brief 
         * 
         * @param target 
         * @param amount 
         * @param source 
         * @return true if amount is greater or equal to the the target health's current health, false otherwise.
         *
         * @throws NullPointerException if there is an error obtaining a component
         */
        [[nodiscard]] 
        bool applyDamage(EntityId target, u8 amount, EntityId source) throws (NullPointerException) {
            SharedPointer<HealthComponent> health = COORDINATOR->getComponent<HealthComponent>(target);
            if (!health) {
                throw NullPointerException("Error obtaining health component!");
            }

            if (amount >= health->currentHealth) {
                health->currentHealth = 0;
                handleDeath(target, source);
                return true;
            } else {
                health->currentHealth -= amount;
                return false;
            }
        }

        /**
         * @brief 
         * 
         * @param deltaTime 
         */
        void update(f32 deltaTime) override {
            return;
        }
    };

    /**
     * @class BattleSystem
     * @brief System for Battle
     *
     * @implements ISystem 
     */
    class [[deprecated(SYSTEMS_DEPRECATION_MESSAGE)]] BattleSystem: public ISystem {
    private:
        static inline const SharedPointer<Coordinator> COORDINATOR = Coordinator::getInstance(); //< The coordinator instance

        SharedPointer<DamageSystem> damageSystem;
    public:
        /**
         * @brief Construct a new Battle System object
         */
        BattleSystem() = default;

        /**
         * @brief Destroy the Battle System object
         */
        virtual ~BattleSystem() = default;

        /**
         * @brief Set the Damage System object
         * 
         * @param system 
         */
        void setDamageSystem(SharedPointer<DamageSystem> system) noexcept {
            damageSystem = system;
        }

        /**
         * @brief 
         * 
         * @param attacker The attacker entity ID
         * @param defender The defender entity ID
         * @return The damage dealt to the defender
         *
         * @throws NullPointerException if there is an error obtaining a component
         */
        [[nodiscard]]
        u8 calculateDamage(EntityId attacker, EntityId defender) throws (NullPointerException) {
            SharedPointer<UnitComponent> attackerUnit = COORDINATOR->getComponent<UnitComponent>(attacker);
            SharedPointer<UnitComponent> defenderUnit = COORDINATOR->getComponent<UnitComponent>(defender);

            if (!attackerUnit || !attackerUnit->unit) {
                throw NullPointerException("Error obtaining attacker component!");
            }
            if (!defenderUnit || !defenderUnit->unit) {
                throw NullPointerException("Error obtaining defender component!");
            }

            SharedPointer<BattleStateComponent> battleState = COORDINATOR->getComponent<BattleStateComponent>(defender);

            if (!battleState) {
                throw NullPointerException("Error obtaining defender battle state component!");
            }

            i8 attackModifier = attackerUnit->unit->getAttack();
            i8 defenceModifier = defenderUnit->unit->getDefence();
            i8 evadeModifier = defenderUnit->unit->getEvade();

            u8 attackRoll = static_cast<u8>(Dice::getInstance().rollD6() + attackModifier);
            attackRoll = attackRoll < 1 ? 1 : attackRoll;

            u8 defenceRoll = 0;

            if (battleState->defenceChoice == DefenceChoice::DEFEND) {
                defenceRoll = static_cast<u8>(Dice::getInstance().rollD6() + defenceModifier);
                defenceRoll = defenceRoll < 1 ? 1 : defenceRoll;
                return attackRoll > defenceRoll ? attackRoll - defenceRoll : 1;
            } else {
                defenceRoll = static_cast<u8>(Dice::getInstance().rollD6() + evadeModifier);
                defenceRoll = defenceRoll < 1 ? 1 : defenceRoll;
                return attackRoll >= defenceRoll ? attackRoll : 0;
            }
            System::unreachable();
        }

        /**
         * @brief 
         * 
         * @param attacker 
         * @param defender 
         * @return true if applyDamage returns true, false otherwise
         *
         * @throws NullPointerException if the damage system is not initialised
         */
        [[nodiscard]] 
        bool executeBattle(EntityId attacker, EntityId defender) throws (NullPointerException) {
            if (!damageSystem) {
                throw NullPointerException("Damage system not initialised!");
            }
            SharedPointer<BattleStateComponent> battleState = COORDINATOR->addComponent<BattleStateComponent>(defender);
            if (!battleState) {
                throw NullPointerException("Error obtaining battle state!");
            }

            u8 damage = calculateDamage(attacker, defender);
            bool defenderDefeated = damageSystem->applyDamage(defender, damage, attacker);

            if (!defenderDefeated) {
                SharedPointer<BattleStateComponent> counterBattleState = COORDINATOR->addComponent<BattleStateComponent>(attacker);
                u8 counterDamage = calculateDamage(defender, attacker);
                bool attackerDefeated = damageSystem->applyDamage(attacker, counterDamage, defender);
            }

            COORDINATOR->removeComponent<BattleStateComponent>(defender);
            if (!defenderDefeated) {
                COORDINATOR->removeComponent<BattleStateComponent>(attacker);
            }
            return true;
        }

        /**
         * @brief 
         * 
         * @param deltaTime 
         */
        void update(f32 deltaTime) override {
            return;
        }
    };

    /**
     * @class BattleManagerSystem
     * @brief System for managing battle flow and user interaction
     * 
     * @implements ISystem
     */
    class [[deprecated(SYSTEMS_DEPRECATION_MESSAGE)]] BattleManagerSystem: public ISystem {
    private:
        static inline const SharedPointer<Coordinator> COORDINATOR = Coordinator::getInstance(); //< The coordinator instance    

        SharedPointer<BattleSystem> battleSystem;

        EntityId currentAttacker = 0;
        EntityId currentDefender = 0;
        bool battleInProgress = false;
    public:
        /**
         * @brief Construct a new Battle Manager System object
         */
        BattleManagerSystem() = default;

        /**
         * @brief Destroy the Battle Manager System object
         */
        virtual ~BattleManagerSystem() = default;

        /**
         * @brief Set the Battle System reference
         */
        void setBattleSystem(SharedPointer<BattleSystem> system) {
            battleSystem = system;
        }

        /**
         * @brief Start a battle between two entities
         * 
         * @param attacker 
         * @param defender 
         * @return true if a battle completes, false otherwise
         */
        [[nodiscard]] 
        bool startBattle(EntityId attacker, EntityId defender) {
            if (battleInProgress) {
                return false;
            }

            currentAttacker = attacker;
            currentDefender = defender;
            battleInProgress = true;

            return true;
        }

        /**
         * @brief Set the Defence Choice object
         * 
         * @param choice 
         */
        void setDefenceChoice(DefenceChoice choice) const {
            if (!battleInProgress) {
                return;
            }

            SharedPointer<BattleStateComponent> battleState = COORDINATOR->getComponent<BattleStateComponent>(currentDefender);
            if (battleState) {
                battleState->defenceChoice = choice;
            }
        }

        /**
         * @brief Play a battle card for an entity
         * 
         * @param entity 
         * @param card 
         */
        void playBattleCard(EntityId entity, const SharedPointer<Card>& card) const {
            if (!battleInProgress) {
                return;
            }

            SharedPointer<BattleStateComponent> battleState = COORDINATOR->getComponent<BattleStateComponent>(entity);
            if (battleState) {
                battleState->activeBattleCard = card;

                card->play();
            }
        }

        /**
         * @brief Execute the current battle
         *
         * @throws NullPointerException 
         */
        void executeBattle() throws (NullPointerException) {
            if (!battleSystem) {
                throw NullPointerException("Battle system not initialised!");
            }
            if (!battleInProgress) {
                return;
            }
            bool battleExecuted = battleSystem->executeBattle(currentAttacker, currentDefender);
            battleInProgress = false;
        }

        /**
         * @brief 
         * 
         * @param deltaTime 
         */
        void update(f32 deltaTime) override {
            return;
        }
    };
}

#endif

END_MODULE_NAMESPACE();
