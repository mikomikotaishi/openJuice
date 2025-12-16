/**
 * @file json.cppm
 * @module nlohmann.json
 * @brief File containing the module declaration for nlohmann.json 
 */

export module nlohmann.json;

import :detail;

/**
 * @namespace nlohmnann
 * @brief The nlohmann.json nlohmann:: namespace 
 */
export namespace nlohmann::json {
    using _detail::nlohmann::json::AdlSerializer;
    using _detail::nlohmann::json::BasicJson;
    using _detail::nlohmann::json::JsonPointer;
    using _detail::nlohmann::json::Json;
    using _detail::nlohmann::json::OrderedMap;
    using _detail::nlohmann::json::OrderedJson;

    using _detail::nlohmann::json::JsonSerializer;
    using _detail::nlohmann::json::JsonValue;
    using _detail::nlohmann::json::ErrorHandler;
    using _detail::nlohmann::json::CborTagHandler;
    using _detail::nlohmann::json::BinaryJsonDataVersion;
    using _detail::nlohmann::json::JsonInitializerList;
    using _detail::nlohmann::json::InputFormat;
    using _detail::nlohmann::json::JsonSax;

    using _detail::nlohmann::json::JsonValueType;
    using _detail::nlohmann::json::JsonReference;
    using _detail::nlohmann::json::JsonConstReference;
    using _detail::nlohmann::json::JsonDifferenceType;
    using _detail::nlohmann::json::JsonSizeType;
    using _detail::nlohmann::json::JsonAllocatorType;
    using _detail::nlohmann::json::JsonIterator;
    using _detail::nlohmann::json::JsonConstIterator;
    using _detail::nlohmann::json::JsonReverseIterator;
    using _detail::nlohmann::json::JsonConstReverseIterator;

    using _detail::nlohmann::json::JsonObject;
    using _detail::nlohmann::json::JsonArray;
    using _detail::nlohmann::json::JsonString;
    using _detail::nlohmann::json::JsonBoolean;
    using _detail::nlohmann::json::JsonInteger;
    using _detail::nlohmann::json::JsonUnsignedInteger;
    using _detail::nlohmann::json::JsonFloat;
    using _detail::nlohmann::json::JsonBinary;
    using _detail::nlohmann::json::JsonObjectComparator;
    using _detail::nlohmann::json::JsonDefaultObjectComparator;

    using _detail::nlohmann::json::JsonException;
    using _detail::nlohmann::json::JsonParseException;
    using _detail::nlohmann::json::InvalidJsonIteratorException;
    using _detail::nlohmann::json::JsonTypeException;
    using _detail::nlohmann::json::JsonOutOfRangeException;
    using _detail::nlohmann::json::JsonLibraryException;
}
