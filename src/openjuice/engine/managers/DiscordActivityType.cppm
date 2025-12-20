/**
 * @file DiscordActivityType.cppm
 * @module openjuice.engine.managers.DiscordManager:DiscordActivityType
 * @brief Definition of the DiscordActivityType enum class.
 *
 * This file contains the definition of the DiscordActivityType enum class, which represents Discord activity status types.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.managers.DiscordManager:DiscordActivityType;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @enum DiscordActivityType
 * @brief Enumeration for discord activity types.
 * 
 * The DiscordActivityType enumeration defines the activity types that can be displayed in Discord.
 */
export enum class DiscordActivityType: u8 {
    IN_MENU, ///< Status is on menu
    IN_GAME, ///< Status is in game
    PAUSED ///< Status is paused
};

END_MODULE_NAMESPACE();

using openjuice::engine::managers::DiscordActivityType;

template <>
struct Formatter<DiscordActivityType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(DiscordActivityType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case DiscordActivityType::IN_MENU:
                name = "In Menu";
                break;
            case DiscordActivityType::IN_GAME:
                name = "In Game";
                break;
            case DiscordActivityType::PAUSED:
                name = "Paused";
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(DiscordActivityType);
