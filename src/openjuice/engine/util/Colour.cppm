/**
 * @file Colour.cppm
 * @module openjuice.engine.util:Colour
 * @brief Definition of the Colour struct.
 *
 * This file contains the definition of the Colour struct, which provides predefined colours and ANSI colour codes.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:Colour;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @struct Colour
 * @brief Struct representing a colour with red, green, and blue components.
 */
export struct [[nodiscard]] Colour {
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

    static const Colour BLACK; ///< Predefined black colour.
    static const Colour RED; ///< Predefined red colour.
    static const Colour GREEN; ///< Predefined green colour.
    static const Colour YELLOW; ///< Predefined yellow colour.
    static const Colour BLUE; ///< Predefined blue colour.
    static const Colour MAGENTA; ///< Predefined magenta colour.
    static const Colour CYAN; ///< Predefined cyan colour.
    static const Colour WHITE; ///< Predefined white colour.

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

inline constexpr Colour Colour::BLACK = Colour(0, 0, 0);
inline constexpr Colour Colour::RED = Colour(255, 0, 0);
inline constexpr Colour Colour::GREEN = Colour(0, 255, 0);
inline constexpr Colour Colour::YELLOW = Colour(255, 255, 0);
inline constexpr Colour Colour::BLUE = Colour(0, 0, 255);
inline constexpr Colour Colour::MAGENTA = Colour(255, 0, 255);
inline constexpr Colour Colour::CYAN = Colour(0, 255, 255);
inline constexpr Colour Colour::WHITE = Colour(255, 255, 255);

END_MODULE_NAMESPACE();
