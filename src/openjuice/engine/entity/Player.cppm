/**
 * @file Player.cppm
 * @module openjuice.engine.entity:Player
 * @brief Implementation of the Player class.
 *
 * This file contains the implementation of the Player class, which represents a player entity in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.entity:Player;

import :Combatant;

import stdx;

import openjuice.engine.card;
import openjuice.engine.unit;

using stdx::collections::BitSet;
using stdx::collections::Vector;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::Card;
using openjuice::engine::card::spawn::MushroomCard;
using openjuice::engine::unit::Playable;
using openjuice::engine::unit::Unit;

BEGIN_MODULE_NAMESPACE(openjuice::engine::entity);

/**
 * @class Player
 * @brief Class representing a player entity.
 * @extends Combatant
 *
 * The Player class extends the Combatant abstract class and represents a player entity with attributes such as wins, norma, and hand.
 */
export class Player: public Combatant {
private:
    Vector<SharedPointer<Card>> hand; ///< The cards currently held by the player.

    // Consists of (in this order):
    // Blue, Brown, Green, Orange, Pink, Purple, Rainbow, Red, White, Yellow
    BitSet<MushroomCard::NUM_MUSHROOMS> usedMushrooms; ///< The Mushrooms that have been used by the player.

    // Consists of (in this order):
    // Legendary Red, Phantom Blue
    BitSet<MushroomCard::NUM_LEGENDARY_MUSHROOMS> usedLegendaryMushrooms; ///< The Legendary Mushrooms that have been used by the player.

    u8 wins = 0; ///< The number of battles the player has won.
    u8 norma = 1; ///< The player's current norma level.
public:
    /**
     * @brief Constructor to initialize a Player object.
     * @param character The character associated with the player.
     */
    explicit Player(const SharedPointer<Playable>& character = nullptr) noexcept:
        Combatant(character) {}

    /**
     * @brief Get the number of wins the player has.
     * @return The number of wins.
     */
    [[nodiscard]]
    u8 getWins() const noexcept {
        return wins;
    }

    /**
     * @brief Set the number of wins the player has.
     * @param newWins The number of wins to set.
     */
    void setWins(u8 newWins) noexcept {
        wins = newWins;
    }

    /**
     * @brief Get the norma level of the player.
     * @return The norma level.
     */
    [[nodiscard]]
    u8 getNorma() const noexcept {
        return norma;
    }

    /**
     * @brief Set the norma level of the player.
     * @param newNorma The norma level to set.
     */
    void setNorma(u8 newNorma) noexcept {
        norma = newNorma;
    }

    /**
     * @brief Add a card to the player's hand.
     * @param card The card to add.
     */
    void addCard(const SharedPointer<Card>& card) {
        hand.push_back(card);
    }

    /**
     * @brief Get all cards in the player's hand.
     * @return The cards in hand.
     */
    [[nodiscard]]
    const Vector<SharedPointer<Card>>& getCards() const noexcept {
        return hand;
    }

    /**
     * @brief Get the recovery value of the player's character.
     * @return The recovery value, or 0 if no character is assigned or it's not a Playable.
     */
    [[nodiscard]]
    u8 getRecovery() const {
        SharedPointer<Playable> character = Pointers::dynamic_pointer_cast<Playable>(unit);
        return character ? character->getRecovery() : 0;
    }

    /**
     * @brief Get the used mushrooms BitSet.
     * @return BitSet representing used mushrooms.
     */
    [[nodiscard]]
    const BitSet<MushroomCard::NUM_MUSHROOMS>& getUsedMushrooms() const noexcept {
        return usedMushrooms;
    }

    /**
     * @brief Get the used legendary mushrooms BitSet.
     * @return BitSet representing used legendary mushrooms.
     */
    [[nodiscard]]
    const BitSet<MushroomCard::NUM_LEGENDARY_MUSHROOMS>& getUsedLegendaryMushrooms() const noexcept {
        return usedLegendaryMushrooms;
    }

    /**
     * @brief Check if a specific mushroom has been used.
     * @param index The index of the mushroom to check.
     * @return True if the mushroom has been used, false otherwise.
     */
    [[nodiscard]]
    bool hasMushroom(usize index) const noexcept {
        if (index >= MushroomCard::NUM_MUSHROOMS) {
            return false;
        }

        #ifndef NDEBUG
        return usedMushrooms.test(index);
        #else
        return usedMushrooms[index];
        #endif
    }

    /**
     * @brief Check if a specific legendary mushroom has been used.
     * @param index The index of the legendary mushroom to check.
     * @return True if the legendary mushroom has been used, false otherwise.
     */
    [[nodiscard]]
    bool hasLegendaryMushroom(usize index) const noexcept {
        if (index >= MushroomCard::NUM_LEGENDARY_MUSHROOMS) {
            return false;
        }

        #ifndef NDEBUG
        return usedLegendaryMushrooms.test(index);
        #else
        return usedLegendaryMushrooms[index];
        #endif
    }

    /**
     * @brief Use a mushroom at the specified index.
     * @param index The index of the mushroom to use.
     */
    void useMushroom(usize index) noexcept {
        if (index >= MushroomCard::NUM_MUSHROOMS) {
            return;
        }

        #ifndef NDEBUG
        usedMushrooms.set(index);
        #else
        usedMushrooms[index] = true;
        #endif
    }

    /**
     * @brief Use a legendary mushroom at the specified index.
     * @param index The index of the legendary mushroom to use.
     */
    void useLegendaryMushroom(usize index) noexcept {
        if (index >= MushroomCard::NUM_LEGENDARY_MUSHROOMS) {
            return;
        }

        #ifndef NDEBUG
        usedLegendaryMushrooms.set(index);
        #else
        usedLegendaryMushrooms[index] = true;
        #endif
    }

    /**
     * @brief Reset all mushrooms.
     */
    void resetMushrooms() noexcept {
        usedMushrooms.reset();
        usedLegendaryMushrooms.reset();
    }
};

END_MODULE_NAMESPACE();
