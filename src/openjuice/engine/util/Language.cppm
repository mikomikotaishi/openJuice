/**
 * @file Language.cppm
 * @module openjuice.engine.util:Language
 * @brief Definition of the Language enum class.
 *
 * This file contains the definition of the Language enum class, which represents supported languages.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.util:Language;

import stdx;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @enum Language 
 * @brief Enum class for supported languages.
 */
export enum class Language: u8 {
    ENGLISH, ///< English language.
    SPANISH, ///< Spanish language.
    FRENCH, ///< French language.
    PORTUGUESE_BR, ///< Brazilian Portuguese language.
    RUSSIAN, ///< Russian language.
    JAPANESE, ///< Japanese language.
    CHINESE_SIMPLIFIED, ///< Simplified Chinese language.
    CHINESE_TRADITIONAL, ///< Traditional Chinese language.
    KOREAN, ///< Korean language.
};

END_MODULE_NAMESPACE();

using openjuice::engine::util::Language;

template <>
struct Formatter<Language> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Language lang, FormatContext& ctx) {
        StringView name;
        switch (lang) {
            case Language::ENGLISH:
                name = "English";
                break;
            case Language::SPANISH:
                name = "Spanish";
                break;
            case Language::FRENCH:
                name = "French";
                break;
            case Language::PORTUGUESE_BR:
                name = "Brazilian Portuguese";
                break;
            case Language::RUSSIAN:
                name = "Russian";
                break;
            case Language::JAPANESE:
                name = "Japanese";
                break;
            case Language::CHINESE_SIMPLIFIED:
                name = "Simplified Chinese";
                break;
            case Language::CHINESE_TRADITIONAL:
                name = "Traditional Chinese";
                break;
            case Language::KOREAN:
                name = "Korean";
                break;
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(Language);
