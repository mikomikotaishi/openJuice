/**
 * @file CharacterSpecificCardFactory.cppm
 * @module openjuice.card:CharacterSpecificCardFactory
 * @brief Implementation of the CharacterSpecificCardFactory class.
 *
 * This file contains the implementation of the CharacterSpecificCardFactory class, which is used to create CharacterSpecificCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:CharacterSpecificCardFactory;

import stdx;

import :character;

import openjuice.engine.card;
import openjuice.engine.services;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::spawn::CharacterSpecificCard;

using namespace openjuice::card::character;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class CharacterSpecificCardFactory
 * @brief Factory class for creating CharacterSpecificCard objects.
 *
 * The CharacterSpecificCardFactory class is a singleton factory class that creates CharacterSpecificCard objects based on the given ID.
 */
export class CharacterSpecificCardFactory final {
public:
    CharacterSpecificCardFactory() = delete("CharacterSpecificCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a CharacterSpecificCard object with the given ID.
     *
     * @param id ID of the CharacterSpecificCard to create
     * @return Shared pointer to the created CharacterSpecificCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<CharacterSpecificCard>> create(u8 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            case MiosChristmasCake::ID:
                return Pointers::shared<MiosChristmasCake>();
            case Freight::ID:
                return Pointers::shared<Freight>();
            case RedAndBlue::ID:
                return Pointers::shared<RedAndBlue>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
