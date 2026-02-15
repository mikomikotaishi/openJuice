/**
 * @file Registry.cppm
 * @module openjuice.engine.game.ecs:Registry
 * @brief Module of the ECS registry.
 *
 * This file contains the definitions for the ECS registry.
 * Based on kawa_ecs (https://github.com/superPuero/kawa_ecs)
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.game.ecs:Registry;

import stdx;

import :EntityManager;
import :Meta;
import :PolymorphicStorage;
import :StorageManager;
import :ThreadPool;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::mem::UniquePointer;
using stdx::meta::IsPointerValue;
using stdx::meta::RemoveConstVolatileReferenceType;
using stdx::meta::RemovePointerType;
using stdx::meta::RemoveReferenceType;
using stdx::ranges::IotaView;

using openjuice::engine::game::ecs::meta::ComponentTypeInfo;
using openjuice::engine::game::ecs::meta::EnsureComponentTypeInfo;
using openjuice::engine::game::ecs::meta::EnsureEntityId;
using openjuice::engine::game::ecs::meta::EnsureFallthroughParameters;
using openjuice::engine::game::ecs::meta::FunctionTraits;
using openjuice::engine::game::ecs::meta::QueryTraits;
using openjuice::engine::game::ecs::meta::ValidComponent;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

export {
    using openjuice::engine::game::ecs::EntityId; ///< An unsigned type representing an identifier value in the EntityManager
    using openjuice::engine::game::ecs::StorageId; ///< An unsigned type representing an identifier value in the StorageManager
    using openjuice::engine::game::ecs::meta::ComponentTypeInfo; ///< An aggregation of size and memory alignment information of the component type
}

/**
 * @class Registry
 * @brief The central coordinator for an Entity Component System.
 * 
 * Registry manages the entire ECS, providing a high-level API for entity lifecycle,
 * component management, and querying. It coordinates between EntityManager (entity IDs)
 * and StorageManager (component data) to provide a cohesive system.
 *
 * The query system inspects function parameters and matches entities accordingly:
 * - Fallthrough parameters (T, T&, T*): Passed from outside, not from components
 * - Required components (Component&, const Component&): Entity must have these
 * - Optional components (Component*): nullptr if entity lacks the component
 */
export class Registry {
public:
    /**
     * @enum Error
     * @brief Enumeration for registry errors.
     * 
     * The DeckPointError enumeration defines the types of errors on ECS registry operations.
     */
    enum class Error: u8 {
        ENTITY_CREATE_FAILURE, ///< Failure to create an entity on the Registry
    };
private:
    static inline StorageId idCount = 0; ///< Global counter for assigning unique storage IDs across component types.
    EntityManager entityManager; ///< Manages entity IDs and lifecycle.
    StorageManager storageManager; ///< Manages component storage and type information.
    u32 capacity = 512; ///< The maximum number of entities that can exist simultaneously.
    u32 queryLevel = 0; ///< Nesting counter tracking active query contexts (for safety checks).
    bool parallelQueryRunning = false; ///< Indicates whether a parallel query is currently executing.

    /**
     * @brief Retrieves the unique storage ID for a component type.
     * 
     * Uses a static local variable to cache the ID, ensuring consistent IDs
     * across multiple calls for the same type.
     * 
     * @tparam T The component type.
     * @return StorageId The unique storage ID for type T.
     */
    template <typename T>
    [[nodiscard]]
    StorageId getId() noexcept {
        static StorageId id = storageManager.getId<T>();
        return id;
    }

    /**
     * @brief Populates an array with storage pointers for optional (pointer) components.
     * 
     * Filters the argument tuple to extract only pointer types and retrieves their
     * corresponding storage containers.
     * 
     * @tparam ArgsTpl The tuple of argument types.
     * @tparam I Index sequence for iterating arguments.
     * @tparam N The size of the output array.
     * @param out Output array to populate with storage pointers.
     */
    template <typename ArgsTpl, usize... I, usize N>
    constexpr void populateOptionalArray(Array<PolymorphicStorage*, N>& out) noexcept {
        usize id = 0;
        (([&]<usize J>() -> void {
            using T = TupleElementType<I, ArgsTpl>;
            if constexpr (IsPointerValue<T>) {
                using CleanT = RemovePointerType<T>;
                StorageId key = getId<CleanT>();
                out[id] = &storageManager.getStorage(key);
                ++id;
            }
        }.template operator()<I>(), void(), 0), ...);
    }

    /**
     * @brief Populates an array with storage pointers for required (non-pointer) components.
     * 
     * Filters the argument tuple to extract only non-pointer types and retrieves their
     * corresponding storage containers.
     * 
     * @tparam ArgsTpl The tuple of argument types.
     * @tparam I Index sequence for iterating arguments.
     * @tparam N The size of the output array.
     * @param out Output array to populate with storage pointers.
     */
    template <typename ArgsTpl, usize... I, usize N>
    constexpr void populateRequiredArray(Array<PolymorphicStorage*, N>& out) noexcept {
        usize id = 0;
        (([&]<usize J>() -> void {
            using T = TupleElementType<I, ArgsTpl>;
            if constexpr (!IsPointerValue<T>) {
                using CleanT = RemovePointerType<T>;
                StorageId key = getId<CleanT>();
                out[id] = &storageManager.getStorage(key);
                ++id;
            }
        }.template operator()<I>(), void(), 0), ...);
    }

    /**
     * @brief Core implementation for sequential query execution.
     * 
     * Iterates over entities matching the required components and invokes the query
     * function with appropriate parameters.
     * 
     * @tparam Fn The query function type.
     * @tparam ArgsTpl Tuple of component argument types.
     * @tparam ArgsInds Index sequence for all arguments.
     * @tparam RequiredInds Index sequence for required components.
     * @tparam OptionalInds Index sequence for optional components.
     * @tparam Params Fallthrough parameter types.
     * @param fn The query function to execute.
     * @param argsIndices Index sequence for component arguments.
     * @param requiredIndices Index sequence for required components.
     * @param optionalIndices Index sequence for optional components.
     * @param params Fallthrough parameters forwarded to the query function.
     */
    template <typename Fn, typename ArgsTpl, usize... ArgsInds, usize... RequiredInds, usize... OptionalInds, typename... Params>
    void queryImpl(
        Fn&& fn,
        [[maybe_unused]] IndexSequence<ArgsInds...> argsIndices,
        [[maybe_unused]] IndexSequence<RequiredInds...> requiredIndices,
        [[maybe_unused]] IndexSequence<OptionalInds...> optionalIndices,
        Params&&... params
    ) noexcept {
        [[maybe_unused]]
        constexpr usize ARGS_COUNT = sizeof...(ArgsInds);
        
        constexpr usize REQUIRED_COUNT = sizeof...(RequiredInds);
        constexpr usize OPTIONAL_COUNT = sizeof...(OptionalInds);
        auto argsStorages = forward_as_tuple(
            storageManager.getStorage<RemovePointerType<RemoveReferenceType<TupleElementType<ArgsInds, ArgsTpl>>>>()...
        );
        Array<PolymorphicStorage*, OPTIONAL_COUNT> optionalStorages;
        populateOptionalArray<ArgsTpl, ArgsInds...>(optionalStorages);
        if constexpr (REQUIRED_COUNT > 0) {
            Array<PolymorphicStorage*, REQUIRED_COUNT> requiredStorages = {};
            populateRequiredArray<ArgsTpl, ArgsInds...>(requiredStorages);
            PolymorphicStorage* smallest = *stdx::ranges::min_element(
                requiredStorages,
                [](PolymorphicStorage* a, PolymorphicStorage* b) -> bool {
                    return a->getOccupied() < b->getOccupied();
                }
            );
            apply(
                [&](auto&&... storages) -> void {
                    for (EntityId id: *smallest) {
                        if ((requiredStorages[RequiredInds]->has(id) && ...)) {
                            stdx::util::forward<Fn>(fn)(
                                stdx::util::forward<Params>(params)..., 
                                storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                            );
                        }
                    }
                },
                argsStorages
            );
        } else {
            apply(
                [&](auto&&... storages) -> void {
                    for (EntityId id: entityManager) {
                        stdx::util::forward<Fn>(fn)(
                            stdx::util::forward<Params>(params)..., 
                            storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                        );
                    }
                },
                argsStorages
            );
        }
    }

    /**
     * @brief Core implementation for parallel query execution.
     * 
     * Distributes entity iteration across worker threads in the thread pool.
     * Each thread processes a chunk of the entity range independently.
     * 
     * @tparam Fn The query function type.
     * @tparam ArgsTpl Tuple of component argument types.
     * @tparam ArgsInds Index sequence for all arguments.
     * @tparam RequiredInds Index sequence for required components.
     * @tparam OptionalInds Index sequence for optional components.
     * @tparam Params Fallthrough parameter types.
     * @param pool The thread pool to use for parallel execution.
     * @param fn The query function to execute.
     * @param argsIndices Index sequence for component arguments.
     * @param requiredIndices Index sequence for required components.
     * @param optionalIndices Index sequence for optional components.
     * @param params Fallthrough parameters forwarded to the query function.
     */
    template <typename Fn, typename ArgsTpl, usize... ArgsInds, usize... RequiredInds, usize... OptionalInds, typename... Params>
    void queryParallelImpl(
        ThreadPool& pool, 
        Fn&& fn,
        [[maybe_unused]] IndexSequence<ArgsInds...> argsIndices,
        [[maybe_unused]] IndexSequence<RequiredInds...> requiredIndices,
        [[maybe_unused]] IndexSequence<OptionalInds...> optionalIndices,
        Params&&... params
    ) noexcept {
        [[maybe_unused]]
        constexpr usize ARGS_COUNT = sizeof...(ArgsInds);

        constexpr usize REQUIRED_COUNT = sizeof...(RequiredInds);
        constexpr usize OPTIONAL_COUNT = sizeof...(OptionalInds);

        auto argsStorages = forward_as_tuple(
            storageManager.getStorage<RemovePointerType<RemoveReferenceType<TupleElementType<ArgsInds, ArgsTpl>>>>()...
        );
        Array<PolymorphicStorage*, OPTIONAL_COUNT> optionalStorages;
        populateOptionalArray<ArgsTpl, ArgsInds...>(optionalStorages);
        if constexpr (REQUIRED_COUNT > 0) {
            Array<PolymorphicStorage*, REQUIRED_COUNT> requiredStorages = {};
            populateRequiredArray<ArgsTpl, ArgsInds...>(requiredStorages);
            PolymorphicStorage* smallest = *stdx::ranges::min_element(
                requiredStorages,
                [](PolymorphicStorage* a, PolymorphicStorage* b) -> bool {
                    return a->getOccupied() < b->getOccupied();
                }
            );
            pool.execTask(
                [&](usize start, usize end) -> void {
                    apply(
                        [&](auto&&... storages) {
                            for (usize i: IotaView(start, end)) {
                                EntityId id = smallest->get(i);
                                if ((requiredStorages[RequiredInds]->has(id) && ...)) {
                                    fn(
                                        stdx::util::forward<Params>(params)...,
                                        storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                                    );
                                }
                            }
                        },
                        argsStorages
                    );
                },
                smallest->getOccupied()
            );
        } else {
            pool.execTask(
                [&](usize start, usize end) {
                    apply(
                        [&](auto&&... storages) {
                            for (usize i: IotaView(start, end)) {
                                EntityId id = entityManager[i];
                                fn(
                                    stdx::util::forward<Params>(params)...,
                                    storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                                );
                            }
                        },
                        argsStorages
                    );
                },
                entityManager.getOccupied()
            );
        }
    }

    /**
     * @brief Core implementation for queries that pass EntityId to the callback.
     * 
     * Similar to queryImpl but automatically passes the entity ID as the first
     * parameter to the query function.
     * 
     * @tparam Fn The query function type (first parameter must be EntityId).
     * @tparam ArgsTpl Tuple of component argument types.
     * @tparam ArgsInds Index sequence for all arguments.
     * @tparam RequiredInds Index sequence for required components.
     * @tparam OptionalInds Index sequence for optional components.
     * @tparam Params Fallthrough parameter types.
     * @param fn The query function to execute.
     * @param argsIndices Index sequence for component arguments.
     * @param requiredIndices Index sequence for required components.
     * @param optionalIndices Index sequence for optional components.
     * @param params Fallthrough parameters forwarded to the query function.
     */
    template <typename Fn, typename ArgsTpl, usize... ArgsInds, usize... RequiredInds, usize... OptionalInds, typename... Params>
    void querySelfImpl(
        Fn&& fn, 
        [[maybe_unused]] IndexSequence<ArgsInds...> argsIndices,
        [[maybe_unused]] IndexSequence<RequiredInds...> requiredIndices,
        [[maybe_unused]] IndexSequence<OptionalInds...> optionalIndices,
        Params&&... params
    ) noexcept {
        [[maybe_unused]]
        constexpr usize ARGS_COUNT = sizeof...(ArgsInds);

        constexpr usize REQUIRED_COUNT = sizeof...(RequiredInds);
        constexpr usize OPTIONAL_COUNT = sizeof...(OptionalInds);

        auto argsStorages = forward_as_tuple(
            storageManager.getStorage<RemovePointerType<RemoveReferenceType<TupleElementType<ArgsInds, ArgsTpl>>>>()...
        );
        Array<PolymorphicStorage*, OPTIONAL_COUNT> optionalStorages;
        populateOptionalArray<ArgsTpl, ArgsInds...>(optionalStorages);
        if constexpr (REQUIRED_COUNT > 0) {
            Array<PolymorphicStorage*, REQUIRED_COUNT> requiredStorages = {};
            populateRequiredArray<ArgsTpl, ArgsInds...>(requiredStorages);
            PolymorphicStorage* smallest = *stdx::ranges::min_element(
                requiredStorages,
                [](PolymorphicStorage* a, PolymorphicStorage* b) -> bool {
                    return a->getOccupied() < b->getOccupied();
                }
            );
            apply(
                [&](auto&&... storages) -> void {
                    for (EntityId id: *smallest) {
                        if ((requiredStorages[RequiredInds]->has(id) && ...)) {
                            fn(
                                id,
                                stdx::util::forward<Params>(params)...,
                                storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                            );
                        }
                    }
                },
                argsStorages
            );
        } else {
            apply(
                [&](auto&&... storages) -> void {
                    for (EntityId id: entityManager) {
                        fn(
                            id,
                            stdx::util::forward<Params>(params)...,
                            storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                        );
                    }
                },
                argsStorages
            );
        }
    }

    /**
     * @brief Parallel implementation for queries that pass EntityId to the callback.
     * 
     * Combines the behaviours of queryParallelImpl and querySelfImpl for parallel
     * execution with EntityId passing.
     * 
     * @tparam Fn The query function type (first parameter must be EntityId).
     * @tparam ArgsTpl Tuple of component argument types.
     * @tparam ArgsInds Index sequence for all arguments.
     * @tparam RequiredInds Index sequence for required components.
     * @tparam OptionalInds Index sequence for optional components.
     * @tparam Params Fallthrough parameter types.
     * @param pool The thread pool to use for parallel execution.
     * @param fn The query function to execute.
     * @param argsIndices Index sequence for component arguments.
     * @param requiredIndices Index sequence for required components.
     * @param optionalIndices Index sequence for optional components.
     * @param params Fallthrough parameters forwarded to the query function.
     */
    template <typename Fn, typename ArgsTpl, usize... ArgsInds, usize... RequiredInds, usize... OptionalInds, typename... Params>
    void querySelfParallelImpl(
        ThreadPool& pool,
        Fn&& fn,
        [[maybe_unused]] IndexSequence<ArgsInds...> argsIndices,
        [[maybe_unused]] IndexSequence<RequiredInds...> requiredIndices,
        [[maybe_unused]] IndexSequence<OptionalInds...> optionalIndices,
        Params&&... params
    ) noexcept {
        [[maybe_unused]]
        constexpr usize ARGS_COUNT = sizeof...(ArgsInds);

        constexpr usize REQUIRED_COUNT = sizeof...(RequiredInds);
        constexpr usize OPTIONAL_COUNT = sizeof...(OptionalInds);

        auto argsStorages = forward_as_tuple(
            storageManager.getStorage<RemovePointerType<RemoveReferenceType<TupleElementType<ArgsInds, ArgsTpl>>>>()...
        );
        Array<PolymorphicStorage*, OPTIONAL_COUNT> optionalStorages;
        populateOptionalArray<ArgsTpl, ArgsInds...>(optionalStorages);
        if constexpr (REQUIRED_COUNT > 0) {
            Array<PolymorphicStorage*, REQUIRED_COUNT> requiredStorages = {};
            populateRequiredArray<ArgsTpl, ArgsInds...>(requiredStorages);
            PolymorphicStorage* smallest = *stdx::ranges::min_element(
                requiredStorages,
                [](PolymorphicStorage* a, PolymorphicStorage* b) -> bool {
                    return a->getOccupied() < b->getOccupied();
                }
            );
            pool.execTask(
                [&](usize start, usize end) -> void {
                    apply(
                        [&](auto&&... storages) -> void {
                            for (usize i: IotaView(start, end)) {
                                EntityId id = smallest->get(i);
                                if ((requiredStorages[RequiredInds]->has(id) && ...)) {
                                    fn(
                                        id,
                                        stdx::util::forward<Params>(params)...,
                                        storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                                    );
                                }
                            }
                        },
                        argsStorages
                    );
                },
                smallest->getOccupied()
            );
        } else {
            pool.execTask(
                [&](usize start, usize end) -> void {
                    apply(
                        [&](auto&&... storages) -> void {
                            for (usize i: IotaView(start, end)) {
                                EntityId id = entityManager[i];
                                fn(
                                    id,
                                    stdx::util::forward<Params>(params)...,
                                    storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                                );
                            }
                        },
                        argsStorages
                    );
                },
                entityManager.getOccupied()
            );
        }
    }

    /**
     * @brief Core implementation for single-entity queries.
     * 
     * Executes a query function on a specific entity if it matches the required
     * component criteria.
     * 
     * @tparam Fn The query function type.
     * @tparam ArgsTpl Tuple of component argument types.
     * @tparam ArgsInds Index sequence for all arguments.
     * @tparam RequiredInds Index sequence for required components.
     * @tparam OptionalInds Index sequence for optional components.
     * @tparam Params Fallthrough parameter types.
     * @param id The entity ID to query.
     * @param fn The query function to execute.
     * @param argsIndices Index sequence for component arguments.
     * @param requiredIndices Index sequence for required components.
     * @param optionalIndices Index sequence for optional components.
     * @param params Fallthrough parameters forwarded to the query function.
     */
    template <typename Fn, typename ArgsTpl, usize... ArgsInds, usize... RequiredInds, usize... OptionalInds, typename... Params>
    void queryWithImpl(
        EntityId id,
        Fn&& fn,
        [[maybe_unused]] IndexSequence<ArgsInds...> argsIndices,
        [[maybe_unused]] IndexSequence<RequiredInds...> requiredIndices,
        [[maybe_unused]] IndexSequence<OptionalInds...> optionalIndices,
        Params&&... params
    ) noexcept {
        [[maybe_unused]]
        constexpr usize ARGS_COUNT = sizeof...(ArgsInds);

        constexpr usize REQUIRED_COUNT = sizeof...(RequiredInds);
        constexpr usize OPTIONAL_COUNT = sizeof...(OptionalInds);

        auto argsStorages = forward_as_tuple(
            storageManager.getStorage<RemovePointerType<RemoveReferenceType<TupleElementType<ArgsInds, ArgsTpl>>>>()...
        );
        Array<PolymorphicStorage*, OPTIONAL_COUNT> optionalStorages;
        populateOptionalArray<ArgsTpl, ArgsInds...>(optionalStorages);
        if constexpr (REQUIRED_COUNT > 0) {
            Array<PolymorphicStorage*, REQUIRED_COUNT> requiredStorages = {};
            populateRequiredArray<ArgsTpl, ArgsInds...>(requiredStorages);
            apply(
                [&](auto&&... storages) -> void {
                    if ((requiredStorages[RequiredInds]->has(id) && ...))  {
                        fn(
                            stdx::util::forward<Params>(params)...,
                            storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                        );
                    }
                },
                argsStorages
            );
        } else {
            apply(
                [&](auto&&... storages) -> void {
                    fn(
                        stdx::util::forward<Params>(params)...,
                        storages.template getDefer<TupleElementType<ArgsInds, ArgsTpl>>(id)...
                    );
                },
                argsStorages
            );
        }
    }
public:
    GETTER(u32, Capacity, capacity);
    GETTER(u32, QueryLevel, queryLevel);

    /**
     * @brief Constructs a new Registry with the specified capacity.
     * 
     * Initialises both the EntityManager and StorageManager with the given capacity.
     * 
     * @param capacity The maximum number of entities that can exist simultaneously.
     */
    explicit Registry(u32 capacity):
        entityManager(capacity), 
        storageManager(capacity),
        capacity{capacity} {}

    /**
     * @brief Destroys the Registry.
     * 
     * Clears all entities and components before destruction.
     */
    ~Registry() {
        clear();
    }

    Registry(const Registry& other) = default;
    Registry(Registry&& other) = default;
    Registry& operator=(const Registry& other) = default;
    Registry& operator=(Registry&& other) = default;

    /**
     * @brief Clears all entities and components from the registry.
     * 
     * Removes all entities and their components, resetting the registry to its
     * initial state while preserving capacity.
     */
    void clear() noexcept {
        entityManager.clear();
        storageManager.clear();
    }

    /**
     * @brief Creates a new entity with the specified components.
     * 
     * Creates an entity and immediately adds all provided components to it.
     * If no components are provided, creates an empty entity.
     * 
     * @tparam Args Component types.
     * @param args Component values to add to the entity.
     * @return Optional<EntityId> The new entity ID, or nullopt if capacity is reached.
     */
    template <ValidComponent... Args>
    [[nodiscard]]
    Optional<EntityId> entity(Args... args) noexcept {
        Optional<EntityId> id = entityManager.createEntity();
        if (!id.has_value()) {
            return nullopt;
        }
        (emplace<Args>(*id, stdx::util::forward<Args>(args)), ...);
        return id;
    }

    /**
     * @brief Adds or replaces a component on an entity.
     * 
     * Constructs a component of type T in-place for the specified entity.
     * If the entity already has this component, it is replaced.
     * 
     * @tparam T The component type.
     * @tparam Args Constructor argument types.
     * @param id The entity ID to add the component to.
     * @param args Constructor arguments forwarded to T's constructor.
     * @return T& Reference to the newly constructed component.
     */
    template <ValidComponent T, typename... Args>
        requires ConstructibleFrom<T, Args...>
    T& emplace(EntityId id, Args&&... args) noexcept {
        return storageManager.emplace<T>(id, stdx::util::forward<Args>(args)...);
    }

    /**
     * @brief Removes one or more components from an entity.
     * 
     * Removes all specified component types from the entity. If the entity
     * does not have a component, it is silently ignored.
     * 
     * @tparam Args Component types to remove.
     * @param id The entity ID to remove components from.
     */
    template <ValidComponent... Args>
    void erase(EntityId id) noexcept {
        storageManager.erase<Args...>(id);
    }

    /**
     * @brief Checks if an entity has all specified components.
     * 
     * Returns true only if the entity has every component type listed.
     * 
     * @tparam Args Component types to check for.
     * @param id The entity ID to check.
     * @return bool True if the entity has all specified components, false otherwise.
     */
    template <ValidComponent... Args>
    [[nodiscard]]
    bool has(EntityId id) noexcept {
        return storageManager.has<Args...>(id);
    }

    /**
     * @brief Retrieves a reference to a component.
     * 
     * Returns a reference to the component of type T on the specified entity.
     * 
     * @tparam T The component type.
     * @param id The entity ID to get the component from.
     * @return T& Reference to the component.
     */
    template <ValidComponent T>
    [[nodiscard]]
    T& get(EntityId id) noexcept {
        return storageManager.get<T>(id);
    }

    /**
     * @brief Safely retrieves a pointer to a component.
     * 
     * Returns a pointer to the component if it exists and the entity is alive,
     * or nullptr otherwise.
     * 
     * @tparam T The component type.
     * @param id The entity ID to get the component from.
     * @return T* Pointer to the component, or nullptr if not present or entity is dead.
     */
    template <ValidComponent T>
    [[nodiscard]]
    T* getIf(EntityId id) noexcept {
        return entityManager.alive(id)
            ? storageManager.getIf<T>(id)
            : nullptr;
    }

    /**
     * @brief Copies specific components from one entity to another.
     * 
     * Copy-constructs the specified components from the source entity to the
     * destination entity. All component types must be copyable.
     * 
     * @tparam Args Component types to copy.
     * @param from The source entity ID.
     * @param to The destination entity ID.
     */
    template <ValidComponent... Args>
        requires (Copyable<Args> && ...)
    void copy(EntityId from, EntityId to) noexcept {
        storageManager.copy<Args...>(from, to);
    }

    /**
     * @brief Moves specific components from one entity to another.
     * 
     * Move-constructs the specified components from the source entity to the
     * destination entity, then removes them from the source. All component types
     * must be movable.
     * 
     * @tparam Args Component types to move.
     * @param from The source entity ID.
     * @param to The destination entity ID.
     */
    template <ValidComponent... Args>
        requires (Movable<Args> && ...)
    void move(EntityId from, EntityId to) noexcept {
        storageManager.move<Args...>(from, to);
    }

    /**
     * @brief Clones an entity into a new entity.
     * 
     * Creates a new entity and copies all components from the source entity.
     * This is a deep copy that preserves all component data.
     * 
     * @param from The entity ID to clone.
     * @return Optional<EntityId> The new cloned entity ID, or nullopt if capacity is reached.
     */
    [[nodiscard]]
    Optional<EntityId> clone(EntityId from) noexcept {
        Optional<EntityId> id = entity();
        if (!id.has_value()) {
            return nullopt;
        }
        for (StorageId s: storageManager) {
            storageManager.getStorage(s).copy(from, *id);
        }
        return id;
    }

    /**
     * @brief Clones an entity's components onto an existing entity.
     * 
     * Copies all components from the source entity to the destination entity,
     * overwriting any existing components on the destination.
     * 
     * @param from The source entity ID to clone from.
     * @param to The destination entity ID to overwrite.
     */
    void clone(EntityId from, EntityId to) noexcept {
        for (StorageId s: storageManager) {
            storageManager.getStorage(s).copy(from, to);
        }
    }

    /**
     * @brief Destroys an entity and removes all its components.
     * 
     * Removes all components from the entity (triggering destroy callbacks) and
     * marks the entity ID as free for reuse. If the entity is already dead, does nothing.
     * 
     * @param id The entity ID to destroy.
     */
    void destroy(EntityId id) noexcept {
        if (entityManager.alive(id)) {
            for (StorageId s: storageManager) {
                storageManager.getStorage(s).erase(id);
            }
            entityManager.remove(id);
        }
    }

    /**
     * @brief Checks if an entity is currently alive.
     * 
     * Returns true if the optional contains a value and the entity ID is alive.
     * 
     * @param id The optional entity ID to check.
     * @return bool True if the entity exists and is alive, false otherwise.
     */
    [[nodiscard]]
    bool alive(Optional<EntityId> id) noexcept {
        return id.has_value() ? entityManager.alive(*id) : false;
    }

    /**
     * @brief Checks if an entity ID is valid.
     * 
     * Returns true if the optional contains a value and the ID is within capacity.
     * This does not check if the entity is alive, only if the ID is valid.
     * 
     * @param id The optional entity ID to validate.
     * @return bool True if the ID is valid, false otherwise.
     */
    [[nodiscard]]
    bool valid(Optional<EntityId> id) noexcept {
        return id.has_value() || *id < capacity;
    }

    /**
     * @brief Registers a callback invoked when a component is added to an entity.
     * 
     * The callback receives the entity ID and a reference to the newly constructed
     * component. The component type is deduced from the callback's second parameter.
     * 
     * @tparam Fn A callable type with signature (EntityId, T&).
     * @param fn The callback function to register.
     */
    template <typename Fn>
        requires EnsureEntityId<Fn, 0>
    void onConstruct(Fn&& fn) {
        using FnTraits = FunctionTraits<Fn>;
        using SecondArg = typename FnTraits::template ArgumentAt<1>;
        storageManager.getStorage<RemoveConstVolatileReferenceType<SecondArg>>().setOnConstruct(stdx::util::forward<Fn>(fn));
    }

    /**
     * @brief Registers a callback invoked when a component is removed from an entity.
     * 
     * The callback receives the entity ID and a reference to the component being
     * destroyed. The component type is deduced from the callback's second parameter.
     * 
     * @tparam Fn A callable type with signature (EntityId, T&).
     * @param fn The callback function to register.
     */
    template <typename Fn>
        requires EnsureEntityId<Fn, 0>
    void onDestroy(Fn&& fn) {
        using FnTraits = FunctionTraits<Fn>;
        using SecondArg = typename FnTraits::template ArgumentAt<1>;
        storageManager.getStorage<RemoveConstVolatileReferenceType<SecondArg>>().setOnDestroy(stdx::util::forward<Fn>(fn));
    }

    /**
     * @brief Pre-registers component types without allocating storage.
     * 
     * Ensures that IDs are assigned for the specified component types. Useful for
     * batch registration or ensuring deterministic component IDs.
     * 
     * @tparam Args Component types to register.
     */
    template <ValidComponent... Args>
    void ensure() noexcept {
        storageManager.ensure<Args...>();
    }

    /**
     * @brief Queries component metadata for a specific entity.
     * 
     * Invokes the callback for each component type present on the specified entity,
     * passing ComponentTypeInfo (size and alignment) for each.
     * 
     * @tparam Fn A callable type with signature (Params..., ComponentTypeInfo).
     * @tparam Params Fallthrough parameter types.
     * @param id The entity ID to query.
     * @param fn The callback function to invoke for each component.
     * @param params Additional parameters forwarded to the callback.
     */
    template <typename Fn, typename... Params>
        requires EnsureComponentTypeInfo<Fn, 0> && EnsureFallthroughParameters<Fn, 1, Params...>
    void queryInfoWith(EntityId id, Fn&& fn, Params&&... params) noexcept {
        if (entityManager.alive(id)) {
            for (StorageId s: storageManager) {
                PolymorphicStorage& storage = storageManager.getStorage(s);
                if (storage.has(id)) {
                    stdx::util::forward<Fn>(fn)(stdx::util::forward<Params>(params)..., storage.getTypeInfo());
                }
            }
        }
    }

    /**
     * @brief Queries component metadata for all entities.
     * 
     * Invokes the callback for each entity-component pair, passing the entity ID
     * and ComponentTypeInfo for each component.
     * 
     * @tparam Fn A callable type with signature (EntityId, Params..., ComponentTypeInfo).
     * @tparam Params Fallthrough parameter types.
     * @param fn The callback function to invoke.
     * @param params Additional parameters forwarded to the callback.
     */
    template <typename Fn, typename... Params>
        requires EnsureEntityId<Fn, 0> && EnsureComponentTypeInfo<Fn, 1> && EnsureFallthroughParameters<Fn, 2, Params...>
    void queryInfo(Fn&& fn, Params&&... params) noexcept {
        ++queryLevel;
        for (EntityId e: entityManager) {
            for (StorageId s: storageManager) {
                PolymorphicStorage& storage = storageManager.getStorage(s);
                if (storage.has(e)) {
                    stdx::util::forward<Fn>(fn)(e, stdx::util::forward<Params>(params)..., storage.getTypeInfo());
                }
            }
        }
        --queryLevel;
    }

    /**
     * @brief Iterates over entities matching the query parameters.
     * 
     * Automatically deduces required and optional components from the function signature:
     * - Non-pointer references (T&, const T&) are required components
     * - Pointer parameters (T*) are optional components (nullptr if missing)
     * - Leading parameters are Fallthrough values passed from params
     * - Optional first parameter EntityId receives the entity ID
     * 
     * @tparam Fn A callable type with parameters: [Params...] [EntityId] [Components...]
     * @tparam Params Fallthrough parameter types.
     * @param fn The query function to execute for each matching entity.
     * @param params Additional parameters forwarded to the query function.
     */
    template <typename Fn, typename... Params>
        requires EnsureFallthroughParameters<Fn, 0, Params...>
    void query(Fn&& fn, Params&&... params) noexcept {
        using QrTraits = QueryTraits<Fn, 0, Params...>;
        ++queryLevel;
        if constexpr (QrTraits::IS_EMPTY) {
            for ([[maybe_unused]] EntityId _: entityManager) {
                stdx::util::forward<Fn>(fn)(stdx::util::forward<Params>(params)...);
            }
        } else {
            if constexpr (QrTraits::PASSES_ENTITY_ID) {
                querySelfImpl<Fn, typename QrTraits::NO_PARAMS_ARGS_COUNT>(
                    stdx::util::forward<Fn>(fn),
                    make_index_sequence<QrTraits::NO_PARAMS_ARGS_COUNT>{},
                    make_index_sequence<QrTraits::REQUIRED_COUNT>{},
                    make_index_sequence<QrTraits::OPTIONAL_COUNT>{},
                    stdx::util::forward<Params>(params)...
                );
            } else {
                queryImpl<Fn, typename QrTraits::NoParamsNoConstVolatileArgsTuple>(
                    stdx::util::forward<Fn>(fn),
                    make_index_sequence<QrTraits::NO_PARAMS_ARGS_COUNT>{},
                    make_index_sequence<QrTraits::REQUIRED_COUNT>{},
                    make_index_sequence<QrTraits::OPTIONAL_COUNT>{},
                    stdx::util::forward<Params>(params)...
                );
            }
        }
        --queryLevel;
    }

    /**
     * @brief Iterates over entities in parallel using a thread pool.
     * 
     * Identical to query() but distributes work across worker threads for better
     * performance on large datasets. The query function must be thread-safe.
     * 
     * @tparam Fn A callable type with parameters: [Params...] [EntityId] [Components...]
     * @tparam Params Fallthrough parameter types.
     * @param pool The thread pool to use for parallel execution.
     * @param fn The query function to execute for each matching entity.
     * @param params Additional parameters forwarded to the query function.
     * 
     * @warning The query function must be thread-safe as it will be invoked
     *          concurrently from multiple threads.
     */
    template <typename Fn, typename... Params>
        requires EnsureFallthroughParameters<Fn, 0, Params...>
    void queryParallel(ThreadPool& pool, Fn&& fn, Params&&... params) noexcept {
        parallelQueryRunning = true;
        ++queryLevel;
        using QrTraits = QueryTraits<Fn, 0, Params...>;
        if constexpr (QrTraits::IS_EMPTY) {
            pool.execTask(
                [&](usize start, usize end) -> void {
                    for ([[maybe_unused]] usize _: IotaView(start, end)) {
                        fn(stdx::util::forward<Params>(params)...);
                    }
                },
                entityManager.getOccupied()
            );
        } else if constexpr (QrTraits::PASSES_ENTITY_ID) {
            querySelfParallelImpl<Fn, typename QrTraits::NoParamsNoConstVolatileArgsTuple>(
                pool,
                stdx::util::forward<Fn>(fn),
                make_index_sequence<QrTraits::NO_PARAMS_ARGS_COUNT>{},
                make_index_sequence<QrTraits::REQUIRED_COUNT>{},
                make_index_sequence<QrTraits::OPTIONAL_COUNT>{},
                stdx::util::forward<Params>(params)...
            );
        } else {
            queryParallelImpl<Fn, typename QrTraits::NoParamsNoConstVolatileArgsTuple>(
                pool,
                stdx::util::forward<Fn>(fn),
                make_index_sequence<QrTraits::NO_PARAMS_ARGS_COUNT>{},
                make_index_sequence<QrTraits::REQUIRED_COUNT>{},
                make_index_sequence<QrTraits::OPTIONAL_COUNT>{},
                stdx::util::forward<Params>(params)...
            );
        }
        --queryLevel;
        parallelQueryRunning = false;
    }

    /**
     * @brief Executes a query on a single specific entity.
     * 
     * Similar to query() but operates on only one entity. The query function is
     * invoked only if the entity is alive and matches the required components.
     * 
     * @tparam Fn A callable type with parameters: [Params...] [Components...]
     * @tparam Params Fallthrough parameter types.
     * @param id The entity ID to query.
     * @param fn The query function to execute.
     * @param params Additional parameters forwarded to the query function.
     */
    template <typename Fn, typename... Params>
        requires EnsureFallthroughParameters<Fn, 0, Params...>
    void queryWith(EntityId id, Fn fn, Params&&... params) noexcept {
        ++queryLevel;
        using QrTraits = QueryTraits<Fn, 0, Params...>;
        if (entityManager.alive(id)) {
            if constexpr (QrTraits::ARGS_COUNT == QrTraits::PARAMS_COUNT) {
                fn(stdx::util::forward<Params>(params)...);
            } else {
                queryWithImpl<Fn, typename QrTraits::NoParamsNoConstVolatileArgsTuple>(
                    id,
                    stdx::util::forward<Fn>(fn),
                    make_index_sequence<QrTraits::NO_PARAMS_ARGS_COUNT>{},
                    make_index_sequence<QrTraits::REQUIRED_COUNT>{},
                    make_index_sequence<QrTraits::OPTIONAL_COUNT>{},
                    stdx::util::forward<Params>(params)...
                );
            }
        }
        --queryLevel;
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::game::ecs::Registry;

template <>
struct Formatter<Registry::Error> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(Registry::Error err, FormatContext& ctx) {
        StringView msg;
        switch (err) {
            case Registry::Error::ENTITY_CREATE_FAILURE:
                msg = "Failed to create registry entity";
            default:
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", msg);
    }
};

SPECIALISE_FORMATTER(Registry::Error);
