/**
 * @file Meta.cppm
 * @module openjuice.engine.game.ecs.Meta
 * @brief Module of the ECS registry.
 *
 * This file contains the definitions for the ECS metaprogramming utilities.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs.Meta;

import std;

using std::mem::AlignValue;
using std::meta::EnableIfType;
using std::meta::IsConstValue;
using std::meta::IsConvertible;
using std::meta::IsPointerValue;
using std::meta::IsSameValue;
using std::meta::IsVolatileValue;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

export {
    using EntityId = u32; ///< An unsigned type representing an identifier value in the EntityManager
    using StorageId = u32; ///< An unsigned type representing an identifier value in the StorageManager
}

/**
 * @namespace meta
 * @brief Metaprogramming utilities for the ECS.
 * 
 * This namespace contains compile-time type manipulation utilities, function traits,
 * query parameter validation, and other metaprogramming facilities used throughout
 * the ECS implementation. These utilities enable type-safe component queries and
 * automatic parameter deduction.
 */
export namespace meta {
    /**
     * @class ComponentTypeInfo
     * @brief Stores size and alignment information for a component type.
     * 
     * This class encapsulates compile-time type information that is needed for
     * proper memory allocation and layout of components in the ECS storage system.
     * It supports comparison operations for sorting and organizing component types.
     */
    class ComponentTypeInfo {
    private:
        usize size; ///< The size of the component type in bytes.
        AlignValue alignment; ///< The alignment requirement of the component type.
    public:
        GETTER(usize, Size, size);
        GETTER(AlignValue, Alignment, alignment);

        /**
         * @brief Default constructor.
         */
        constexpr ComponentTypeInfo() = default;
        
        /**
         * @brief Default destructor.
         */
        constexpr ~ComponentTypeInfo() = default;
        
        /**
         * @brief Default copy constructor.
         *
         * @param other The ComponentTypeInfo to copy from.
         */
        constexpr ComponentTypeInfo(const ComponentTypeInfo& other) = default;

        /**
         * @brief Constructs ComponentTypeInfo with specified size and alignment.
         *
         * @param size The size of the component type in bytes.
         * @param alignment The alignment requirement of the component type.
         */
        constexpr ComponentTypeInfo(usize size, AlignValue alignment):
            size{size}, alignment{alignment} {}

        /**
         * @brief Three-way comparison operator.
         * @param other The ComponentTypeInfo to compare with.
         * @return StrongOrdering The comparison result.
         */
        constexpr StrongOrdering operator<=>(const ComponentTypeInfo& other) const noexcept = default;
    };

    /**
     * @brief Implementation function to count pointer types in a parameter pack.
     *
     * @tparam Ts Types to check.
     * @return The number of pointer types in the pack.
     */
    template <typename... Ts>
    [[nodiscard]]
    constexpr usize pointerTypeCountImpl() {
        return (0 + ... + (IsPointerValue<Ts> ? 1 : 0));
    }

    /**
     * @struct PointerTypeCount
     * @brief Counts the number of pointer types in a parameter pack.
     *
     * @tparam Ts Types to count pointers from.
     */
    template <typename... Ts>
    struct PointerTypeCount {
        static constexpr usize VALUE = pointerTypeCountImpl<Ts...>(); ///< The count of pointer types.
    };

    /**
     * @struct PointerTypeCount
     * @brief Specialisation for Tuple types.
     *
     * @tparam Ts Types within the Tuple to count pointers from.
     */
    template <typename... Ts>
    struct PointerTypeCount<Tuple<Ts...>> {
        static constexpr usize VALUE = pointerTypeCountImpl<Ts...>(); ///< The count of pointer types.
    };

    /**
     * @brief Implementation function to count non-pointer types in a parameter pack.
     *
     * @tparam Ts Types to check.
     * @return The number of non-pointer types in the pack.
     */
    template <typename... Ts>
    constexpr usize nonPointerTypeCountImpl() {
        return (0 + ... + (!IsPointerValue<Ts> ? 1 : 0));
    }

    /**
     * @struct NonPointerTypeCount
     * @brief Counts the number of non-pointer types in a parameter pack.
     *
     * @tparam Ts Types to count non-pointers from.
     */
    template <typename... Ts>
    struct NonPointerTypeCount {
        static constexpr usize VALUE = nonPointerTypeCountImpl<Ts...>(); ///< The count of non-pointer types.
    };

    /**
     * @struct NonPointerTypeCount
     * @brief Specialisation for Tuple types.
     *
     * @tparam Ts Types within the Tuple to count non-pointers from.
     */
    template <typename... Ts>
    struct NonPointerTypeCount<Tuple<Ts...>> {
        static constexpr usize VALUE = nonPointerTypeCountImpl<Ts...>(); ///< The count of non-pointer types.
    };

    /**
     * @struct RemoveSuffixConstVolatile
     * @brief Removes const and volatile qualifiers from references and pointers.
     * 
     * This trait removes only the suffix const/volatile qualifiers (those applied
     * to the reference or pointer itself), not those applied to the pointed-to type.
     * For example, `const int&` becomes `int&`, but `int* const` becomes `int*`.
     * 
     * @tparam T The type to remove qualifiers from.
     */
    template <typename T>
    struct RemoveSuffixConstVolatile {
        using Type = T; ///< The unqualified type.
    };

    template <typename T>
    struct RemoveSuffixConstVolatile<T const&> {
        using Type = T&;
    };

    template <typename T>
    struct RemoveSuffixConstVolatile<T volatile&> {
        using Type = T&;
    };

    template <typename T>
    struct RemoveSuffixConstVolatile<T const volatile&> {
        using Type = T&;
    };

    template <typename T>
    struct RemoveSuffixConstVolatile<T const*> {
        using Type = T*;
    };

    template <typename T>
    struct RemoveSuffixConstVolatile<T volatile*> {
        using Type = T*;
    };

    template <typename T>
    struct RemoveSuffixConstVolatile<T const volatile*> {
        using Type = T*;
    };

    template <typename T>
    using RemoveSuffixConstVolatileType = typename RemoveSuffixConstVolatile<T>::Type;

    /**
     * @struct FunctionTraits
     * @brief Extracts type information from callable types.
     * 
     * Provides compile-time introspection of function signatures, including
     * return types, argument types, and argument counts. Supports function pointers,
     * member function pointers, and callable objects (lambdas, functors).
     * 
     * @tparam Ret The return type.
     * @tparam ArgTypes The argument types.
     */
    template <typename Ret, typename... ArgTypes>
    struct FunctionTraits {};

    /**
     * @struct FunctionTraits<Ret(*)(ArgTypes...)>
     * @brief Specialisation for function pointer types.
     *
     * @tparam Ret The return type of the function.
     * @tparam ArgTypes The parameter types of the function.
     */
    template <typename Ret, typename... ArgTypes>
    struct FunctionTraits<Ret(*)(ArgTypes...)> {
        using ReturnType = Ret; ///< The return type of the function.
        using ArgsTuple = Tuple<ArgTypes...>; ///< Tuple containing all argument types.

        /**
         * @brief Retrieves the type of the argument at the given index.
         * @tparam Index The zero-based index of the argument.
         */
        template <usize Index>
        using ArgumentAt = TupleElementType<Index, ArgsTuple>;

        static constexpr usize ARG_COUNT = sizeof...(ArgTypes); ///< The number of arguments.
    };

    /**
     * @struct FunctionTraits<Ret(ArgTypes...)>
     * @brief Specialisation for plain function types.
     *
     * @tparam Ret The return type of the function.
     * @tparam ArgTypes The parameter types of the function.
     */
    template <typename Ret, typename... ArgTypes>
    struct FunctionTraits<Ret(ArgTypes...)> {
        using ReturnType = Ret; ///< The return type of the function.
        using ArgsTuple = Tuple<ArgTypes...>; ///< Tuple containing all argument types.

        /**
         * @brief Retrieves the type of the argument at the given index.
         * @tparam Index The zero-based index of the argument.
         */
        template <usize Index>
        using ArgumentAt = TupleElementType<Index, ArgsTuple>;

        static constexpr usize ARG_COUNT = sizeof...(ArgTypes); ///< The number of arguments.
    };

    /**
     * @struct FunctionTraits<Ret(Obj::*)(ArgTypes...)>
     * @brief Specialisation for non-const member function pointer types.
     *
     * @tparam Ret The return type of the member function.
     * @tparam Obj The class type that owns the member function.
     * @tparam ArgTypes The parameter types of the member function.
     */
    template <typename Ret, typename Obj, typename... ArgTypes>
    struct FunctionTraits<Ret(Obj::*)(ArgTypes...)> {
        using ReturnType = Ret; ///< The return type of the member function.
        using ObjectType = Obj; ///< The class type that owns this member function.
        using ArgsTuple = Tuple<ArgTypes...>; ///< Tuple containing all argument types.

        /**
         * @brief Retrieves the type of the argument at the given index.
         * @tparam Index The zero-based index of the argument.
         */
        template <usize Index>
        using ArgumentAt = TupleElementType<Index, ArgsTuple>;

        static constexpr usize ARG_COUNT = sizeof...(ArgTypes); ///< The number of arguments.
    };

    /**
     * @struct FunctionTraits<Ret(Obj::*)(ArgTypes...) const>
     * @brief Specialisation for const member function pointer types.
     *
     * @tparam Ret The return type of the member function.
     * @tparam Obj The class type that owns the member function.
     * @tparam ArgTypes The parameter types of the member function.
     */
    template <typename Ret, typename Obj, typename... ArgTypes>
    struct FunctionTraits<Ret(Obj::*)(ArgTypes...) const> {
        using ReturnType = Ret; ///< The return type of the member function.
        using ObjectType = Obj; ///< The class type that owns this member function.
        using ArgsTuple = Tuple<ArgTypes...>; ///< Tuple containing all argument types.

        /**
         * @brief Retrieves the type of the argument at the given index.
         * @tparam Index The zero-based index of the argument.
         */
        template <usize Index>
        using ArgumentAt = TupleElementType<Index, ArgsTuple>;

        static constexpr usize ARG_COUNT = sizeof...(ArgTypes); ///< The number of arguments.
    };

    /**
     * @struct FunctionTraits<Callable>
     * @brief Specialisation for callable objects (lambdas, functors).
     * 
     * Deduces function traits from the operator() of the callable object.
     * 
     * @tparam Callable A type with an operator() method (lambda, functor, etc.).
     */
    template <typename Callable>
    struct FunctionTraits<Callable>: FunctionTraits<decltype(&Callable::operator())> {};

    /**
     * @struct SubTuple
     * @brief Extracts a sub-tuple from a tuple type by index range.
     * 
     * Creates a new tuple type containing elements from [Start, End) of the original tuple.
     * 
     * @tparam Tpl The source tuple type.
     * @tparam Start The starting index (inclusive).
     * @tparam End The ending index (exclusive).
     */
    template <typename Tpl, usize Start, usize End, typename = void>
    struct SubTuple {
        using InternalTuple = decltype([]<usize... I>(IndexSequence<I...>) -> Tuple<TupleElementType<Start + I, Tpl>...>
            {}(make_index_sequence<End - Start>{})
        ); ///< The extracted sub-tuple type.
    };

    /**
     * @struct SubTuple
     * @brief Specialisation when the range exceeds tuple size.
     * 
     * Returns an empty tuple when the requested range is invalid.
     * 
     * @tparam Tpl The source tuple type.
     * @tparam Start The starting index.
     * @tparam End The ending index.
     */
    template <typename Tpl, usize Start, usize End>
    struct SubTuple<Tpl, Start, End, EnableIfType<((End - Start) > TupleSizeValue<Tpl>)>> {
        using InternalTuple = Tuple<>; ///< Empty tuple type.
    };

    /**
     * @struct TransformEach
     * @brief Applies a type transformation to each element of a tuple.
     *
     * @tparam T The tuple type to transform.
     * @tparam F The transformation template to apply to each element.
     */
    template <typename T, template <typename> typename F>
    struct TransformEach;

    /**
     * @struct TransformEach<Tuple<Ts...>, F>
     * @brief Specialisation that transforms each type in the tuple.
     *
     * @tparam Ts The types within the tuple.
     * @tparam F The transformation template to apply.
     */
    template <typename... Ts, template <typename> typename F>
    struct TransformEach<Tuple<Ts...>, F> {
        using Type = Tuple<F<Ts>...>; ///< The transformed tuple type.
    };

    /**
     * @typedef TransformEachType
     * @brief Convenience alias for TransformEach::Type.
     *
     * @tparam T The tuple type to transform.
     * @tparam F The transformation template to apply.
     */
    template <typename T, template <typename...> typename F>
    using TransformEachType = typename TransformEach<T, F>::Type;

    /**
     * @struct Collect
     * @brief Checks if a predicate holds for all types in a parameter pack.
     *
     * @tparam P A unary predicate template.
     * @tparam Args The types to check.
     */
    template <template <typename> typename P, typename... Args>
    struct Collect {
        static constexpr bool VALUE = (P<Args>::VALUE && ...); ///< True if P holds for all Args.
    };

    /**
     * @struct CollectPairs
     * @brief Checks if a binary predicate holds for all corresponding pairs from two tuples.
     *
     * @tparam P A binary predicate template.
     * @tparam Tpl1 The first tuple type.
     * @tparam Tpl2 The second tuple type.
     */
    template <template <typename, typename> typename P, typename Tpl1, typename Tpl2>
    struct CollectPairs {
        static constexpr bool VALUE = []<usize... I>(IndexSequence<I...>) -> bool {
            return (P<TupleElementType<I, Tpl1>, TupleElementType<I, Tpl2>>::VALUE && ...);
        }(make_index_sequence<TupleSizeValue<Tpl1>>{}); ///< True if P holds for all pairs.
    };

    /**
     * @struct QueryTraits
     * @brief Analyzes query function signatures for ECS component queries.
     * 
     * Extracts information about query parameters including:
     * - Whether the query passes EntityId as the first parameter
     * - Separation of required (non-pointer) and optional (pointer) components
     * - Handling of fall-through parameters
     * - Removal of const/volatile qualifiers for storage lookup
     * 
     * @tparam Fn The query function type to analyze.
     * @tparam Offset The number of parameters to skip at the beginning.
     * @tparam Params Additional fall-through parameter types.
     */
    template <typename Fn, usize Offset, typename... Params>
    struct QueryTraits {
        using DirtyArgsTuple = typename FunctionTraits<Fn>::ArgsTuple;

        static constexpr usize PARAMS_COUNT = sizeof...(Params) + Offset;
        static constexpr bool IS_EMPTY = (TupleSizeValue<DirtyArgsTuple> - sizeof...(Params) == 0);
        static constexpr bool PASSES_ENTITY_ID = []() -> bool {
            if constexpr (IS_EMPTY) {
                return false;
            } else {
                return IsSameValue<TupleElementType<0, DirtyArgsTuple>, EntityId>;
            }
        }();

        using ParamsTuple = typename SubTuple<DirtyArgsTuple, Offset + PASSES_ENTITY_ID, PARAMS_COUNT + PASSES_ENTITY_ID>::InternalTuple;
        using NoConstVolatileArgsTuple = TransformEachType<DirtyArgsTuple, RemoveSuffixConstVolatileType>;

        static constexpr usize ARGS_COUNT = TupleSizeValue<NoConstVolatileArgsTuple>;

        using NoParamsNoConstVolatileArgsTuple = SubTuple<NoConstVolatileArgsTuple, PARAMS_COUNT + PASSES_ENTITY_ID, ARGS_COUNT>::InternalTuple;

        static constexpr usize NO_PARAMS_ARGS_COUNT = TupleSizeValue<NoParamsNoConstVolatileArgsTuple>;
        static constexpr usize REQUIRED_COUNT = NonPointerTypeCount<NoParamsNoConstVolatileArgsTuple>::Value;
        static constexpr usize OPTOINAL_COUNT = PointerTypeCount<NoParamsNoConstVolatileArgsTuple>::Value;
    };

    /**
     * @brief Checks whether type T is a valid component type.
     * 
     * A valid component must not be const or volatile qualified. These qualifiers
     * are only allowed in query contexts when accessing components.
     * 
     * @tparam T The type to validate.
     * @return bool True if T is not const and not volatile.
     */
    template <typename T>
    [[nodiscard]]
    consteval bool validComponentFn() noexcept {
        static_assert(!IsConstValue<T>, "Component may only be const-qualified in query contexts.");
        static_assert(!IsVolatileValue<T>, "Component may only be volatile-qualified in query contexts.");
        return !IsConstValue<T> && !IsVolatileValue<T>;
    }

    /**
     * @concept ValidComponent
     * @brief Concept that enforces valid component type constraints.
     * 
     * Ensures that component types are not const or volatile qualified at the storage level.
     * 
     * @tparam T The type to validate as a component.
     */
    template <typename T>
    concept ValidComponent = validComponentFn<T>();

    /**
     * @brief Validates that fall-through parameters are convertible to query parameters.
     * 
     * Ensures type safety when passing additional parameters to query functions.
     * 
     * @tparam Fn The query function type.
     * @tparam Offset The parameter offset.
     * @tparam Params The fall-through parameter types.
     * @return bool True if all parameters are convertible.
     */
    template <typename Fn, usize Offset, typename... Params>
    [[nodiscard]]
    consteval bool ensureFallthroughParametersFn() noexcept {
        constexpr bool result = CollectPairs<IsConvertible, Tuple<Params...>, typename QueryTraits<Fn, Offset, Params...>::ParamsTuple>::VALUE;
        static_assert(result, "All fall-through parameters must be convertible to corresponding query function parameters.");
        return result;
    }

    /**
     * @concept EnsureFallthroughParameters
     * @brief Enforces that fall-through parameters match query function signature.
     *
     * @tparam Fn The query function type.
     * @tparam Offset The parameter offset.
     * @tparam Params The fall-through parameter types.
     */
    template <typename Fn, usize Offset, typename... Params>
    concept EnsureFallthroughParameters = ensureFallthroughParametersFn<Fn, Offset, Params...>();

    /**
     * @brief Validates that a query parameter at a given index matches expected type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index to check.
     * @tparam T The expected parameter type.
     * @tparam Params Additional parameter types.
     * @return bool True if the parameter type matches.
     */
    template <typename Fn, usize Index, typename T, typename... Params>
    [[nodiscard]]
    consteval bool ensureParameterFn() noexcept {
        constexpr bool result = IsSameValue<typename FunctionTraits<Fn>::template ArgumentAt<sizeof...(Params) + Index>, T>;
        static_assert(result, "Unexpected query parameter.");
        return result;
    }

    /**
     * @concept EnsureParameter
     * @brief Enforces that a query parameter matches the expected type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index.
     * @tparam T The expected type.
     * @tparam Params Additional parameters.
     */
    template <typename Fn, usize Index, typename T, typename... Params>
    concept EnsureParameter = ensureParameterFn<Fn, Index, T, Params...>();

    /**
     * @brief Validates that a query parameter is EntityId type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index to check.
     * @tparam Params Additional parameter types.
     * @return bool True if the parameter is EntityId.
     */
    template <typename Fn, usize Index, typename... Params>
    [[nodiscard]]
    consteval bool ensureEntityIdFn() noexcept {
        constexpr bool result = IsSameValue<typename FunctionTraits<Fn>::template ArgumentAt<sizeof...(Params) + Index>, EntityId>;
        static_assert(result, "Unexpected query function parameter, expected EntityId.");
        return result;
    }

    /**
     * @concept EnsureEntityId
     * @brief Enforces that a query parameter is EntityId type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index.
     * @tparam Params Additional parameters.
     */
    template <typename Fn, usize Index, typename... Params>
    concept EnsureEntityId = ensureEntityIdFn<Fn, Index, Params...>();

    /**
     * @brief Validates that a query parameter is usize type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index to check.
     * @tparam Params Additional parameter types.
     * @return bool True if the parameter is usize.
     */
    template <typename Fn, usize Index, typename... Params>
    [[nodiscard]]
    consteval bool ensureSizeFn() noexcept {
        constexpr bool result = IsSameValue<typename FunctionTraits<Fn>::template ArgumentAt<sizeof...(Params) + Index>, usize>;
        static_assert(result, "Unexpected query function parameter, expected usize.");
        return result;
    }

    /**
     * @concept EnsureSize
     * @brief Enforces that a query parameter is usize type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index.
     * @tparam Params Additional parameters.
     */
    template <typename Fn, usize Index, typename... Params>
    concept EnsureSize = ensureSizeFn<Fn, Index, Params...>();

    /**
     * @brief Validates that a query parameter is AlignValue type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index to check.
     * @tparam Params Additional parameter types.
     * @return bool True if the parameter is AlignValue.
     */
    template <typename Fn, usize Index, typename... Params>
    [[nodiscard]]
    consteval bool ensureAlignmentFn() noexcept {
        constexpr bool result = IsSameValue<typename FunctionTraits<Fn>::template ArgumentAt<sizeof...(Params) + Index>, AlignValue>;
        static_assert(result, "Unexpected query function parameter, expected AlignValue.");
        return result;
    }

    /**
     * @concept EnsureAlignment
     * @brief Enforces that a query parameter is AlignValue type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index.
     * @tparam Params Additional parameters.
     */
    template <typename Fn, usize Index, typename... Params>
    concept EnsureAlignment = ensureAlignmentFn<Fn, Index, Params...>();

    /**
     * @brief Validates that a query parameter is ComponentTypeInfo type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index to check.
     * @tparam Params Additional parameter types.
     * @return bool True if the parameter is ComponentTypeInfo.
     */
    template <typename Fn, usize Index, typename... Params>
    [[nodiscard]]
    consteval bool ensureComponentTypeInfoFn() noexcept {
        constexpr bool result = IsSameValue<typename FunctionTraits<Fn>::template ArgumentAt<sizeof...(Params) + Index>, ComponentTypeInfo>;
        static_assert(result, "Unexpected query function parameter, expected ComponentTypeInfo.");
        return result;
    }

    /**
     * @concept EnsureComponentTypeInfo
     * @brief Enforces that a query parameter is ComponentTypeInfo type.
     *
     * @tparam Fn The query function type.
     * @tparam Index The parameter index.
     * @tparam Params Additional parameters.
     */
    template <typename Fn, usize Index, typename... Params>
    concept EnsureComponentTypeInfo = ensureComponentTypeInfoFn<Fn, Index, Params...>();
}

END_MODULE_NAMESPACE();
