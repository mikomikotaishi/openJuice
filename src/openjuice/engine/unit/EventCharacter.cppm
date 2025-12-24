/**
 * @file EventCharacter.cppm
 * @module openjuice.engine.unit:EventCharacter
 * @brief Definition of the EventCharacter abstract class.
 *
 * This file contains the definition of the EventCharacter abstract class, which represents a main character unit in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.unit:EventCharacter;

import std;

import :Playable;

using std::meta::IsBaseOfValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::unit);

/**
 * @class EventCharacter
 * @brief Abstract class representing a character unit.
 * 
 * @extends Unit
 *
 * The EventCharacter abstract class extends the Playable abstract class and represents a main character unit with a specific recovery attribute.
 */
export class EventCharacter: public Playable {
public:
    /**
     * @brief Constructor to initialise a EventCharacter object.
     *
     * @param id The ID of the event character.
     * @param health The health of the event character.
     * @param attack The attack value of the event character.
     * @param defence The defence value of the event character.
     * @param evade The evade value of the event character.
     * @param recovery The recovery value of the event character.
     */
    EventCharacter(u16 id, u8 health, i8 attack, i8 defence, i8 evade, u8 recovery):
        Playable(id, health, attack, defence, evade, recovery) {}
};

/**
 * @concept ExtendsEventCharacter
 * @brief Concept that checks if a type extends the EventCharacter class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsEventCharacter = IsBaseOfValue<EventCharacter, T>;

END_MODULE_NAMESPACE();
