/**
 * @file Unit.cppm
 * @module openjuice.engine.unit:Unit
 * @brief Definition of the Unit abstract class.
 *
 * This file contains the definition of the Unit abstract class, which represents a generic unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit:Unit;

import stdx;

import openjuice.engine.services;

using openjuice::engine::services::LocalizationService;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @class Unit
 * @brief Class representing a generic unit.
 * 
 * The Unit class represents a generic unit in the game with the following attributes: ID, health, attack, defense, and evade.
 */
export class [[nodiscard]] Unit {
private:
    const u16 id; ///< The ID of the unit.
    const u8 health; ///< The health of the unit.
    const i8 attack; ///< The attack value of the unit.
    const i8 defense; ///< The defense value of the unit.
    const i8 evade; ///< The evade value of the unit.
protected:
    static constexpr StringView UNIT_KEY = ""; ///< The key belonging to the card to query in LocalizationService
    static constexpr StringView ARTIST_KEY = ""; ///< The key belonging to the name of the artist to query in LocalizationService
    static constexpr StringView VOICEACTOR_KEY = ""; ///< The key belonging to the name of the voice actor to query in LocalizationService

    /**
     * @brief Constructor to initialize a Unit object.
     *
     * @param id The ID of the unit.
     * @param health The health of the unit.
     * @param attack The attack value of the unit.
     * @param defense The defense value of the unit.
     * @param evade The evade value of the unit.
     */
    Unit(u16 id, u8 health, i8 attack, i8 defense, i8 evade):
        id{id}, health{health}, attack{attack}, defense{defense}, evade{evade} {}

    virtual ~Unit() = default;
public:
    /**
     * @brief Get the ID of the unit
     * @return The ID of the unit
     */
    [[nodiscard]]
    u16 getId() const noexcept {
        return id;
    }

    /**
     * @brief Get the health stat of the unit
     * @return The health stat
     */
    [[nodiscard]]
    u8 getHealth() const noexcept {
        return health;
    }

    /**
     * @brief Get the attack stat of the unit
     * @return The attack stat
     */
    [[nodiscard]]
    i8 getAttack() const noexcept {
        return attack;
    }

    /**
     * @brief Get the defense stat of the unit
     * @return The defense stat
     */
    [[nodiscard]]
    i8 getDefense() const noexcept {
        return defense;
    }

    /**
     * @brief Get the evade stat of the unit
     * @return The evade stat
     */
    [[nodiscard]]
    i8 getEvade() const noexcept {
        return evade;
    }

    /**
     * @brief Gets the name of the character.
     * @return The name of the character.
     */
    [[nodiscard]]
    String getName(const LocalizationService& loc) const noexcept {
        return loc
            .getUnitName(UNIT_KEY)
            .value_or("");
    }

    /**
     * @brief Get the description of the unit.
     * @return The description of the unit.
     */
    [[nodiscard]]
    String getDescription(const LocalizationService& loc) const noexcept {
        return loc
            .getUnitDescription(UNIT_KEY)
            .value_or("");
    }

    /**
     * @brief Get the unit artist name.
     * @return The unit artist name.
     */
    [[nodiscard]]
    String getArtistName(const LocalizationService& loc) const noexcept {
        return loc
            .getCardArtistName(ARTIST_KEY)
            .value_or("");
    }

    /**
     * @brief Get the unit voice actor name.
     * @return The unit voice actor name.
     */
    [[nodiscard]]
    String getVoiceActorName(const LocalizationService& loc) const noexcept {
        return loc
            .getVoiceActorName(VOICEACTOR_KEY)
            .value_or("");
    }
};

END_MODULE_NAMESPACE();
