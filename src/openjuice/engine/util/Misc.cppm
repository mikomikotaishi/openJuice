/**
 * @file Misc.cppm
 * @module openjuice.engine.util:Misc
 * @brief Implementation of miscellaneous utility functions for the engine.
 *
 * This file contains the implementation of miscellaneous utility functions for the engine, such as hashing strings and getting terminal size.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:Misc;

import stdx;

using stdx::process::Command;
using stdx::process::ExitStatus;

#ifdef __unix__
using stdx::os::unix::sys::WindowSize;
#endif

using namespace stdx::os;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/** 
 * @brief Lambda to check if character is a format specifier
 */
constexpr auto isFormatSpecifier = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'X' || c == 'u'
        || c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'g' || c == 'G'
        || c == 'a' || c == 'A' || c == 'c' || c == 's' || c == 'p' || c == 'n';
};

/**
 * @brief Lambda to check if character is a format flag
 */
constexpr auto isFlag = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return c == '-' || c == '+' || c == '#' || c == '0' || c == ' ';
};

/**
 * @brief Lambda to check if character is width/precision related
 */
constexpr auto isWidthOrPrecision = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return (c >= '0' && c <= '9') || c == '*' || c == '.';
};

/**
 * @brief Lambda to check if character is a length modifier
 */
constexpr auto isLengthModifier = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return c == 'h' || c == 'l' || c == 'L' || c == 'z' || c == 'j' || c == 't';
};

/**
 * @brief Lambda to check if character is an integer specifier
 */
constexpr auto isIntegerSpecifier = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'X' || c == 'u';
};

/**
 * @brief Lambda to check if character is a float specifier
 */
constexpr auto isFloatSpecifier = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'g' || c == 'G' || c == 'a' || c == 'A';
};

/**
 * @brief Lambda to check if character is an 'other' specifier
 */
constexpr auto isOtherSpecifier = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return c == 'c' || c == 's' || c == 'p' || c == 'n';
};

/**
 * @brief Lambda to check if character is a format modifier
 */
constexpr auto isFormatModifier = [] [[nodiscard]] (char c) constexpr noexcept -> bool {
    return isFlag(c) || isWidthOrPrecision(c) || isLengthModifier(c);
};

export {
    /**
     * @brief Hash a string using a polynomial rolling hash function.
     * @param s The string to hash.
     * @return The hash value of the string.
     */
    [[nodiscard]]
    constexpr usize hashString(StringView s) noexcept {
        static constexpr i64 P = 131;
        static constexpr i64 M = 4294967291;
        i64 total = 0;
        i64 currentMultiplier = 1;
        for (char ch: s) {
            total = (total + currentMultiplier * static_cast<i64>(ch)) % M;
            currentMultiplier = (currentMultiplier * P) % M;
        }
        return static_cast<usize>(total);
    }

    /**
     * @brief Trims leading and trailing whitespace from a string.
     * @param str The string to trim.
     * @return The trimmed string.
     */
    [[nodiscard]]
    String trimString(StringView str) {
        const usize start = str.find_first_not_of(" \t\r\n");
        if (start == String::npos) {
            return "";
        }
        const usize end = str.find_last_not_of(" \t\r\n");
        return String(str.substr(start, end - start + 1));
    }

    /**
     * @brief Converts C-style format specifiers to C++ format specifiers.
     * @param format The format string with C-style specifiers (%d, %s, etc.).
     * @return A string with C++ style format specifiers ({}).
     */
    [[nodiscard]]
    String convertFormatSpecifier(StringView format) noexcept {
        String result;
        result.reserve(format.size());

        for (usize i = 0; i < format.size(); ++i) {
            if (format[i] == '%' && i + 1 < format.size()) {
                char next = format[i + 1];
                if (next == '%') {
                    result += '%';
                    ++i;
                    continue;
                }
                usize j = i + 1;
                while (j < format.size() && isFlag(format[j])) {
                    ++j;
                }
                if (j < format.size() && format[j] == '*') {
                    ++j;
                } else {
                    while (j < format.size() && format[j] >= '0' && format[j] <= '9') {
                        ++j;
                    }
                }
                if (j < format.size() && format[j] == '.') {
                    ++j;
                    if (j < format.size() && format[j] == '*') {
                        ++j;
                    } else {
                        while (j < format.size() && format[j] >= '0' && format[j] <= '9') {
                            ++j;
                        }
                    }
                }
                while (j < format.size() && isLengthModifier(format[j])) {
                    ++j;
                }
                if (j < format.size() && isFormatSpecifier(format[j])) {
                    result += "{}";
                    i = j;
                } else {
                    result += format[i];
                }
            } else {
                result += format[i];
            }
        }
        return result;
    }

    /**
     * @brief Converts C-style format specifiers to C++ format specifiers (constexpr version).
     * @param format The format string with C-style specifiers.
     * @return A string with C++ style format specifiers.
     * @note This is a simplified version that handles basic cases at compile-time.
     */
    template <usize N>
    [[nodiscard]]
    constexpr Array<char, N * 2> convertFormatSpecifier(const char (&fmt)[N]) noexcept {
        Array<char, N * 2> result;
        usize resultIndex = 0;
        for (usize i = 0; i < N - 1; ++i) {
            if (fmt[i] == '%' && i + 1 < N - 1) {
                char next = fmt[i + 1];
                if (next == '%') {
                    result[resultIndex++] = '%';
                    ++i;
                    continue;
                }
                bool foundSpecifier = false;
                for (usize j = i + 1; j < N - 1 && j < i + 10; ++j) {
                    char c = fmt[j];
                    if (isFormatSpecifier(c)) {
                        result[resultIndex++] = '{';
                        result[resultIndex++] = '}';
                        i = j;
                        foundSpecifier = true;
                        break;
                    }
                    if (!isFormatModifier(c)) {
                        break;
                    }
                }
                if (!foundSpecifier) {
                    result[resultIndex++] = fmt[i];
                }
            } else {
                result[resultIndex++] = fmt[i];
            }
        }
        result[resultIndex] = '\0';
        return result;
    }

    /**
     * @enum UrlError
     * @brief Errors representing possible errors in opening a URL.
     */
    enum class UrlOpenError: u8 {
        UNSUPPORTED_PLATFORM,
        SYSTEM_CALL_FAILED,
        INVALID_URL,
    };

    /**
     * @brief Opens a URL on the browser.
     * @param url The URL to open
     * @return Expected<void, UrlOpenError> 
     */
    [[nodiscard]]
    Expected<void, UrlOpenError> openUrl(StringView url) noexcept {
        if (url.empty()) {
            return Unexpected(UrlOpenError::INVALID_URL);
        }

        #if defined(_WIN32) || defined(_WIN64)
        StringView opener = "start";
        #elif defined(__linux__)
        StringView opener = "xdg-open";
        #elif defined(__APPLE__) || defined(__MACH__)
        StringView opener = "open";
        #else
        return Unexpected(UrlOpenError::UNSUPPORTED_PLATFORM);
        #endif

        Expected<ExitStatus, ErrorCode> result = Command::from(opener)
            .arg(url)
            .status();
        if (!result || !result->success()) {
            return Unexpected(UrlOpenError::SYSTEM_CALL_FAILED);
        }

        return {};
    }

    /**
     * @brief Get the size of the terminal.
     * @return A pair containing the number of rows and columns of the terminal, if check succeeds.
     */
    [[nodiscard]]
    Optional<Pair<i32, i32>> getTerminalSize() noexcept {
        i32 rows = 0;
        i32 cols = 0;
        #ifdef _WIN32
        ConsoleScreenBufferInfo cbsi;
        if (win32::GetConsoleScreenBufferInfo(win32::GetStdHandle(win32::STD_OUTPUT_HANDLE), &csbi)) {
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        } else {
            return nullopt;
        }
        #else
        WindowSize w;
        if (unix::sys::ioctl(unix::STDOUT_FILENO, unix::sys::TIOCGWINSZ, &w) == 0) {
            rows = w.ws_row;
            cols = w.ws_col;
        } else {
            return nullopt;
        }
        #endif
        return Pair<i32, i32>(rows, cols);
    }

}

END_MODULE_NAMESPACE();

export namespace openjuice::inline literals {
    /**
     * @brief User-defined literal for hashing strings at compile-time.
     * @param str The string to hash.
     * @param size The size of the string.
     * @return The hash value of the string.
     */
    [[nodiscard]]
    constexpr usize operator""_hash(const char* str, usize size) noexcept {
        return engine::util::hashString(StringView(str, size));
    }
}
