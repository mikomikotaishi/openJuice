/**
 * @file regex.cppm
 * @module boost.regex:detail
 * @brief Module file for Boost library Regex operations.
 * @version 1.88.0
 */

module;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#include <boost/regex.hpp>

#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

export module boost.regex:detail;

/**
 * @internal
 * @namespace _detail::boost::regex
 * @brief The Boost boost:: namespace
 * Detail namespace - not to be exported for external use
 */
export namespace _detail::boost::regex {
    template <class CharT>
    using CRegexTraits = ::boost::c_regex_traits<CharT>;

    template <class CharT>
    using CppRegexTraits = ::boost::cpp_regex_traits<CharT>;

    template <class CharT>
    using Win32RegexTraits = ::boost::w32_regex_traits<CharT>;

    template <class CharT, class ImplementationT = CppRegexTraits<class charT>>
    using RegexTraits = ::boost::regex_traits<CharT, ImplementationT>;

    template <class CharT, class Traits = RegexTraits<CharT>>
    using BasicRegex = ::boost::basic_regex<CharT, Traits>;

    using Regex = ::boost::regex;

    template <class BidirectionalIterator>
    using SubMatch = ::boost::sub_match<BidirectionalIterator>;

    template <class BidirectionalIterator, class Allocator = std::allocator<SubMatch<BidirectionalIterator>>>
    using MatchResults = ::boost::match_results<BidirectionalIterator, Allocator>;

    template <class BidirectionalIterator, class CharT = std::iterator_traits<BidirectionalIterator>::value_type, class Traits = RegexTraits<CharT>>
    using RegexIterator = ::boost::regex_iterator<BidirectionalIterator, CharT, Traits>;

    template <class BidirectionalIterator, class CharT = std::iterator_traits<BidirectionalIterator>::value_type, class Traits = RegexTraits<CharT>>
    using RegexTokenIterator = ::boost::regex_token_iterator<BidirectionalIterator, CharT, Traits>;

    using RegexException = ::boost::bad_expression;
    using BadPatternException = ::boost::bad_pattern;
    using BadExpressionException = ::boost::bad_expression;

    using ::boost::regex_match;
    using ::boost::regex_search;
    using ::boost::regex_replace;

    namespace regex_constants {
        using SyntaxOptionType = ::boost::regex_constants::syntax_option_type;

        inline constexpr SyntaxOptionType NORMAL = ::boost::regex_constants::normal;
        inline constexpr SyntaxOptionType ECMASCRIPT = ::boost::regex_constants::ECMAScript;
        inline constexpr SyntaxOptionType JAVASCRIPT = ::boost::regex_constants::JavaScript;
        inline constexpr SyntaxOptionType JSCRIPT = ::boost::regex_constants::JScript;
        inline constexpr SyntaxOptionType PERL = ::boost::regex_constants::perl;
        inline constexpr SyntaxOptionType SED = ::boost::regex_constants::sed;
        inline constexpr SyntaxOptionType EXTENDED = ::boost::regex_constants::extended;
        inline constexpr SyntaxOptionType AWK = ::boost::regex_constants::awk;
        inline constexpr SyntaxOptionType GREP = ::boost::regex_constants::grep;
        inline constexpr SyntaxOptionType EGREP = ::boost::regex_constants::egrep;
        inline constexpr SyntaxOptionType ICASE = ::boost::regex_constants::icase;
        inline constexpr SyntaxOptionType NOSUBS = ::boost::regex_constants::nosubs;
        inline constexpr SyntaxOptionType OPTIMIZE = ::boost::regex_constants::optimize;
        inline constexpr SyntaxOptionType COLLATE = ::boost::regex_constants::collate;
        inline constexpr SyntaxOptionType NEWLINE_ALT = ::boost::regbase::newline_alt;
        inline constexpr SyntaxOptionType NO_EXCEPT = ::boost::regex_constants::no_except;
        inline constexpr SyntaxOptionType SAVE_SUBEXPRESSION_LOCATION = ::boost::regex_constants::save_subexpression_location;
        inline constexpr SyntaxOptionType NO_MOD_M = ::boost::regex_constants::no_mod_m;
        inline constexpr SyntaxOptionType NO_MOD_S = ::boost::regex_constants::no_mod_s;
        inline constexpr SyntaxOptionType MOD_S = ::boost::regex_constants::mod_s;
        inline constexpr SyntaxOptionType MOD_X = ::boost::regex_constants::mod_x;
        inline constexpr SyntaxOptionType NO_EMPTY_EXPRESSIONS = ::boost::regex_constants::no_empty_expressions;
        inline constexpr SyntaxOptionType NO_ESCAPE_IN_LISTS = ::boost::regex_constants::no_escape_in_lists;
        inline constexpr SyntaxOptionType NO_BK_REFS = ::boost::regbase::no_bk_refs;
        inline constexpr SyntaxOptionType NO_CHAR_CLASSES = ::boost::regex_constants::no_char_classes;
        inline constexpr SyntaxOptionType NO_INTERVALS = ::boost::regex_constants::no_intervals;
        inline constexpr SyntaxOptionType BK_PLUS_QM = ::boost::regex_constants::bk_plus_qm;
        inline constexpr SyntaxOptionType BK_VBAR = ::boost::regex_constants::bk_vbar;

        using MatchFlagType = ::boost::regex_constants::match_flag_type;

        inline constexpr MatchFlagType MATCH_DEFAULT = ::boost::regex_constants::match_default;
        inline constexpr MatchFlagType MATCH_NOT_BOB = ::boost::regex_constants::match_not_bob;
        inline constexpr MatchFlagType MATCH_NOT_EOB = ::boost::regex_constants::match_not_eob;
        inline constexpr MatchFlagType MATCH_NOT_BOL = ::boost::regex_constants::match_not_bol;
        inline constexpr MatchFlagType MATCH_NOT_EOL = ::boost::regex_constants::match_not_eol;
        inline constexpr MatchFlagType MATCH_NOT_BOW = ::boost::regex_constants::match_not_bow;
        inline constexpr MatchFlagType MATCH_NOT_EOW = ::boost::regex_constants::match_not_eow;
        inline constexpr MatchFlagType MATCH_ANY = ::boost::regex_constants::match_any;
        inline constexpr MatchFlagType MATCH_NOT_NULL = ::boost::regex_constants::match_not_null;
        inline constexpr MatchFlagType MATCH_CONTINUOUS = ::boost::regex_constants::match_continuous;
        inline constexpr MatchFlagType MATCH_PARTIAL = ::boost::regex_constants::match_partial;
        inline constexpr MatchFlagType MATCH_SINGLE_LINE = ::boost::regex_constants::match_single_line;
        inline constexpr MatchFlagType MATCH_PREV_AVAIL = ::boost::regex_constants::match_prev_avail;
        inline constexpr MatchFlagType MATCH_NOT_DOT_NEWLINE = ::boost::regex_constants::match_not_dot_newline;
        inline constexpr MatchFlagType MATCH_NOT_DOT_NULL = ::boost::regex_constants::match_not_dot_null;
        inline constexpr MatchFlagType MATCH_POSIX = ::boost::regex_constants::match_posix;
        inline constexpr MatchFlagType MATCH_PERL =  ::boost::regex_constants::match_perl;
        inline constexpr MatchFlagType MATCH_NOSUBS = ::boost::regex_constants::match_nosubs;
        inline constexpr MatchFlagType MATCH_EXTRA = ::boost::regex_constants::match_extra;

        inline constexpr MatchFlagType FORMAT_DEFAULT = ::boost::regex_constants::format_default;
        inline constexpr MatchFlagType FORMAT_SED = ::boost::regex_constants::format_sed;
        inline constexpr MatchFlagType FORMAT_PERL = ::boost::regex_constants::format_perl;
        inline constexpr MatchFlagType FORMAT_LITERAL = ::boost::regex_constants::format_literal;
        inline constexpr MatchFlagType FORMAT_NO_COPY = ::boost::regex_constants::format_no_copy;
        inline constexpr MatchFlagType FORMAT_FIRST_ONLY = ::boost::regex_constants::format_first_only;
        inline constexpr MatchFlagType FORMAT_ALL = ::boost::regex_constants::format_all;

        using ErrorType = ::boost::regex_constants::error_type;

        inline constexpr ErrorType ERROR_COLLATE = ::boost::regex_constants::error_collate;
        inline constexpr ErrorType ERROR_CTYPE = ::boost::regex_constants::error_ctype;
        inline constexpr ErrorType ERROR_ESCAPE = ::boost::regex_constants::error_escape;
        inline constexpr ErrorType ERROR_BACKREF = ::boost::regex_constants::error_backref;
        inline constexpr ErrorType ERROR_BRACK = ::boost::regex_constants::error_brack;
        inline constexpr ErrorType ERROR_PAREN = ::boost::regex_constants::error_paren;
        inline constexpr ErrorType ERROR_BRACE = ::boost::regex_constants::error_brace;
        inline constexpr ErrorType ERROR_BADBRACE = ::boost::regex_constants::error_badbrace;
        inline constexpr ErrorType ERROR_RANGE = ::boost::regex_constants::error_range;
        inline constexpr ErrorType ERROR_SPACE = ::boost::regex_constants::error_space;
        inline constexpr ErrorType ERROR_BADREPEAT = ::boost::regex_constants::error_badrepeat;
        inline constexpr ErrorType ERROR_COMPLEXITY = ::boost::regex_constants::error_complexity;
        inline constexpr ErrorType ERROR_STACK = ::boost::regex_constants::error_stack;
        inline constexpr ErrorType ERROR_BAD_PATTERN = ::boost::regex_constants::error_bad_pattern;
    }
}
