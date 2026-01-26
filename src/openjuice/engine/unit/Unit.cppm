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

import std;

import openjuice.engine.managers;
import openjuice.engine.util;

using std::meta::IsBaseOfValue;

using openjuice::engine::managers::TextManager;
using openjuice::engine::util::IFinalOnly;
using openjuice::engine::util::IKeyQueryable;

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
export class [[nodiscard]] Unit: public IFinalOnly, public IKeyQueryable {
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
    GETTER(u16, Id, id);
    GETTER(u8, Health, health);
    GETTER(i8, Attack, attack);
    GETTER(i8, Defence, defence);
    GETTER(i8, Evade, evade);

    /**
     * @brief Gets the name of the character.
     *
     * @return The name of the character.
     */
    [[nodiscard]]
    String getName() const noexcept {
        return TextManager::getInstance()
            .getUnitName(UNIT_KEY)
            .value_or("");
    }

    /**
     * @brief Get the description of the unit.
     *
     * @return The description of the unit.
     */
    [[nodiscard]]
    String getDescription() const noexcept {
        return TextManager::getInstance()
            .getUnitDescription(UNIT_KEY)
            .value_or("");
    }

    /**
     * @brief Get the unit artist name.
     *
     * @return The unit artist name.
     */
    [[nodiscard]]
    String getArtistName() const noexcept {
        return TextManager::getInstance()
            .getCardArtistName(ARTIST_KEY)
            .value_or("");
    }

    /**
     * @brief Get the unit voice actor name.
     *
     * @return The unit voice actor name.
     */
    [[nodiscard]]
    String getVoiceActorName() const noexcept {
        return TextManager::getInstance()
            .getVoiceActorName(VOICEACTOR_KEY)
            .value_or("");
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
