/**
 * @file BoardLibraryError.cppm
 * @module openjuice.engine.board.BoardLibrary:BoardLibraryError
 * @brief Definition of the BoardLibraryError enum class.
 *
 * This file contains the definition of the BoardLibraryError enum class, which possible errors during board library loading.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.board.BoardLibrary:BoardLibraryError;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

namespace fmt = std::fmt;
namespace sys = std::sys;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @enum BoardLibraryError
 * @brief Enumeration of errors occuring in BoardLibrary operations
 */
export enum class BoardLibraryError: u8 {
    DIRECTORY_NOT_FOUND, ///< The directory containing boards was not found
    INVALID_TOML_ARRAY, ///< A TOML array was not valid or contained invalid data
    INVALID_TOML_ARRAY_SIZE, ///< A TOML array had an invalid size
    CORRUPTED_LIBRARY_TOML ///< The TOML file storing the board library is corrupted or has invalid data
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::BoardLibraryError;

template <>
struct Formatter<BoardLibraryError> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(BoardLibraryError err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case BoardLibraryError::DIRECTORY_NOT_FOUND:
                name = "Directory not found"; 
                break;
            case BoardLibraryError::INVALID_TOML_ARRAY:
                name = "Invalid TOML array"; 
                break;
            case BoardLibraryError::INVALID_TOML_ARRAY_SIZE:
                name = "Invalid TOML array size"; 
                break;
            case BoardLibraryError::CORRUPTED_LIBRARY_TOML:
                name = "Corrupted library TOML";
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BoardLibraryError);
