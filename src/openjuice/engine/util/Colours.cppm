/**
 * @file Colours.cppm
 * @module openjuice.engine.util.Colours
 * @brief Definition of the Colour struct and Colours namespace.
 *
 * This file contains the definition of the Colour struct and the Colours namespace, which provides predefined colours and ANSI colour codes.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Colours;

import std;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @struct Colour
 * @brief Struct representing a colour with red, green, and blue components.
 */
export struct Colour {
    u8 r; ///< Red component.
    u8 g; ///< Green component.
    u8 b; ///< Blue component.

    Colour() = default;

    constexpr Colour(u8 r, u8 g, u8 b):
        r{r}, g{g}, b{b} {}
};

/**
 * @namespace Colours
 * @brief Namespace for predefined colours and ANSI colour codes.
 */
export namespace Colours {
    constexpr Colour BLACK = Colour(0, 0, 0); ///< Black colour.
    constexpr Colour RED = Colour(255, 0, 0); ///< Red colour.
    constexpr Colour GREEN = Colour(0, 255, 0); ///< Green colour.
    constexpr Colour YELLOW = Colour(255, 255, 0); ///< Yellow colour.
    constexpr Colour BLUE = Colour(0, 0, 255); ///< Blue colour.
    constexpr Colour MAGENTA = Colour(255, 0, 255); ///< Magenta colour.
    constexpr Colour CYAN = Colour(0, 255, 255); ///< Cyan colour.
    constexpr Colour WHITE = Colour(255, 255, 255); ///< White colour.

    constexpr char RESET_ANSI[] = "\033[0m"; ///< ANSI code to reset colour.

    constexpr char BLACK_ANSI[] = "\033[30m"; ///< ANSI code for black colour.
    constexpr char RED_ANSI[] = "\033[31m"; ///< ANSI code for red colour.
    constexpr char GREEN_ANSI[] = "\033[32m"; ///< ANSI code for green colour.
    constexpr char YELLOW_ANSI[] = "\033[33m"; ///< ANSI code for yellow colour.
    constexpr char BLUE_ANSI[] = "\033[34m"; ///< ANSI code for blue colour.
    constexpr char MAGENTA_ANSI[] = "\033[35m"; ///< ANSI code for magenta colour.
    constexpr char CYAN_ANSI[] = "\033[36m"; ///< ANSI code for cyan colour.
    constexpr char WHITE_ANSI[] = "\033[37m"; ///< ANSI code for white colour.

    constexpr char BOLD_BLACK_ANSI[] = "\033[1m\033[30m"; ///< ANSI code for bold black colour.
    constexpr char BOLD_RED_ANSI[] = "\033[1m\033[31m"; ///< ANSI code for bold red colour.
    constexpr char BOLD_GREEN_ANSI[] = "\033[1m\033[32m"; ///< ANSI code for bold green colour.
    constexpr char BOLD_YELLOW_ANSI[] = "\033[1m\033[33m"; ///< ANSI code for bold yellow colour.
    constexpr char BOLD_BLUE_ANSI[] = "\033[1m\033[34m"; ///< ANSI code for bold blue colour.
    constexpr char BOLD_MAGENTA_ANSI[] = "\033[1m\033[35m"; ///< ANSI code for bold magenta colour.
    constexpr char BOLD_CYAN_ANSI[] = "\033[1m\033[36m"; ///< ANSI code for bold cyan colour.
    constexpr char BOLD_WHITE_ANSI[] = "\033[1m\033[37m"; ///< ANSI code for bold white colour.
}

END_MODULE_NAMESPACE();
