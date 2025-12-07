/**
 * @file tomlpp.cppm
 * @module tomlpp
 * @brief File containing the module declaration for toml++ 
 * This module re-exports tomlplusplus to tomlpp for convenience, and 
 * re-aliases all tomlplusplus types to PascalCase.
 */

module;

#ifndef TOMLPLUSPLUS_BUILD_MODULES
#include <toml++/toml.hpp>
#endif

export module tomlpp;

#ifdef TOMLPLUSPLUS_BUILD_MODULES
import tomlplusplus;
#endif

/**
 * @namespace tomlpp
 * @brief The toml++ namespace toml:: 
 */
export namespace tomlpp {
    /**
     * @namespace literals
     * @brief The toml++ namespace toml::literals::
     */
    inline namespace literals {
        using toml::literals::operator""_toml;
        using toml::literals::operator""_tpath;
    }

    using TomlArray = toml::array;
    using TomlDate = toml::date;
    using TomlDateTime = toml::date_time;

    template <typename T>
    using Inserter = toml::inserter<T>;

    using JsonFormatter = toml::json_formatter;
    using TomlKey = toml::key;
    using TomlNode = toml::node;

    template <typename T>
    using NodeView = toml::node_view<T>;

    using TomlParseException = toml::parse_error;
    using TomlParseResult = toml::parse_result;
    using TomlPath = toml::path;
    using PathComponent = toml::path_component;
    using SourcePosition = toml::source_position;
    using SourceRegion = toml::source_region;
    using TomlTable = toml::table;
    using TomlTime = toml::time;
    using TimeOffset = toml::time_offset;
    using TomlFormatter = toml::toml_formatter;

    template <typename T>
    using TomlValue = toml::value<T>;
    
    using YamlFormatter = toml::yaml_formatter;

    using FormatFlags = toml::format_flags;
    using NodeType = toml::node_type;
    using PathComponentType = toml::path_component_type;
    using TomlValueFlags = toml::value_flags;

    using ArrayIterator = toml::array_iterator;
    using ConstArrayIterator = toml::const_array_iterator;
    using ConstTableIterator = toml::const_table_iterator;
    using DefaultFormatter = toml::default_formatter;

    template <typename T>
    using InsertedTypeOf = toml::inserted_type_of<T>;

    template <typename T>
    using TomlOptional = toml::optional<T>;

    using SourceIndex = toml::source_index;
    using SourcePathPointer = toml::source_path_ptr;
    using TomlTableIterator = toml::table_iterator;

    using toml::at_path;
    using toml::operator""_toml;
    using toml::operator""_tpath;
    using toml::operator<<;
    using toml::parse;
    using toml::parse_file;

    template <typename T>
    constexpr bool IsArray = toml::is_array<T>;

    template <typename T>
    constexpr bool IsBoolean = toml::is_boolean<T>;

    template <typename T>
    constexpr bool IsChronological = toml::is_chronological<T>;
    
    template <typename T>
    constexpr bool IsContainer = toml::is_container<T>;

    template <typename T>
    constexpr bool IsDate = toml::is_date<T>;

    template <typename T>
    constexpr bool IsDateTime = toml::is_date_time<T>;

    template <typename T>
    constexpr bool IsFloatingPoint = toml::is_floating_point<T>;

    template <typename T>
    constexpr bool IsInteger = toml::is_integer<T>;

    template <typename T>
    constexpr bool IsKey = toml::is_key<T>;

    template <typename T>
    constexpr bool IsKeyOrConvertible = toml::is_key_or_convertible<T>;

    template <typename T>
    constexpr bool IsNode = toml::is_node<T>;

    template <typename T>
    constexpr bool IsNodeView = toml::is_node_view<T>;

    template <typename T>
    constexpr bool IsNumber = toml::is_number<T>;

    template <typename T>
    constexpr bool IsString = toml::is_string<T>;

    template <typename T>
    constexpr bool IsTable = toml::is_table<T>;

    template <typename T>
    constexpr bool IsTime = toml::is_time<T>;

    template <typename T>
    constexpr bool IsValue = toml::is_value<T>;

    constexpr TomlValueFlags preserveSourceValueFlags = toml::preserve_source_value_flags;
}
