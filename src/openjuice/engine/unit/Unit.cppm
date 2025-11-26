/**
 * @file Unit.cppm
 * @module openjuice.engine.unit.Unit
 * @brief Definition of the Unit abstract class.
 *
 * This file contains the definition of the Unit abstract class, which represents a generic unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit.Unit;

import std;

import openjuice.engine.managers.TextManager;
import openjuice.engine.util.Interfaces;

using std::meta::IsBaseOfValue;

using openjuice::engine::managers::TextManager;
using openjuice::engine::managers::TextManagerError;
using openjuice::engine::util::interfaces::IFinalOnly;
using openjuice::engine::util::interfaces::IKeyQueryable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @class Unit
 * @brief Abstract class representing a generic unit.
 * 
 * The Unit abstract class represents a generic unit in the game with the following attributes: ID, health, attack, defence, and evade.
 *
 * @implements IFinalOnly
 * @implements IKeyQueryable
 */
export class Unit: public IFinalOnly, public IKeyQueryable {
private:
    const u16 id; ///< The ID of the unit.
    const u8 health; ///< The health of the unit.
    const i8 attack; ///< The attack value of the unit.
    const i8 defence; ///< The defence value of the unit.
    const i8 evade; ///< The evade value of the unit.
protected:
    static constexpr StringView UNIT_KEY = ""; ///< The key belonging to the card to query in TextManager
    static constexpr StringView ARTIST_KEY = ""; ///< The key belonging to the name of the artist to query in TextManager
    static constexpr StringView VOICEACTOR_KEY = ""; ///< The key belonging to the name of the voice actor to query in TextManager

    /**
     * @brief Constructor to initialise a Unit object.
     *
     * @param id The ID of the unit.
     * @param health The health of the unit.
     * @param attack The attack value of the unit.
     * @param defence The defence value of the unit.
     * @param evade The evade value of the unit.
     */
    Unit(u16 id, u8 health, i8 attack, i8 defence, i8 evade):
        id{id}, health{health}, attack{attack}, defence{defence}, evade{evade} {}

public:
    /**
     * @brief Get the ID of the unit.
     *
     * @return The ID of the unit.
     */
    [[nodiscard]]
    u16 getID() const noexcept {
        return id;
    }

    /**
     * @brief Get the health of the unit.
     *
     * @return The health of the unit.
     */
    [[nodiscard]]
    u8 getHealth() const noexcept {
        return health;
    }

    /**
     * @brief Get the attack value of the unit.
     *
     * @return The attack value of the unit.
     */
    [[nodiscard]]
    i8 getAttack() const noexcept {
        return attack;
    }

    /**
     * @brief Get the defence value of the unit.
     *
     * @return The defence value of the unit.
     */
    [[nodiscard]]
    i8 getDefence() const noexcept {
        return defence;
    }

    /**
     * @brief Get the evade value of the unit.
     *
     * @return The evade value of the unit.
     */
    [[nodiscard]]
    i8 getEvade() const noexcept {
        return evade;
    }

    /**
     * @brief Gets the name of the character.
     *
     * @return The name of the character.
     */
    [[nodiscard]]
    String getName() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getUnitName(UNIT_KEY);
        return String(result ? *result : "");
    }

    /**
     * @brief Get the description of the unit.
     *
     * @return The description of the unit.
     */
    [[nodiscard]]
    String getDescription() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getUnitDescription(UNIT_KEY);
        return String(result ? *result : "");
    }

    /**
     * @brief Get the unit artist name.
     *
     * @return The unit artist name.
     */
    [[nodiscard]]
    String getArtistName() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getCardArtistName(ARTIST_KEY);
        return String(result ? *result : "");
    }

    /**
     * @brief Get the unit voice actor name.
     *
     * @return The unit voice actor name.
     */
    [[nodiscard]]
    String getVoiceActorName() const {
        Expected<StringView, TextManagerError> result = TextManager::getInstance().getVoiceActorName(VOICEACTOR_KEY);
        return String(result ? *result : "");
    }
};

/**
 * @concept ExtendsUnit
 * @brief Concept that checks if a type extends the Unit class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsUnit = IsBaseOfValue<Unit, T>;

END_MODULE_NAMESPACE();
