/**
 * @file PolymorphicStorage.cppm
 * @module openjuice.engine.game.ecs.PolymorphicStorage
 * @brief Module of the polymorphic storage class.
 *
 * This file contains the definitions for the polymorphic storage class.
 * Based on kawa_ecs (https://github.com/superPuero/kawa_ecs)
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs.PolymorphicStorage;

import std;

import openjuice.engine.game.ecs.Meta;

using std::mem::AlignValue;
using std::mem::UniquePointer;
using std::meta::EnableIfType;
using std::meta::IsCopyConstructibleValue;
using std::meta::IsEmptyValue;
using std::meta::IsMoveConstructibleValue;
using std::meta::IsPointerValue;
using std::meta::RemoveReferenceType;

using openjuice::engine::game::ecs::meta::ComponentTypeInfo;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @class PolymorphicStorage
 * @brief Type-erased storage container for ECS components.
 * 
 * PolymorphicStorage provides a generic, type-erased storage mechanism for components
 * of any type. It uses a sparse-set architecture with raw memory allocation and
 * function pointers to achieve polymorphic behavior without virtual functions.
 * 
 * @note This class must be populated with a concrete type via populate<T>() before use.
 */
export class PolymorphicStorage {
private:
    using DeleteFunction = void(*)(void*); ///< Function pointer type for deallocating storage with proper alignment.
    using EraseFunction = void(*)(void*, u32); ///< Function pointer type for calling destructor on a component at an index.
    using CopyFunction = void(*)(void*, void*, u32, u32); ///< Function pointer type for copy-constructing a component from one index to another.
    using MoveFunction = void(*)(void*, void*, u32, u32); ///< Function pointer type for move-constructing a component from one index to another.
    using HandlerInvokeFunction = void(*)(void*, void*, EntityId); ///< Function pointer type for invoking type-erased callbacks with entity and component.
    using CopyHandlerFunction = void(*)(void*, void*&); ///< Function pointer type for deep-copying a callback function object.

    UniquePointer<bool[]> mask; ///< Boolean mask tracking which entity IDs have components in this storage.
    UniquePointer<EntityId[]> connector; ///< Dense array of entity IDs that have components in this storage.
    UniquePointer<u32[]> indices; ///< Sparse array mapping entity IDs to their dense array indices.
    void* storage = nullptr; ///< Raw memory buffer containing the actual component data, indexed by entity ID.
    void* onConstructFn = nullptr; ///< Type-erased callable invoked when a component is created.
    void* onDestroyFn = nullptr; ///< Type-erased callable invoked when a component is destroyed.
    EraseFunction eraseFn = nullptr; ///< Function pointer that calls the component destructor.
    DeleteFunction deleteFn = nullptr; ///< Function pointer that deallocates the storage buffer with proper alignment.
    CopyFunction copyFn = nullptr; ///< Function pointer that copy-constructs a component from one index to another.
    MoveFunction moveFn = nullptr; ///< Function pointer that move-constructs a component from one index to another.
    HandlerInvokeFunction onConstructInvokeFn = nullptr; ///< Function pointer to invoke the construct callback.
    HandlerInvokeFunction onDestroyInvokeFn = nullptr; ///< Function pointer to invoke the destroy callback.
    CopyHandlerFunction onConstructFunctionCopyFn; ///< Function pointer that deep-copies the construct callback.
    CopyHandlerFunction onDestroyFunctionCopyFn; ///< Function pointer that deep-copies the destroy callback.
    DeleteFunction onConstructDeleteFn; ///< Function pointer that deletes the construct callback.
    DeleteFunction onDestroyDeleteFn; ///< Function pointer that deletes the destroy callback.
    usize size = 0; ///< The size in bytes of each component (0 for empty types).
    AlignValue alignment = AlignValue{0}; ///< The memory alignment requirement of the component type.
    u32 capacity = 0; ///< The maximum number of components that can be stored.
    u32 occupied = 0; ///< The highest entity ID that has ever been stored (includes alive and freed slots).
    bool populated = false; ///< Flag indicating whether the storage has been initialised with a concrete type.

    /**
     * @brief Invokes the construct callback if one is registered.
     * 
     * Called after a component is created to notify observers.
     * 
     * @param id The entity ID that received the new component.
     */
    void onConstruct(EntityId id) noexcept {
        if (onConstructFn) {
            onConstructInvokeFn(onConstructFn, storage, id);
        }
    }

    /**
     * @brief Invokes the destroy callback if one is registered.
     * 
     * Called before a component is destroyed to notify observers.
     * 
     * @param id The entity ID that is losing the component.
     */
    void onDestroy(EntityId id) noexcept {
        if (onDestroyFn) {
            onDestroyInvokeFn(onDestroyFn, storage, id);
        }
    }

    /**
     * @brief Updates the bidirectional mapping between entity ID and dense array index.
     * 
     * Maintains the sparse-set invariant by updating both the dense array (connector)
     * and the sparse array (indices).
     * 
     * @param id The entity ID to map.
     * @param index The position in the dense array.
     */
    void setConnectorTableId(EntityId id, u32 index) noexcept {
        connector[index] = id;
        indices[id] = index;
    }
public:
    /**
     * @brief Default constructor.
     * 
     * Creates an unpopulated storage that must be initialized via populate<T>().
     */
    PolymorphicStorage() = default;

    /**
     * @brief Copy constructor for PolymorphicStorage.
     * 
     * Performs a deep copy of all storage structures and components if the source
     * is populated. Callbacks are also deep-copied if present.
     * 
     * @param other The PolymorphicStorage instance to copy from.
     */
    PolymorphicStorage(const PolymorphicStorage& other):
        mask{other.populated ? std::mem::make_unique<bool[]>(other.capacity) : nullptr},
        connector{other.populated ? std::mem::make_unique<EntityId[]>(other.capacity) : nullptr},
        indices{other.populated ? std::mem::make_unique<u32[]>(other.capacity) : nullptr},
        eraseFn{other.populated ? other.eraseFn : nullptr},
        deleteFn{other.populated ? other.deleteFn : nullptr},
        copyFn{other.populated ? other.copyFn : nullptr},
        moveFn{other.populated ? other.moveFn : nullptr},
        size{other.size},
        alignment{other.alignment},
        capacity{other.capacity},
        occupied{other.occupied},
        populated{other.populated} {
        if (other.populated) {
            if (other.storage) {
                storage = ::operator new(size * capacity, alignment);
            }

            if (other.onConstructFn) {
                onConstructFunctionCopyFn = other.onConstructFunctionCopyFn;
                onConstructFunctionCopyFn(other.onConstructFn, onConstructFn);
                onConstructInvokeFn = other.onConstructInvokeFn;
                onConstructDeleteFn = other.onConstructDeleteFn;
            }

            if (other.onDestroyFn) {
                onDestroyFunctionCopyFn = other.onDestroyFunctionCopyFn;
                onDestroyFunctionCopyFn(other.onDestroyFn, onDestroyFn);
                onDestroyInvokeFn = other.onDestroyInvokeFn;
                onDestroyDeleteFn = other.onDestroyDeleteFn;
            }

            std::ranges::copy(Span<bool>(other.mask.get(), capacity), mask.get());
            std::ranges::copy(Span<EntityId>(other.connector.get(), capacity), connector.get());
            std::ranges::copy(Span<u32>(other.indices.get(), capacity), indices.get());

            for (usize i = 0; i < occupied; ++i) {
                EntityId id = connector[i];
                if (mask[id]) {
                    copyFn(other.storage, storage, id, id);
                }
            }
        }
    }

    /**
     * @brief Move constructor for PolymorphicStorage.
     * 
     * Transfers ownership of all storage structures and components from another
     * PolymorphicStorage instance, leaving the source unpopulated.
     * 
     * @param other The PolymorphicStorage instance to move from.
     */
    PolymorphicStorage(PolymorphicStorage&& other):
        mask{std::util::move(other.mask)},
        connector{std::util::move(other.connector)},
        indices{std::util::move(other.indices)},
        storage{other.storage},
        onConstructFn{other.onConstructFn},
        onDestroyFn{other.onDestroyFn},
        eraseFn{other.eraseFn},
        deleteFn{other.deleteFn},
        copyFn{other.copyFn},
        moveFn{other.moveFn},
        onConstructInvokeFn{other.onConstructInvokeFn},
        onDestroyInvokeFn{other.onDestroyInvokeFn},
        onConstructFunctionCopyFn{other.onConstructFunctionCopyFn},
        onDestroyFunctionCopyFn{other.onDestroyFunctionCopyFn},
        onConstructDeleteFn{other.onConstructDeleteFn},
        onDestroyDeleteFn{other.onDestroyDeleteFn},
        size{other.size},
        alignment{other.alignment},
        capacity{other.capacity},
        occupied{other.occupied},
        populated{other.populated} {
        other.populated = false;
    }

    /**
     * @brief Destroys the PolymorphicStorage.
     * 
     * Calls clear() to properly destroy all components and release resources.
     */
    ~PolymorphicStorage() {
        clear();
    }

    /**
     * @brief Copy assignment operator for PolymorphicStorage.
     * 
     * Clears current contents and performs a deep copy of all storage structures
     * and components from another instance.
     * 
     * @param other The PolymorphicStorage instance to copy from.
     * @return PolymorphicStorage& Reference to this instance.
     */
    PolymorphicStorage& operator=(const PolymorphicStorage& other) noexcept {
        if (this != &other) {
            this->clear();
            if (other.populated) {
                capacity = other.capacity;
                occupied = other.occupied;
                size = other.size;
                alignment = other.alignment;
                if (other.storage) {
                    storage = ::operator new(size * capacity, alignment);
                }

                deleteFn = other.deleteFn;
                eraseFn = other.eraseFn;
                copyFn = other.copyFn;
                moveFn = other.moveFn;

                if (other.onConstructFn) {
                    onConstructFunctionCopyFn = other.onConstructFunctionCopyFn;
                    onConstructFunctionCopyFn(other.onConstructFn, onConstructFn);
                    onConstructInvokeFn = other.onConstructInvokeFn;
                    onConstructDeleteFn = other.onConstructDeleteFn;
                }

                if (other.onDestroyFn) {
                    onDestroyFunctionCopyFn = other.onDestroyFunctionCopyFn;
                    onDestroyFunctionCopyFn(other.onDestroyFn, onDestroyFn);
                    onDestroyInvokeFn = other.onDestroyInvokeFn;
                    onDestroyDeleteFn = other.onDestroyDeleteFn;
                }

                mask = std::mem::make_unique<bool[]>(capacity);
                std::ranges::copy(Span<bool>(other.mask.get(), capacity), mask.get());

                connector = std::mem::make_unique<EntityId[]>(capacity);
                std::ranges::copy(Span<EntityId>(other.connector.get(), capacity), connector.get());

                indices = std::mem::make_unique<u32[]>(capacity);
                std::ranges::copy(Span<u32>(other.indices.get(), capacity), indices.get());

                for (usize i = 0; i < occupied; ++i) {
                    EntityId id = connector[i];
                    if (mask[id]) {
                        copyFn(other.storage, storage, id, id);
                    }
                }
                this->populated = true;
            }
        }
        return *this;
    }

    /**
     * @brief Move assignment operator for PolymorphicStorage.
     * 
     * Clears current contents and transfers ownership of all storage structures
     * and components from another instance.
     * 
     * @param other The PolymorphicStorage instance to move from.
     * @return PolymorphicStorage& Reference to this instance.
     */
    PolymorphicStorage& operator=(PolymorphicStorage&& other) noexcept {
        if (this != &other) {
            this->clear();
            if (other.populated) {
                capacity = other.capacity;
                occupied = other.occupied;
                storage = other.storage;
                size = other.size;
                alignment = other.alignment;
                mask = std::util::move(other.mask);
                connector = std::util::move(other.connector);
                indices = std::util::move(other.indices);
                eraseFn = other.eraseFn;
                deleteFn = other.deleteFn;
                copyFn = other.copyFn;
                moveFn = other.moveFn;
                onConstructFn = other.onConstructFn;
                onDestroyFn = other.onDestroyFn;
                onConstructInvokeFn = other.onConstructInvokeFn;
                onDestroyInvokeFn = other.onDestroyInvokeFn;
                onConstructFunctionCopyFn = other.onConstructFunctionCopyFn;
                onDestroyFunctionCopyFn = other.onDestroyFunctionCopyFn;
                onConstructDeleteFn = other.onConstructDeleteFn;
                onDestroyDeleteFn = other.onDestroyDeleteFn;
                other.populated = false;
                this->populated = true;
            }
        }
        return *this;
    }

    /**
     * @brief Returns an iterator to the beginning of entity IDs with components.
     * 
     * @return EntityId* Pointer to the first element in the dense connector array.
     */
    EntityId* begin() noexcept {
        return connector.get();
    }

    /**
     * @brief Returns an iterator to the end of entity IDs with components.
     * 
     * @return EntityId* Pointer to one past the last element in the dense connector array.
     */
    EntityId* end() noexcept {
        return connector.get() + occupied;
    }

    GETTER(u32, Capacity, capacity);
    GETTER(u32, Occupied, occupied);
    GETTER(usize, Size, size);
    GETTER(AlignValue, Alignment, alignment);

    /**
     * @brief Validates that an entity ID is within storage capacity.
     * 
     * @param id The entity ID to validate.
     * @return bool True if the ID is valid (within capacity), false otherwise.
     */
    [[nodiscard]]
    bool validateIndex(u32 id) const noexcept {
        return id < capacity;
    }

    /**
     * @brief Checks if the storage has been initialized with a concrete type.
     * 
     * @return bool True if populate<T>() has been called, false otherwise.
     */
    [[nodiscard]]
    bool isPopulated() const noexcept {
        return populated;
    }

    /**
     * @brief Checks if a construct callback is registered.
     * 
     * @return bool True if a construct callback is set, false otherwise.
     */
    [[nodiscard]]
    bool hasOnConstruct() const noexcept {
        return onConstructFn;
    }

    /**
     * @brief Checks if a destroy callback is registered.
     * 
     * @return bool True if a destroy callback is set, false otherwise.
     */
    [[nodiscard]]
    bool hasOnDestroy() const noexcept {
        return onDestroyFn;
    }

    /**
     * @brief Registers a callback to be invoked when components are constructed.
     * 
     * The callback receives the entity ID and a reference to the newly constructed
     * component. If a callback is already registered, it is replaced.
     * 
     * @tparam Fn A callable type with signature (EntityId, T&) where T is the component type.
     * @param fn The callback function to register.
     */
    template <typename Fn>
    void setOnConstruct(Fn&& fn) noexcept {
        if (onConstructFn) {
            onConstructDeleteFn(onConstructFn);
        }
        onConstructFn = new Fn(std::util::forward<Fn>(fn));
        onConstructDeleteFn = [](void* fn) -> void {
            delete static_cast<Fn*>(fn);
        };
        onConstructInvokeFn = [](void* fn, void* data, EntityId entity) -> void {
            using T = typename meta::template FunctionTraits<Fn>::template ArgumentAt<1>;
            static_cast<Fn*>(fn)->operator()(entity, *(static_cast<RemoveReferenceType<T>*>(data) + entity));
        };
        onConstructFunctionCopyFn = [](void* from, void*& to) -> void {
            to = new Fn(*static_cast<Fn*>(from));
        };
    }

    /**
     * @brief Registers a callback to be invoked when components are destroyed.
     * 
     * The callback receives the entity ID and a reference to the component being
     * destroyed. If a callback is already registered, it is replaced.
     * 
     * @tparam Fn A callable type with signature (EntityId, T&) where T is the component type.
     * @param fn The callback function to register.
     */
    template <typename Fn>
    void setOnDestroy(Fn&& fn) noexcept {
        if (onDestroyFn) {
            onDestroyDeleteFn(onDestroyFn);
        }
        onDestroyFn = new Fn(std::util::forward<Fn>(fn));
        onDestroyDeleteFn = [](void* fn) -> void {
            delete static_cast<Fn*>(fn);
        };
        onDestroyInvokeFn = [](void* fn, void* data, EntityId entity) -> void {
            using T = typename meta::template FunctionTraits<Fn>::template ArgumentAt<1>;
            static_cast<Fn*>(fn)->operator()(entity, *(static_cast<RemoveReferenceType<T>*>(data) + entity));
        };
        onDestroyFunctionCopyFn = [](void* from, void*& to) -> void {
            to = new Fn(*static_cast<Fn*>(from));
        };
    }

    /**
     * @brief Clears all components and releases storage resources.
     * 
     * Destroys all components (calling destructors and destroy callbacks),
     * deallocates memory, removes callbacks, and resets the storage to an
     * unpopulated state.
     */
    void clear() noexcept {
        if (populated) {
            for (usize i = 0; i < occupied; ++i) {
                onDestroy(connector[i]);
                eraseFn(storage, connector[i]);
            }

            deleteFn(storage);

            if (onConstructFn) {
                onConstructDeleteFn(onConstructFn);
                onConstructFn = nullptr;
            }

            if (onDestroyFn) {
                onDestroyDeleteFn(onDestroyFn);
                onDestroyFn = nullptr;
            }

            mask.reset();
            connector.reset();
            indices.reset();

            populated = false;
        }
    }

    /**
     * @brief Initialises the storage for a specific component type.
     * 
     * Allocates raw memory with proper alignment and sets up function pointers
     * for type-specific operations (construction, destruction, copy, move).
     * Special handling for empty types to minimise memory usage.
     * 
     * @tparam T The component type to store.
     * @param cap The maximum number of components to allocate space for.
     * @return PolymorphicStorage* Pointer to this instance for chaining.
     * 
     * @note Must be called before any other operations on the storage.
     * @note Empty types (sizeof(T) == 0) only allocate a single instance.
     */
    template <typename T>
    PolymorphicStorage* populate(u32 cap) noexcept {
        size = 0;
        alignment = AlignValue{alignof(T)};
        capacity = cap;
        if constexpr (IsEmptyValue<T>) {
            storage = ::operator new(sizeof(T) * 1, alignment);
        } else {
            storage = ::operator new(sizeof(T) * cap, alignment);
        }

        deleteFn = [](void* data) -> void {
            ::operator delete(data, AlignValue{alignof(T)});
        };

        mask = std::mem::make_unique<bool[]>(cap);
        connector = std::mem::make_unique<EntityId[]>(cap);
        indices = std::mem::make_unique<u32[]>(cap);

        eraseFn = [](void* data, u32 index) -> void {
            if constexpr (!IsEmptyValue<T>) {
                (static_cast<T*>(data) + index)->~T();
            } else {
                (static_cast<T*>(data))->~T();
            }
        };

        copyFn = [](void* origin, void* destination, u32 from, u32 to) -> void {
            if constexpr (IsCopyConstructibleValue<T>) {
                new (static_cast<T*>(destination) + to) T(*(static_cast<T*>(origin) + from));
            } else {
                static_assert(false, "Error, trying to copy uncopyable type!");
            }
        };

        moveFn = [](void* origin, void* destination, u32 from, u32 to) -> void {
            if constexpr (IsCopyConstructibleValue<T>) {
                new (static_cast<T*>(destination) + to) T(std::util::move(*(static_cast<T*>(origin) + from)));
            } else {
                static_assert(false, "Error, trying to copy immovable type!");
            }
        };

        populated = true;
        return this;
    }

    /**
     * @brief Checks if an entity has a component in this storage.
     * 
     * @param index The entity ID to check.
     * @return bool True if the entity has a component, false otherwise.
     */
    [[nodiscard]]
    bool has(u32 index) const noexcept {
        return mask[index];
    }

    /**
     * @brief Constructs a component in-place for an entity.
     * 
     * If the entity does not have a component, creates a new one and updates
     * tracking structures. If the entity already has a component, destroys the
     * old one and constructs a new one in its place.
     * 
     * @tparam T The component type.
     * @tparam Args Constructor argument types.
     * @param index The entity ID to emplace the component for.
     * @param args Constructor arguments forwarded to T's constructor.
     * @return T& Reference to the newly constructed component.
     */
    template <typename T, typename... Args>
    T& emplace(u32 index, Args&&... args) noexcept {
        bool& cell = mask[index];
        if (!cell) {
            u32 next = occupied++;
            setConnectorTableId(next, index);
            cell = true;
            T& val = *(new (static_cast<T*>(storage) + index) T(std::util::forward<Args>(args)...));
            onConstruct(index);
            return val;
        } else {
            onDestroy(index);
            eraseFn(storage, index);
            return *(new (static_cast<T*>(storage) + index) T(std::util::forward<Args>(args)...));
        }
    }

    /**
     * @brief Removes a component from an entity.
     * 
     * Calls the destroy callback and destructor, then removes the entity from
     * the dense array using swap-and-pop and updates indices.
     * 
     * @param index The entity ID to remove the component from.
     */
    void erase(u32 index) {
        bool& cell = mask[index];
        if (cell) {
            u32 leftIndex = indices[index];
            onDestroy(index);
            eraseFn(storage, index);
            connector[leftIndex] = connector[--occupied];
            indices[connector[occupied]] = leftIndex;
            cell = false;
        }
    }

    /**
     * @brief Copies a component from one entity to another.
     * 
     * If the destination entity already has a component, it is destroyed first.
     * The source component is copy-constructed at the destination.
     * 
     * @param from The source entity ID.
     * @param to The destination entity ID.
     */
    void copy(u32 from, u32 to) noexcept {
        if (mask[from]) {
            bool& cell = mask[to];
            if (!cell) {
                u32 next = occupied++;
                setConnectorTableId(next, to);
                cell = true;
                copyFn(storage, storage, from, to);
                onConstruct(to);
            } else {
                onDestroy(to);
                eraseFn(storage, to);
                copyFn(storage, storage, from, to);
                onConstruct(to);
            }
        }
    }

    /**
     * @brief Moves a component from one entity to another.
     * 
     * If the destination entity already has a component, it is destroyed first.
     * The source component is move-constructed at the destination, then the
     * source component is destroyed and removed.
     * 
     * @param from The source entity ID.
     * @param to The destination entity ID.
     */
    void move(u32 from, u32 to) noexcept {
        if (mask[from]) {
            bool& cell = mask[to];
            if (!cell) {
                u32 next = occupied++;
                setConnectorTableId(next, to);
                cell = true;
                moveFn(storage, storage, from, to);
                onConstruct(to);
            } else {
                onDestroy(to);
                eraseFn(storage, to);
                moveFn(storage, storage, from, to);
                onConstruct(to);
            }
            onDestroy(from);
            erase(from);
        }
    }

    /**
     * @brief Retrieves a reference to a component.
     * 
     * @tparam T The component type.
     * @param index The entity ID to get the component from.
     * @return T& Reference to the component.
     */
    template <typename T>
    [[nodiscard]]
    T& get(u32 index) const noexcept {
        return *(static_cast<T*>(storage) + index);
    }

    /**
     * @brief Safely retrieves a pointer to a component.
     * 
     * @tparam T The component type.
     * @param index The entity ID to get the component from.
     * @return T* Pointer to the component, or nullptr if not present.
     */
    template <typename T>
    [[nodiscard]]
    T* getIf(u32 index) const noexcept {
        return mask[static_cast<u32>(index)] ? static_cast<T*>(storage) + index : nullptr;
    }

    /**
     * @brief Retrieves a pointer to a component for pointer types.
     * 
     * Specialized version for querying optional components (pointer types).
     * 
     * @tparam T The component pointer type.
     * @param index The entity ID to get the component from.
     * @return T Pointer to the component, or nullptr if not present.
     */
    template <typename T>
    [[nodiscard]]
    EnableIfType<IsPointerValue<T>, T> getDefer(u32 index) const noexcept {
        return mask[index] ? static_cast<T>(storage) + index : nullptr;
    }

    /**
     * @brief Removes the construct callback if one is registered.
     * 
     * Deletes the callback function object and clears the function pointer.
     */
    void removeOnConstruct() noexcept {
        if (onConstructFn) {
            onConstructDeleteFn(onConstructFn);
            onConstructFn = nullptr;
        }
    }

    /**
     * @brief Removes the destroy callback if one is registered.
     * 
     * Deletes the callback function object and clears the function pointer.
     */
    void removeOnDestroy() noexcept {
        if (onDestroyFn) {
            onDestroyDeleteFn(onDestroyFn);
            onDestroyFn = nullptr;
        }
    }

    /**
     * @brief Retrieves the entity ID at a given dense array index.
     * 
     * @param id The dense array index.
     * @return EntityId The entity ID at the specified index.
     * 
     * @warning No bounds checking is performed.
     */
    [[nodiscard]]
    EntityId get(usize id) const noexcept {
        return connector[id];
    }

    /**
     * @brief Array subscript operator for accessing entity IDs by dense index.
     * 
     * @param id The dense array index.
     * @return EntityId The entity ID at the specified index.
     * 
     * @warning No bounds checking is performed.
     */
    [[nodiscard]]
    EntityId operator[](usize id) const noexcept {
        return get(id);
    }

    /**
     * @brief Retrieves component type information.
     * 
     * Returns size and alignment information for the stored component type.
     * 
     * @return ComponentTypeInfo The type information (size and alignment).
     */
    [[nodiscard]]
    const ComponentTypeInfo getTypeInfo() const noexcept {
        return ComponentTypeInfo(this->size, this->alignment);
    }
};

END_MODULE_NAMESPACE();
