/**
 * @file regex.cppm
 * @module boost.regex
 * @brief Module file for Boost library Regex operations.
 * @version 1.88.0
 */

module;

export module boost.regex;

import :detail;

/**
 * @namespace boost::regex
 * @brief The Boost boost:: namespace
 */
export namespace boost::regex {
    using _detail::boost::regex::CRegexTraits;
    using _detail::boost::regex::CppRegexTraits;
    using _detail::boost::regex::Win32RegexTraits;
    using _detail::boost::regex::RegexTraits;
    using _detail::boost::regex::BasicRegex;
    using _detail::boost::regex::Regex;
    using _detail::boost::regex::SubMatch;
    using _detail::boost::regex::MatchResults;
    using _detail::boost::regex::RegexIterator;
    using _detail::boost::regex::RegexTokenIterator;
    using _detail::boost::regex::RegexException;
    using _detail::boost::regex::BadPatternException;
    using _detail::boost::regex::BadExpressionException;

    using _detail::boost::regex::regex_match;
    using _detail::boost::regex::regex_search;
    using _detail::boost::regex::regex_replace;

    namespace regex_constants {
        using _detail::boost::regex::regex_constants::SyntaxOptionType;

        using _detail::boost::regex::regex_constants::NORMAL;
        using _detail::boost::regex::regex_constants::ECMASCRIPT;
        using _detail::boost::regex::regex_constants::JAVASCRIPT;
        using _detail::boost::regex::regex_constants::JSCRIPT;
        using _detail::boost::regex::regex_constants::PERL;
        using _detail::boost::regex::regex_constants::SED;
        using _detail::boost::regex::regex_constants::EXTENDED;
        using _detail::boost::regex::regex_constants::AWK;
        using _detail::boost::regex::regex_constants::GREP;
        using _detail::boost::regex::regex_constants::EGREP;
        using _detail::boost::regex::regex_constants::ICASE;
        using _detail::boost::regex::regex_constants::NOSUBS;
        using _detail::boost::regex::regex_constants::OPTIMIZE;
        using _detail::boost::regex::regex_constants::COLLATE;
        using _detail::boost::regex::regex_constants::NEWLINE_ALT;
        using _detail::boost::regex::regex_constants::NO_EXCEPT;
        using _detail::boost::regex::regex_constants::SAVE_SUBEXPRESSION_LOCATION;
        using _detail::boost::regex::regex_constants::NO_MOD_M;
        using _detail::boost::regex::regex_constants::NO_MOD_S;
        using _detail::boost::regex::regex_constants::MOD_S;
        using _detail::boost::regex::regex_constants::MOD_X;
        using _detail::boost::regex::regex_constants::NO_EMPTY_EXPRESSIONS;
        using _detail::boost::regex::regex_constants::NO_ESCAPE_IN_LISTS;
        using _detail::boost::regex::regex_constants::NO_BK_REFS;
        using _detail::boost::regex::regex_constants::NO_CHAR_CLASSES;
        using _detail::boost::regex::regex_constants::NO_INTERVALS;
        using _detail::boost::regex::regex_constants::BK_PLUS_QM;
        using _detail::boost::regex::regex_constants::BK_VBAR;

        using _detail::boost::regex::regex_constants::MatchFlagType;
        
        using _detail::boost::regex::regex_constants::MATCH_DEFAULT;
        using _detail::boost::regex::regex_constants::MATCH_NOT_BOB;
        using _detail::boost::regex::regex_constants::MATCH_NOT_EOB;
        using _detail::boost::regex::regex_constants::MATCH_NOT_BOL;
        using _detail::boost::regex::regex_constants::MATCH_NOT_EOL;
        using _detail::boost::regex::regex_constants::MATCH_NOT_BOW;
        using _detail::boost::regex::regex_constants::MATCH_NOT_EOW;
        using _detail::boost::regex::regex_constants::MATCH_ANY;
        using _detail::boost::regex::regex_constants::MATCH_NOT_NULL;
        using _detail::boost::regex::regex_constants::MATCH_CONTINUOUS;
        using _detail::boost::regex::regex_constants::MATCH_PARTIAL;
        using _detail::boost::regex::regex_constants::MATCH_SINGLE_LINE;
        using _detail::boost::regex::regex_constants::MATCH_PREV_AVAIL;
        using _detail::boost::regex::regex_constants::MATCH_NOT_DOT_NEWLINE;
        using _detail::boost::regex::regex_constants::MATCH_NOT_DOT_NULL;
        using _detail::boost::regex::regex_constants::MATCH_POSIX;
        using _detail::boost::regex::regex_constants::MATCH_PERL;
        using _detail::boost::regex::regex_constants::MATCH_NOSUBS;
        using _detail::boost::regex::regex_constants::MATCH_EXTRA;

        using _detail::boost::regex::regex_constants::FORMAT_DEFAULT;
        using _detail::boost::regex::regex_constants::FORMAT_SED;
        using _detail::boost::regex::regex_constants::FORMAT_PERL;
        using _detail::boost::regex::regex_constants::FORMAT_LITERAL;
        using _detail::boost::regex::regex_constants::FORMAT_NO_COPY;
        using _detail::boost::regex::regex_constants::FORMAT_FIRST_ONLY;
        using _detail::boost::regex::regex_constants::FORMAT_ALL;

        using _detail::boost::regex::regex_constants::ErrorType;

        using _detail::boost::regex::regex_constants::ERROR_COLLATE;
        using _detail::boost::regex::regex_constants::ERROR_CTYPE;
        using _detail::boost::regex::regex_constants::ERROR_ESCAPE;
        using _detail::boost::regex::regex_constants::ERROR_BACKREF;
        using _detail::boost::regex::regex_constants::ERROR_BRACK;
        using _detail::boost::regex::regex_constants::ERROR_PAREN;
        using _detail::boost::regex::regex_constants::ERROR_BRACE;
        using _detail::boost::regex::regex_constants::ERROR_BADBRACE;
        using _detail::boost::regex::regex_constants::ERROR_RANGE;
        using _detail::boost::regex::regex_constants::ERROR_SPACE;
        using _detail::boost::regex::regex_constants::ERROR_BADREPEAT;
        using _detail::boost::regex::regex_constants::ERROR_COMPLEXITY;
        using _detail::boost::regex::regex_constants::ERROR_STACK;
        using _detail::boost::regex::regex_constants::ERROR_BAD_PATTERN;
    }
}
