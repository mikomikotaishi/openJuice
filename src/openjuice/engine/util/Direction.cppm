/**
 * @file Direction.cppm
 * @module openjuice.engine.util:Direction
 * @brief Definition of the Direction enum class.
 *
 * This file contains the definition of the Direction enum class, which represents cardinal directions.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:Direction;

import stdx;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @enum Direction
 * @brief Enumeration for directions.
 *
 * The Direction enumeration defines the four cardinal directions.
 */
export enum class Direction: u8 {
    UP = 0,
    LEFT = 1,
    RIGHT = 2,
    DOWN = 3,
};

END_MODULE_NAMESPACE();

using openjuice::engine::util::Direction;

template <>
struct Formatter<Direction> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(Direction dir, FormatContext& ctx) {
        StringView name;
        switch (dir) {
            case Direction::UP:
                name = "Up";
                break;
            case Direction::LEFT:
                name = "Left";
                break;
            case Direction::RIGHT:
                name = "Right";
                break;
            case Direction::DOWN:
                name = "Down";
                break;
            default:
                Ops::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(Direction);
