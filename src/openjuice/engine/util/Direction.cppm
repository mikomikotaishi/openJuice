/**
 * @file Direction.cppm
 * @module openjuice.engine.util.Direction
 * @brief Definition of the Direction enum class.
 *
 * This file contains the definition of the Direction enum class, which represents cardinal directions.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.util.Direction;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

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
    DOWN = 3
};

END_MODULE_NAMESPACE();

using openjuice::engine::util::Direction;

template <>
struct Formatter<Direction> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Direction dir, FormatContext& ctx) {
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
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(Direction);
