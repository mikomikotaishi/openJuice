/**
 * @file Language.cppm
 * @module openjuice.engine.localization.Language
 * @brief Definition of the Language enum class.
 *
 * This file contains the definition of the Language enum class, which represents supported languages.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.localization.Language;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::engine::localization);

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

using openjuice::engine::localization::Language;

namespace stdx::fmt {
    template <>
    struct Formatter<Language> {
        enum class Mode: u8 {
            SHORT,
            FULL,
            DEBUG,
        };

        Mode mode = Mode::FULL;

        THROWS(FormatException)
        constexpr FormatParseContext::iterator parse(FormatParseContext& ctx) {
            auto it = ctx.begin();
            auto end = ctx.end();

            if (it != end && (*it == 's' || *it == 'f' || *it == '?')) {
                switch (*it) {
                    case 's':
                        mode = Mode::SHORT;
                        break;
                    case 'f':
                        mode = Mode::FULL;
                        break;
                    case '?':
                        mode = Mode::DEBUG;
                        break;
                }
                ++it;
            }

            if (it != end && *it != '}') {
                throw FormatException("Invalid specifier"); 
            }
            return it;
        }

        FormatContext::iterator format(Language lang, FormatContext& ctx) const {
            StringView name;
            bool useShortName = (mode == Mode::SHORT);
            switch (lang) {
                case Language::ENGLISH:
                    name = useShortName ? "en" : "English";
                    break;
                case Language::SPANISH:
                    name = useShortName ? "sp" : "Spanish";
                    break;
                case Language::FRENCH:
                    name = useShortName ? "fr" : "French";
                    break;
                case Language::PORTUGUESE_BR:
                    name = useShortName ? "ptbr" : "Brazilian Portuguese";
                    break;
                case Language::RUSSIAN:
                    name = useShortName ? "ru" : "Russian";
                    break;
                case Language::JAPANESE:
                    name = useShortName ? "jp" : "Japanese";
                    break;
                case Language::CHINESE_SIMPLIFIED:
                    name = useShortName ? "chs" : "Simplified Chinese";
                    break;
                case Language::CHINESE_TRADITIONAL:
                    name = useShortName ? "cht" : "Traditional Chinese";
                    break;
                case Language::KOREAN:
                    name = useShortName ? "ko" : "Korean";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(Language);
