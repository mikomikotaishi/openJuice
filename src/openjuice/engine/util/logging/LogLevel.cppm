/**
 * @file LogLevel.cppm
 * @module openjuice.engine.util.Logging:LogLevel
 * @brief Definition of the LogLevel enum class.
 *
 * This file contains the definition of the LogLevel enum class, which represents logging message level.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.util.Logging:LogLevel;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util::logging);

/**
 * @enum LogLevel
 * @brief Enumeration for log message levels.
 * 
 * The LogLevel enumeration defines the logger message level.
 */
export enum class LogLevel: u8 {
    INFO, ///< An info message type
    WARNING, ///< A warning message type
    ERROR, ///< An error message type
    DEBUG ///< A debug message type
};

END_MODULE_NAMESPACE();

using openjuice::engine::util::logging::LogLevel;

template <>
struct Formatter<LogLevel> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(LogLevel lvl, FormatContext& ctx) {
        StringView name;
        switch (lvl) {
            case LogLevel::INFO:
                name = "[INFO]:";
                break;
            case LogLevel::WARNING:
                name = "[WARNING]:";
                break;
            case LogLevel::ERROR:
                name = "[ERROR]:";
                break;
            case LogLevel::DEBUG:
                name = "[DEBUG]:";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{:11}", name);
    }
};

SPECIALISE_FORMATTER(LogLevel);
