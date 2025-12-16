/**
 * @file json_detail.cppm
 * @module nlohmann.json:detail
 * @brief File containing the module declaration for nlohmann.json 
 */

module;

#include <nlohmann/json.hpp>

export module nlohmann.json:detail;

/**
 * @internal
 * @namespace _detail::nlohmann::json
 * @brief The nlohmann.json nlohmann:: namespace
 * Detail namespace - not to be exported for external use
 */
export namespace _detail::nlohmann::json {
    template <typename T = void, typename Err = void>
    using AdlSerializer = ::nlohmann::adl_serializer<T, Err>;

    template <
        template <typename U, typename V, typename... Args> class ObjectType = std::map,
        template <typename U, typename... Args> class ArrayType = std::vector,
        class StringType = std::string, 
        class BooleanType = bool,
        class NumberIntegerType = std::int64_t,
        class NumberUnsignedType = std::uint64_t,
        class NumberFloatType = double,
        template <typename U> class AllocatorType = std::allocator,
        template <typename T, typename Err = void> class JSONSerializer = ::nlohmann::adl_serializer,
        class BinaryType = std::vector<std::uint8_t>, // cppcheck-suppress syntaxError
        class CustomBaseClass = void
    >
    using BasicJson = ::nlohmann::basic_json<
        ObjectType, 
        ArrayType, 
        StringType, 
        BooleanType, 
        NumberIntegerType, 
        NumberUnsignedType, 
        NumberFloatType, 
        AllocatorType, 
        JSONSerializer, 
        BinaryType, 
        CustomBaseClass
    >;

    template <typename RefStringType>
    using JsonPointer = ::nlohmann::json_pointer<RefStringType>;

    using Json = ::nlohmann::json;
    
    template <class Key, class T, class IgnoredLess, class Allocator>
    using OrderedMap = ::nlohmann::ordered_map<Key, T, IgnoredLess, Allocator>;

    using OrderedJson = ::nlohmann::ordered_json;

    using JsonException = ::nlohmann::basic_json<>::exception;
    using JsonParseException = ::nlohmann::basic_json<>::parse_error;
    using InvalidJsonIteratorException = ::nlohmann::basic_json<>::invalid_iterator;
    using JsonTypeException = ::nlohmann::basic_json<>::type_error;
    using JsonOutOfRangeException = ::nlohmann::basic_json<>::out_of_range;
    using JsonLibraryException = ::nlohmann::basic_json<>::other_error;

    template <typename T, typename Err>
    using JsonSerializer = ::nlohmann::basic_json<>::json_serializer<T, Err>;

    using JsonValue = ::nlohmann::basic_json<>::value_t;
    using ErrorHandler = ::nlohmann::basic_json<>::error_handler_t;
    using CborTagHandler = ::nlohmann::basic_json<>::cbor_tag_handler_t;
    using BinaryJsonDataVersion = ::nlohmann::basic_json<>::bjdata_version_t;
    using JsonInitializerList = ::nlohmann::basic_json<>::initializer_list_t;
    using InputFormat = ::nlohmann::basic_json<>::input_format_t;
    using JsonSax = ::nlohmann::basic_json<>::json_sax_t;

    using JsonValueType = ::nlohmann::basic_json<>::value_type;
    using JsonReference = ::nlohmann::basic_json<>::reference;
    using JsonConstReference = ::nlohmann::basic_json<>::const_reference;
    using JsonDifferenceType = ::nlohmann::basic_json<>::difference_type;
    using JsonSizeType = ::nlohmann::basic_json<>::size_type;
    using JsonAllocatorType = ::nlohmann::basic_json<>::allocator_type;
    using JsonIterator = ::nlohmann::basic_json<>::iterator;
    using JsonConstIterator = ::nlohmann::basic_json<>::const_iterator;
    using JsonReverseIterator = ::nlohmann::basic_json<>::reverse_iterator;
    using JsonConstReverseIterator = ::nlohmann::basic_json<>::const_reverse_iterator;

    using JsonObject = ::nlohmann::basic_json<>::object_t;
    using JsonArray = ::nlohmann::basic_json<>::array_t;
    using JsonString = ::nlohmann::basic_json<>::string_t;
    using JsonBoolean = ::nlohmann::basic_json<>::boolean_t;
    using JsonInteger = ::nlohmann::basic_json<>::number_integer_t;
    using JsonUnsignedInteger = ::nlohmann::basic_json<>::number_unsigned_t;
    using JsonFloat = ::nlohmann::basic_json<>::number_float_t;
    using JsonBinary = ::nlohmann::basic_json<>::binary_t;
    using JsonObjectComparator = ::nlohmann::basic_json<>::object_comparator_t;
    using JsonDefaultObjectComparator = ::nlohmann::basic_json<>::default_object_comparator_t;
}
