/**
 * @file StorageManager.cppm
 * @module openjuice.engine.game.ecs:StorageManager
 * @brief Module of the ECS registry.
 *
 * This file contains the definitions for the ECS registry.
 * Based on kawa_ecs (https://github.com/superPuero/kawa_ecs)
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs:StorageManager;

import stdx;

import :Meta;
import :PolymorphicStorage;
import :ThreadPool;

using stdx::mem::UniquePointer;
using stdx::meta::RemoveConstVolatileReferenceType;
using stdx::ranges::IotaView;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @class StorageManager
 * @brief Manages component storage for an Entity Component System (ECS).
 * 
 * The StorageManager is responsible for storing and managing all component types
 * in the ECS. It uses a sparse set architecture with polymorphic storage containers
 * to handle different component types efficiently. Each component type is assigned
 * a unique ID, and components are stored in type-erased storage arrays.
 * 
 * The manager maintains:
 * - A dense array of active entity IDs (entries)
 * - A sparse array mapping entity IDs to dense indices (indices)
 * - A mask tracking which component types are registered
 * - Polymorphic storage containers for each component type
 * 
 * @note This class uses a global static counter for component type IDs that is
 * shared across all StorageManager instances.
 */
export class StorageManager {
private:
    static inline u32 idCount = 0; ///< Global counter for assigning unique IDs to component types (shared across all instances).
    UniquePointer<PolymorphicStorage[]> storages; ///< Array of polymorphic storage containers, one per component type.
    UniquePointer<bool[]> mask; ///< Boolean mask tracking which component types are registered/active.
    UniquePointer<StorageId[]> entries; ///< Dense array of active component type IDs.
    UniquePointer<u32[]> indices; ///< Sparse array mapping component type IDs to dense array indices.
    u32 capacity = 512; ///< The maximum number of component types that can be registered.
    u32 storageCapacity = 0; ///< The highest component type ID ever allocated.
    u32 entryCount = 0; ///< The number of registered component types currently active.

    /**
     * @brief Retrieves a unique global ID for a component type.
     * @tparam T The component type to get an ID for.
     * @return StorageId The unique ID for component type T.
     *
     * Uses a static local variable to ensure each component type T gets a unique,
     * persistent ID that remains the same across calls. The ID is assigned on first
     * access and cached for subsequent calls.
     */
    template <typename T>
    [[nodiscard]]
    StorageId getIdInternal() noexcept {
        static StorageId id = idCount++;
        return id;
    }

    /**
     * @brief Updates the bidirectional mapping between storage ID and dense array index.
     * @param id The component type ID (sparse array index).
     * @param index The position in the dense array (entries).
     *
     * Maintains the sparse-set invariant by updating both the dense array (entries)
     * and the sparse array (indices) to create a bidirectional mapping.
     */
    void setEntriesTableId(StorageId id, u32 index) noexcept {
        entries[index] = id;
        indices[id] = index;
    }
public:
    /**
     * @brief Constructs a new StorageManager instance.
     * @param capacity The maximum number of component types that can be registered.
     * Defaults to 512 if not specified.
     *
     * Allocates arrays for storing component types, tracking active types,
     * and maintaining the sparse-set data structure.
     */
    explicit StorageManager(u32 capacity):
        storages{Pointers::unique<PolymorphicStorage[]>(capacity)},
        mask{Pointers::unique<bool[]>(capacity)},
        entries{Pointers::unique<StorageId[]>(capacity)},
        indices{Pointers::unique<u32[]>(capacity)},
        capacity{capacity} {}

    /**
     * @brief Destroys the StorageManager instance.
     * 
     * Releases all allocated storage arrays and component data.
     * Automatically called when the StorageManager goes out of scope.
     */
    ~StorageManager() {
        storages.reset();
        mask.reset();
        entries.reset();
        indices.reset();
    }

    /**
     * @brief Copy constructor for StorageManager.
     * @param other The StorageManager instance to copy from.
     *
     * Performs a deep copy of all storage arrays and component data from another
     * StorageManager instance.
     */
    StorageManager(const StorageManager& other):
        storages{Pointers::unique<PolymorphicStorage[]>(other.storageCapacity)},
        mask{Pointers::unique<bool[]>(other.storageCapacity)},
        entries{Pointers::unique<StorageId[]>(other.storageCapacity)},
        indices{Pointers::unique<u32[]>(other.storageCapacity)},
        capacity{other.capacity},
        storageCapacity{other.storageCapacity},
        entryCount{other.entryCount} {
        stdx::ranges::copy(Span<PolymorphicStorage>(other.storages.get(), storageCapacity), storages.get());
        stdx::ranges::copy(Span<bool>(other.mask.get(), storageCapacity), mask.get());
        stdx::ranges::copy(Span<StorageId>(other.entries.get(), storageCapacity), entries.get());
        stdx::ranges::copy(Span<u32>(other.indices.get(), storageCapacity), indices.get());
    }

    /**
     * @brief Move constructor for StorageManager.
     * @param other The StorageManager instance to move from.
     *
     * Transfers ownership of all storage arrays and component data from another
     * StorageManager instance, leaving the source in a valid but unspecified state.
     */
    StorageManager(StorageManager&& other):
        storages{Ops::move(other.storages)},
        mask{Ops::move(other.mask)},
        entries{Ops::move(other.entries)},
        indices{Ops::move(other.indices)},
        capacity{other.capacity},
        storageCapacity{other.storageCapacity},
        entryCount{other.entryCount} {}

    /**
     * @brief Copy assignment operator for StorageManager.
     * @param other The StorageManager instance to copy from.
     * @return StorageManager& Reference to this instance.
     *
     * Releases current resources and performs a deep copy of all storage arrays
     * and component data from another StorageManager instance.
     */
    StorageManager& operator=(const StorageManager& other) noexcept {
        if (this != &other) {
            storages.reset();
            mask.reset();
            entries.reset();
            indices.reset();

            capacity = other.capacity;
            storageCapacity = other.storageCapacity;
            entryCount = other.entryCount;

            storages = Pointers::unique<PolymorphicStorage[]>(storageCapacity);
            stdx::ranges::copy(Span<PolymorphicStorage>(other.storages.get(), storageCapacity), storages.get());

            mask = Pointers::unique<bool[]>(storageCapacity);
            stdx::ranges::copy(Span<bool>(other.mask.get(), storageCapacity), mask.get());

            entries = Pointers::unique<StorageId[]>(storageCapacity);
            stdx::ranges::copy(Span<StorageId>(other.entries.get(), storageCapacity), entries.get());

            indices = Pointers::unique<u32[]>(storageCapacity);
            stdx::ranges::copy(Span<u32>(other.indices.get(), storageCapacity), indices.get());
        }
        return *this;
    }

    /**
     * @brief Move assignment operator for StorageManager.
     * @param other The StorageManager instance to move from.
     * @return StorageManager& Reference to this instance.
     *
     * Releases current resources and transfers ownership of all storage arrays
     * and component data from another StorageManager instance.
     */
    StorageManager& operator=(StorageManager&& other) noexcept {
        if (this != &other) {
            storages.reset();
            mask.reset();
            entries.reset();
            indices.reset();

            capacity = other.capacity;
            storages = Ops::move(other.storages);
            storageCapacity = other.storageCapacity;
            mask = Ops::move(other.mask);
            entries = Ops::move(other.entries);
            indices = Ops::move(other.indices);
            entryCount = other.entryCount;
        }
        return *this;
    }

    /**
     * @brief Returns an iterator to the beginning of active component type IDs.
     * @return StorageId* Pointer to the first element in the dense entries array.
     */
    StorageId* begin() noexcept {
        return entries.get();
    }

    /**
     * @brief Returns an iterator to the end of active component type IDs.
     * @return StorageId* Pointer to one past the last element in the dense entries array.
     */
    StorageId* end() noexcept {
        return entries.get() + entryCount;
    }

    /**
     * @brief Clears all component data and resets the StorageManager.
     *
     * Removes all components from all storages and resets the active component
     * type tracking, but does not deallocate the underlying storage capacity.
     */
    void clear() noexcept {
        stdx::ranges::fill(Span<bool>(mask.get(), capacity), false);
        for (u32 i: IotaView(0u, entryCount)) {
            storages[entries[i]].clear();
        }
        entryCount = 0;
    }

    /**
     * @brief Retrieves the unique ID for a component type.
     * @tparam T The component type to get an ID for.
     * @return StorageId The unique ID for the component type.
     *
     * Strips const, volatile, and reference qualifiers from T before retrieving
     * the ID to ensure consistent IDs for equivalent types.
     */
    template <typename T>
    [[nodiscard]]
    StorageId getId() noexcept {
        return getIdInternal<RemoveConstVolatileReferenceType<T>>();
    }

    [[nodiscard]]
    u32 getCapacity() const noexcept {
        return capacity;
    }

    [[nodiscard]]
    u32 getEntryCount() const noexcept {
        return entryCount;
    }

    /**
     * @brief Pre-registers multiple component types.
     * @tparam Args The component types to ensure are registered.
     *
     * Ensures that IDs are assigned for all specified component types without
     * necessarily allocating storage. Useful for batch registration.
     */
    template <typename... Args>
    void ensure() noexcept {
        (getId<Args>(), ...);
    }

    /**
     * @brief Constructs and emplaces a component in-place.
     * @tparam T The component type to emplace.
     * @tparam Args The types of constructor arguments.
     * @param index The entity index where the component should be stored.
     * @param args Constructor arguments forwarded to T's constructor.
     * @return T& Reference to the newly constructed component.
     *
     * Creates a component of type T at the specified entity index using the
     * provided constructor arguments. If storage for T does not exist, it is
     * created automatically.
     */
    template <typename T, typename... Args>
    T& emplace(u32 index, Args... args) noexcept {
        PolymorphicStorage& storage = getStorage<T>();
        return storage.emplace<T>(index, Ops::forward<Args>(args)...);
    }

    /**
     * @brief Removes components from an entity.
     * @tparam Args The component types to remove.
     * @param index The entity index to remove components from.
     *
     * Erases all specified component types from the entity at the given index.
     * If a component does not exist, it is silently ignored.
     */
    template <typename... Args>
    void erase(u32 index) noexcept {
        (getStorage<Args>().erase(index), ...);
    }

    /**
     * @brief Checks if an entity has all specified components.
     * @tparam Args The component types to check for.
     * @param index The entity index to check.
     * @return bool True if the entity has all specified components, false otherwise.
     *
     * Returns true only if the entity at the given index has all component
     * types specified in Args.
     */
    template <typename... Args>
    [[nodiscard]]
    bool has(u32 index) noexcept {
        return (getStorage<Args>().has(index) && ...);
    }

    /**
     * @brief Retrieves a reference to a component.
     * @tparam T The component type to retrieve.
     * @param index The entity index to get the component from.
     * @return T& Reference to the component.
     *
     * Returns a reference to the component of type T stored at the specified
     * entity index.
     * 
     * @warning Undefined behavior if the component does not exist. Use has() or getIf().
     */
    template <typename T>
    [[nodiscard]]
    T& get(u32 index) noexcept {
        return getStorage<T>().template get<T>(index);
    }

    /**
     * @brief Safely retrieves a pointer to a component.
     * @tparam T The component type to retrieve.
     * @param index The entity index to get the component from.
     * @return T* Pointer to the component, or nullptr if not present.
     *
     * Returns a pointer to the component of type T if it exists at the specified
     * entity index, or nullptr if it doesn't exist.
     */
    template <typename T>
    [[nodiscard]]
    T* getIf(u32 index) noexcept {
        return getStorage<T>().template getIf<T>(index);
    }

    /**
     * @brief Copies components from one entity to another.
     * @tparam Args The component types to copy.
     * @param from The source entity index.
     * @param to The destination entity index.
     *
     * Creates copies of all specified component types from the source entity
     * to the destination entity. If components do not exist on the source,
     * behavior is undefined.
     *
     * @note If from == to, no operation is performed.
     */
    template <typename... Args>
    void copy(u32 from, u32 to) noexcept {
        if (from != to) {
            (getStorage<Args>().copy(from, to), ...);
        }
    }

    /**
     * @brief Moves components from one entity to another.
     * @tparam Args The component types to move.
     * @param from The source entity index.
     * @param to The destination entity index.
     *
     * Transfers ownership of all specified component types from the source entity
     * to the destination entity, leaving the source in a valid but unspecified state.
     *
     * @note If from == to, no operation is performed.
     */
    template <typename... Args>
    void move(u32 from, u32 to) noexcept {
        if (from != to) {
            (getStorage<Args>().move(from, to), ...);
        }
    }

    /**
     * @brief Checks if a component type is registered/active.
     * @param id The component type ID to check.
     * @return bool True if the component type is registered, false otherwise.
     *
     * Determines whether storage has been allocated for the component type
     * with the given ID.
     */
    [[nodiscard]]
    bool alive(StorageId id) noexcept {
        return mask[id];
    }

    /**
     * @brief Retrieves or creates storage for a component type.
     * @tparam T The component type to get storage for.
     * @return PolymorphicStorage& Reference to the storage container for type T.
     *
     * Gets the polymorphic storage container for component type T. If storage
     * does not exist, it is created and registered automatically.
     */
    template <typename T>
    [[nodiscard]]
    PolymorphicStorage& getStorage() noexcept {
        StorageId id = getId<T>();
        PolymorphicStorage& storage = storages[id];
        bool& cell = mask[id];
        if (!cell) {
            storage.populate<T>(capacity);
            cell = true;
            u32 next = entryCount++;
            setEntriesTableId(next, id);
        }
        return storage;
    }

    /**
     * @brief Retrieves storage by component type ID.
     * @param id The component type ID.
     * @return PolymorphicStorage& Reference to the storage container.
     *
     * Gets the polymorphic storage container for the given component type ID.
     */
    [[nodiscard]]
    PolymorphicStorage& getStorage(StorageId id) noexcept {
        return storages[id];
    }

    /**
     * @brief Returns the number of registered component types.
     * @return u32 The number of active component types.
     *
     * Provides the count of component types that have been registered and
     * have allocated storage.
     */
    [[nodiscard]]
    u32 occupied() noexcept {
        return getEntryCount();
    }
};

END_MODULE_NAMESPACE();
