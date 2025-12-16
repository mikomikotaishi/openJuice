/**
 * @file RegistryError.cppm
 * @module openjuice.engine.game.ecs.Registry:RegistryError
 * @brief Module of the ECS entity manager.
 *
 * This file contains the errors for the ECS entity manager.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.game.ecs.Registry:RegistryError;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @enum RegistryError
 * @brief Enumeration for registry errors.
 * 
 * The DeckPointError enumeration defines the types of errors on ECS registry operations.
 */
export enum class RegistryError: u8 {
    ENTITY_CREATE_FAILURE ///< Failure to create an entity on the Registry
};

END_MODULE_NAMESPACE();

using openjuice::engine::game::ecs::RegistryError;

template <>
struct Formatter<RegistryError> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(RegistryError err, FormatContext& ctx) {
        StringView msg;
        switch (err) {
            case RegistryError::ENTITY_CREATE_FAILURE:
                msg = "Failed to create registry entity";
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", msg);
    }
};

SPECIALISE_FORMATTER(RegistryError);
