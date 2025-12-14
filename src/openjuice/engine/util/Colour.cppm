/**
 * @file Colour.cppm
 * @module openjuice.engine.util.Colour
 * @brief Definition of the Colour struct.
 *
 * This file contains the definition of the Colour struct, which provides predefined colours and ANSI colour codes.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Colour;

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

    /**
     * @brief Constructs an instance of Colour.
     * 
     * @param r Red value
     * @param g Green value
     * @param b Blue value
     * 
     * @return The constructed colour
     */
    constexpr Colour(u8 r, u8 g, u8 b):
        r{r}, g{g}, b{b} {}

    /**
     * @brief Returns a black colour (0, 0, 0).
     * 
     * @return Black colour.
     */
    static constexpr Colour black() {
        return Colour(0, 0, 0);
    }

    /**
     * @brief Returns a red colour (255, 0, 0).
     * 
     * @return Red colour.
     */
    static constexpr Colour red() {
        return Colour(255, 0, 0);
    }

    /**
     * @brief Returns a green colour (0, 255, 0).
     * 
     * @return Green colour.
     */
    static constexpr Colour green() {
        return Colour(0, 255, 0);
    }

    /**
     * @brief Returns a yellow colour (255, 255, 0).
     * 
     * @return Yellow colour.
     */
    static constexpr Colour yellow() {
        return Colour(255, 255, 0);
    }

    /**
     * @brief Returns a blue colour (0, 0, 255).
     * 
     * @return Blue colour.
     */
    static constexpr Colour blue() {
        return Colour(0, 0, 255);
    }

    /**
     * @brief Returns a magenta colour (255, 0, 255).
     * 
     * @return Magenta colour.
     */
    static constexpr Colour magenta() {
        return Colour(255, 0, 255);
    }

    /**
     * @brief Returns a cyan colour (0, 255, 255).
     * 
     * @return Cyan colour.
     */
    static constexpr Colour cyan() {
        return Colour(0, 255, 255);
    }

    /**
     * @brief Returns a white colour (255, 255, 255).
     * 
     * @return White colour.
     */
    static constexpr Colour white() {
        return Colour(255, 255, 255);
    }

    static constexpr StringView RESET_ANSI = "\033[0m"; ///< ANSI code to reset colour.

    static constexpr StringView BLACK_ANSI = "\033[30m"; ///< ANSI code for black colour.
    static constexpr StringView RED_ANSI = "\033[31m"; ///< ANSI code for red colour.
    static constexpr StringView GREEN_ANSI = "\033[32m"; ///< ANSI code for green colour.
    static constexpr StringView YELLOW_ANSI = "\033[33m"; ///< ANSI code for yellow colour.
    static constexpr StringView BLUE_ANSI = "\033[34m"; ///< ANSI code for blue colour.
    static constexpr StringView MAGENTA_ANSI = "\033[35m"; ///< ANSI code for magenta colour.
    static constexpr StringView CYAN_ANSI = "\033[36m"; ///< ANSI code for cyan colour.
    static constexpr StringView WHITE_ANSI = "\033[37m"; ///< ANSI code for white colour.

    static constexpr StringView BOLD_BLACK_ANSI = "\033[1m\033[30m"; ///< ANSI code for bold black colour.
    static constexpr StringView BOLD_RED_ANSI = "\033[1m\033[31m"; ///< ANSI code for bold red colour.
    static constexpr StringView BOLD_GREEN_ANSI = "\033[1m\033[32m"; ///< ANSI code for bold green colour.
    static constexpr StringView BOLD_YELLOW_ANSI = "\033[1m\033[33m"; ///< ANSI code for bold yellow colour.
    static constexpr StringView BOLD_BLUE_ANSI = "\033[1m\033[34m"; ///< ANSI code for bold blue colour.
    static constexpr StringView BOLD_MAGENTA_ANSI = "\033[1m\033[35m"; ///< ANSI code for bold magenta colour.
    static constexpr StringView BOLD_CYAN_ANSI = "\033[1m\033[36m"; ///< ANSI code for bold cyan colour.
    static constexpr StringView BOLD_WHITE_ANSI = "\033[1m\033[37m"; ///< ANSI code for bold white colour.
};

END_MODULE_NAMESPACE();
