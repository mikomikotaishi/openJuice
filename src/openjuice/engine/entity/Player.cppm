/**
 * @file Player.cppm
 * @module openjuice.engine.entity.Player
 * @brief Implementation of the Player class.
 *
 * This file contains the implementation of the Player class, which represents a player entity in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.entity.Player;

import std;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.entity.Entity;
import openjuice.engine.game.ecs.Components;
import openjuice.engine.game.ecs.Registry;
import openjuice.engine.unit.Playable;
import openjuice.engine.unit.Unit;

using std::collections::BitSet;
using std::collections::Vector;
using std::mem::SharedPointer;
using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;
using openjuice::engine::card::spawntypes::MushroomCard;
using openjuice::engine::game::ecs::Registry;
using openjuice::engine::game::ecs::components::PlayerTag;
using openjuice::engine::game::ecs::components::PlayerComponent;
using openjuice::engine::game::ecs::components::HandComponent;
using openjuice::engine::game::ecs::components::MushroomComponent;
using openjuice::engine::unit::Playable;
using openjuice::engine::unit::Unit;

BEGIN_MODULE_NAMESPACE(openjuice::engine::entity);

/**
 * @class Player
 * @brief Class representing a player entity.
 *
 * @extends Entity
 *
 * The Player class extends the Entity abstract class and represents a player entity with attributes such as wins, norma, and hand.
 */
export class Player: public Entity {
public:
    /**
     * @brief Constructor to initialise a Player object.
     *
     * @param reg Reference to the ECS registry
     * @param character The character associated with the player.
     */
    explicit Player(Registry& reg, const SharedPointer<Playable>& character = nullptr):
        Entity(reg, character) {
        registry->emplace<PlayerTag>(getEntityId());
        registry->emplace<PlayerComponent>(getEntityId());
        registry->emplace<HandComponent>(getEntityId());
        registry->emplace<MushroomComponent>(getEntityId());
    }

    /**
     * @brief Get the number of wins the player has.
     *
     * @return The number of wins.
     */
    [[nodiscard]]
    u8 getWins() const noexcept {
        PlayerComponent* playerComp = registry->getIf<PlayerComponent>(getEntityId());
        return playerComp ? playerComp->wins : 0;
    }

    /**
     * @brief Set the number of wins the player has.
     *
     * @param wins The number of wins to set.
     */
    void setWins(u8 wins) noexcept {
        if (PlayerComponent* playerComp = registry->getIf<PlayerComponent>(getEntityId())) {
            playerComp->wins = wins;
        }
    }

    /**
     * @brief Get the norma level of the player.
     *
     * @return The norma level.
     */
    [[nodiscard]]
    u8 getNorma() const noexcept {
        PlayerComponent* playerComp = registry->getIf<PlayerComponent>(getEntityId());
        return playerComp ? playerComp->norma : 1;
    }

    /**
     * @brief Set the norma level of the player.
     *
     * @param norma The norma level to set.
     */
    void setNorma(u8 norma) noexcept {
        if (PlayerComponent* playerComp = registry->getIf<PlayerComponent>(getEntityId())) {
            playerComp->norma = norma;
        }
    }

    /**
     * @brief Add a card to the player's hand.
     *
     * @param card The card to add.
     */
    void addCard(const SharedPointer<Card>& card) {
        if (HandComponent* hand = registry->getIf<HandComponent>(getEntityId())) {
            hand->cards.push_back(card);
        }
    }

    /**
     * @brief Get all cards in the player's hand.
     *
     * @return Vector of cards in hand.
     */
    [[nodiscard]]
    Vector<SharedPointer<Card>> getCards() const {
        HandComponent* hand = registry->getIf<HandComponent>(getEntityId());
        return hand ? hand->cards : Vector<SharedPointer<Card>>();
    }

    /**
     * @brief Get the recovery value of the player's character.
     *
     * @return The recovery value, or 0 if no character is assigned or it's not a Playable.
     */
    [[nodiscard]]
    u8 getRecovery() const {
        SharedPointer<Unit> unit = getUnit();
        SharedPointer<Playable> character = std::mem::dynamic_pointer_cast<Playable>(unit);
        return character ? character->getRecovery() : 0;
    }

    /**
     * @brief Get the used mushrooms BitSet.
     *
     * @return BitSet representing used mushrooms.
     */
    [[nodiscard]]
    BitSet<MushroomCard::NUM_MUSHROOMS> getUsedMushrooms() const {
        MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId());
        return mushrooms ? mushrooms->usedMushrooms : BitSet<MushroomCard::NUM_MUSHROOMS>();
    }

    /**
     * @brief Get the used legendary mushrooms BitSet.
     * @return BitSet representing used legendary mushrooms.
     */
    [[nodiscard]]
    BitSet<MushroomCard::NUM_LEGENDARY_MUSHROOMS> getUsedLegendaryMushrooms() const {
        MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId());
        return mushrooms ? mushrooms->usedLegendaryMushrooms : BitSet<MushroomCard::NUM_LEGENDARY_MUSHROOMS>();
    }

    /**
     * @brief Check if a specific mushroom has been used.
     *
     * @param index The index of the mushroom to check.
     * @return True if the mushroom has been used, false otherwise.
     */
    [[nodiscard]]
    bool hasMushroom(usize index) const noexcept {
        MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId());
        if (mushrooms && index < MushroomCard::NUM_MUSHROOMS) { 
            #ifndef NDEBUG
            return mushrooms->usedMushrooms.test(index);
            #else
            return mushrooms->usedMushrooms[index];
            #endif
        } else {
            return false;
        }
    }

    /**
     * @brief Check if a specific legendary mushroom has been used.
     *
     * @param index The index of the legendary mushroom to check.
     * @return True if the legendary mushroom has been used, false otherwise.
     */
    [[nodiscard]]
    bool hasLegendaryMushroom(usize index) const noexcept {
        MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId());
        if (mushrooms && index < MushroomCard::NUM_LEGENDARY_MUSHROOMS) { 
            #ifndef NDEBUG
            return mushrooms->usedLegendaryMushrooms.test(index);
            #else
            return mushrooms->usedLegendaryMushrooms[index];
            #endif
        } else {
            return false;
        }
    }

    /**
     * @brief Use a mushroom at the specified index.
     *
     * @param index The index of the mushroom to use.
     */
    void useMushroom(usize index) noexcept {
        if (MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId()); mushrooms && index < MushroomCard::NUM_MUSHROOMS) {
            #ifndef NDEBUG
            mushrooms->usedMushrooms.set(index);
            #else
            mushrooms->usedMushrooms[index] = true;
            #endif
        }
    }

    /**
     * @brief Use a legendary mushroom at the specified index.
     *
     * @param index The index of the legendary mushroom to use.
     */
    void useLegendaryMushroom(usize index) noexcept {
        if (MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId()); mushrooms && index < MushroomCard::NUM_LEGENDARY_MUSHROOMS) {
            #ifndef NDEBUG
            mushrooms->usedLegendaryMushrooms.set(index);
            #else
            mushrooms->usedLegendaryMushrooms[index] = true;
            #endif
        }
    }

    /**
     * @brief Reset all mushrooms.
     */
    void resetMushrooms() noexcept {
        if (MushroomComponent* mushrooms = registry->getIf<MushroomComponent>(getEntityId())) {
            mushrooms->reset();
        }
    }
};

/**
 * @concept ExtendsPlayer
 * @brief Concept that checks if a type extends the Player class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsPlayer = IsBaseOfValue<Player, T>;

END_MODULE_NAMESPACE();
