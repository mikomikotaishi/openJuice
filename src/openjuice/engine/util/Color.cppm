/**
 * @file Color.cppm
 * @module openjuice.engine.util:Color
 * @brief Definition of the Color struct.
 *
 * This file contains the definition of the Color struct, which provides predefined colors and ANSI color codes.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:Color;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @struct Color
 * @brief Struct representing a color with red, green, and blue components.
 */
export struct [[nodiscard]] Color {
    u8 r; ///< Red component.
    u8 g; ///< Green component.
    u8 b; ///< Blue component.

    static const Color BLACK; ///< Predefined black color.
    static const Color RED; ///< Predefined red color.
    static const Color GREEN; ///< Predefined green color.
    static const Color YELLOW; ///< Predefined yellow color.
    static const Color BLUE; ///< Predefined blue color.
    static const Color MAGENTA; ///< Predefined magenta color.
    static const Color CYAN; ///< Predefined cyan color.
    static const Color WHITE; ///< Predefined white color.

    static constexpr StringView RESET_ANSI = "\033[0m"; ///< ANSI code to reset color.

    static constexpr StringView BLACK_ANSI = "\033[30m"; ///< ANSI code for black color.
    static constexpr StringView RED_ANSI = "\033[31m"; ///< ANSI code for red color.
    static constexpr StringView GREEN_ANSI = "\033[32m"; ///< ANSI code for green color.
    static constexpr StringView YELLOW_ANSI = "\033[33m"; ///< ANSI code for yellow color.
    static constexpr StringView BLUE_ANSI = "\033[34m"; ///< ANSI code for blue color.
    static constexpr StringView MAGENTA_ANSI = "\033[35m"; ///< ANSI code for magenta color.
    static constexpr StringView CYAN_ANSI = "\033[36m"; ///< ANSI code for cyan color.
    static constexpr StringView WHITE_ANSI = "\033[37m"; ///< ANSI code for white color.

    static constexpr StringView BOLD_BLACK_ANSI = "\033[1m\033[30m"; ///< ANSI code for bold black color.
    static constexpr StringView BOLD_RED_ANSI = "\033[1m\033[31m"; ///< ANSI code for bold red color.
    static constexpr StringView BOLD_GREEN_ANSI = "\033[1m\033[32m"; ///< ANSI code for bold green color.
    static constexpr StringView BOLD_YELLOW_ANSI = "\033[1m\033[33m"; ///< ANSI code for bold yellow color.
    static constexpr StringView BOLD_BLUE_ANSI = "\033[1m\033[34m"; ///< ANSI code for bold blue color.
    static constexpr StringView BOLD_MAGENTA_ANSI = "\033[1m\033[35m"; ///< ANSI code for bold magenta color.
    static constexpr StringView BOLD_CYAN_ANSI = "\033[1m\033[36m"; ///< ANSI code for bold cyan color.
    static constexpr StringView BOLD_WHITE_ANSI = "\033[1m\033[37m"; ///< ANSI code for bold white color.
};

constexpr Color Color::BLACK = Color(0, 0, 0);
constexpr Color Color::RED = Color(255, 0, 0);
constexpr Color Color::GREEN = Color(0, 255, 0);
constexpr Color Color::YELLOW = Color(255, 255, 0);
constexpr Color Color::BLUE = Color(0, 0, 255);
constexpr Color Color::MAGENTA = Color(255, 0, 255);
constexpr Color Color::CYAN = Color(0, 255, 255);
constexpr Color Color::WHITE = Color(255, 255, 255);

END_MODULE_NAMESPACE();
