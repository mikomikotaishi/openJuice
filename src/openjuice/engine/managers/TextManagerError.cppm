/**
 * @file TextManagerError.cppm
 * @module openjuice.engine.managers:TextManagerError
 * @brief Definition of the TextManagerError enum class.
 *
 * This file contains the definition of the TextManagerError enum class, which possible errors during text manager loading.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.managers:TextManagerError;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @enum TextManagerError
 * @brief Enumeration of errors occuring in TextManager operations
 */
export enum class TextManagerError: u8 {
    EMPTY_KEY, ///< The key was empty
    INVALID_KEY, ///< The key did not map anywhere
    FILE_NOT_FOUND, ///< No such file was found
    FILE_OPEN_FAILURE, ///< The file could not be opened
    FILE_READ_FAILURE, ///< The file failed to parse
};

END_MODULE_NAMESPACE();

using openjuice::engine::managers::TextManagerError;

template <>
struct Formatter<TextManagerError> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(TextManagerError err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case TextManagerError::EMPTY_KEY:
                name = "Empty key"; 
                break;
            case TextManagerError::INVALID_KEY:
                name = "Invalid key"; 
                break;
            case TextManagerError::FILE_NOT_FOUND:
                name = "File not found"; 
                break;
            case TextManagerError::FILE_OPEN_FAILURE:
                name = "File open failure"; 
                break;
            case TextManagerError::FILE_READ_FAILURE:
                name = "File read failure"; 
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(TextManagerError);
