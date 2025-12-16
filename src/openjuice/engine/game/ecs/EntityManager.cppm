/**
 * @file EntityManager.cppm
 * @module openjuice.engine.game.ecs.Registry:EntityManager
 * @brief Module of the ECS entity manager.
 *
 * This file contains the definitions for the ECS entity manager.
 * Based on kawa_ecs (https://github.com/superPuero/kawa_ecs)
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs.Registry:EntityManager;

import std;

import openjuice.engine.game.ecs.Meta;

using std::mem::UniquePointer;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @class EntityManager
 * @brief Manages entity lifecycle and ID allocation in the ECS.
 * 
 * The EntityManager is responsible for creating, tracking, and destroying entities.
 * It uses a sparse set architecture combined with a free list for efficient entity
 * ID reuse. The manager maintains:
 * - A dense array of active entity IDs (entries)
 * - A sparse array mapping entity IDs to dense indices (indices)
 * - A mask tracking which IDs are alive
 * - A free list for recycling deleted entity IDs
 */
export class EntityManager {
private:
    UniquePointer<bool[]> mask; ///< Boolean mask tracking which entity IDs are currently active/alive.
    UniquePointer<EntityId[]> entries; ///< Dense array of all currently alive entity IDs.
    UniquePointer<u32[]> indices; ///< Sparse array mapping entity IDs to their dense array indices.
    UniquePointer<u32[]> freeIds; ///< Free list of recycled entity IDs available for reuse.
    u32 capacity = 512; ///< The maximum number of entities that may exist simultaneously.
    u32 occupied = 0; ///< The highest entity ID ever allocated (includes alive and freed IDs).
    u32 entryCount = 0; ///< The number of entities currently alive.
    u32 freeIdsCount = 0; ///< The number of IDs currently in the free list.

    /**
     * @brief Updates the bidirectional mapping between entity ID and dense array index.
     * 
     * Maintains the sparse-set invariant by updating both the dense array (entries)
     * and the sparse array (indices) to create a bidirectional mapping.
     * 
     * @param id The entity ID to add to the mapping.
     */
    void setEntityTableId(EntityId id) noexcept {
        entries[entryCount] = id;
        indices[id] = entryCount;
    }
public:
    GETTER(u32, Capacity, capacity);
    GETTER(u32, Occupied, occupied);
    GETTER(u32, EntryCount, entryCount);
    GETTER(u32, FreeIdsCount, freeIdsCount);

    /**
     * @brief Constructs a new EntityManager with the specified capacity.
     * 
     * Allocates arrays for entity tracking, including the mask, entries, indices,
     * and free list structures.
     * 
     * @param capacity The maximum number of entities that can exist simultaneously.
     */
    explicit EntityManager(u32 capacity):
        mask{std::mem::make_unique<bool[]>(capacity)},
        entries{std::mem::make_unique<EntityId[]>(capacity)},
        indices{std::mem::make_unique<u32[]>(capacity)},
        freeIds{std::mem::make_unique<u32[]>(capacity)},
        capacity{capacity} {}

    /**
     * @brief Copy constructor for EntityManager.
     * 
     * Performs a deep copy of all entity tracking structures from another
     * EntityManager instance.
     * 
     * @param other The EntityManager instance to copy from.
     */
    EntityManager(const EntityManager& other):
        mask{std::mem::make_unique<bool[]>(other.capacity)},
        entries{std::mem::make_unique<EntityId[]>(other.capacity)},
        indices{std::mem::make_unique<u32[]>(other.capacity)},
        freeIds{std::mem::make_unique<u32[]>(other.capacity)},
        capacity{other.capacity},
        occupied{other.occupied},
        entryCount{other.entryCount},
        freeIdsCount{other.freeIdsCount} {
        std::ranges::copy(Span<bool>(other.mask.get(), capacity), mask.get());
        std::ranges::copy(Span<EntityId>(other.entries.get(), capacity), entries.get());
        std::ranges::copy(Span<u32>(other.indices.get(), capacity), indices.get());
        std::ranges::copy(Span<u32>(other.freeIds.get(), capacity), freeIds.get());
    }

    /**
     * @brief Move constructor for EntityManager.
     * 
     * Transfers ownership of all entity tracking structures from another
     * EntityManager instance, leaving the source in a valid but empty state.
     * 
     * @param other The EntityManager instance to move from.
     */
    EntityManager(EntityManager&& other):
        mask{std::util::move(other.mask)},
        entries{std::util::move(other.entries)},
        indices{std::util::move(other.indices)},
        freeIds{std::util::move(other.freeIds)},
        capacity{other.capacity},
        occupied{other.occupied},
        entryCount{other.entryCount},
        freeIdsCount{other.freeIdsCount} {
        other.capacity = 0;
        other.occupied = 0;
        other.entryCount = 0;
        other.freeIdsCount = 0;
    }

    /**
     * @brief Copy assignment operator for EntityManager.
     * 
     * Releases current resources and performs a deep copy of all entity tracking
     * structures from another EntityManager instance.
     * 
     * @param other The EntityManager instance to copy from.
     * @return EntityManager& Reference to this instance.
     */
    EntityManager& operator=(const EntityManager& other) {
        if (this != &other) {
            capacity = other.capacity;
            occupied = other.occupied;
            entryCount = other.entryCount;
            freeIdsCount = other.freeIdsCount;

            mask = std::mem::make_unique<bool[]>(capacity);
            std::ranges::copy(Span<bool>(other.mask.get(), capacity), mask.get());

            entries = std::mem::make_unique<EntityId[]>(capacity);
            std::ranges::copy(Span<EntityId>(other.entries.get(), capacity), entries.get());

            indices = std::mem::make_unique<u32[]>(capacity);
            std::ranges::copy(Span<u32>(other.indices.get(), capacity), indices.get());

            freeIds = std::mem::make_unique<u32[]>(capacity);
            std::ranges::copy(Span<u32>(other.freeIds.get(), capacity), freeIds.get());
        }
        return *this;
    }

    /**
     * @brief Move assignment operator for EntityManager.
     * 
     * Releases current resources and transfers ownership of all entity tracking
     * structures from another EntityManager instance.
     * 
     * @param other The EntityManager instance to move from.
     * @return EntityManager& Reference to this instance.
     */
    EntityManager& operator=(EntityManager&& other) noexcept {
        if (this != &other) {
            capacity = other.capacity;
            occupied = other.occupied;
            entryCount = other.entryCount;
            freeIdsCount = other.freeIdsCount;

            mask = std::util::move(other.mask);
            entries = std::util::move(other.entries);
            indices = std::util::move(other.indices);
            freeIds = std::util::move(other.freeIds);

            other.capacity = 0;
            other.occupied = 0;
            other.entryCount = 0;
            other.freeIdsCount = 0;
        }
        return *this;
    }

    /**
     * @brief Returns an iterator to the beginning of alive entity IDs.
     * 
     * Enables range-based iteration over all currently alive entities.
     * 
     * @return EntityId* Pointer to the first element in the dense entries array.
     */
    EntityId* begin() noexcept {
        return entries.get();
    }

    /**
     * @brief Returns an iterator to the end of alive entity IDs.
     * 
     * Enables range-based iteration over all currently alive entities.
     * 
     * @return EntityId* Pointer to one past the last element in the dense entries array.
     * 
     * @note This returns entries.get() + occupied, not entryCount, which may include
     *       freed IDs that have not been completely cleaned up yet.
     */
    EntityId* end() noexcept {
        return entries.get() + occupied;
    }

    /**
     * @brief Clears all entities and resets the EntityManager.
     * 
     * Removes all entities and resets tracking structures to their initial state.
     * Does not deallocate the underlying storage capacity.
     */
    void clear() noexcept {
        std::ranges::fill(Span<bool>(mask.get(), capacity), false);
        occupied = 0;
        entryCount = 0;
        freeIdsCount = 0;
    }

    /**
     * @brief Creates a new entity and returns its ID.
     * 
     * Attempts to create a new entity by either:
     * 1. Reusing an ID from the free list (if available)
     * 2. Allocating a new ID from the occupied counter (if space available)
     * 
     * The entity is marked as alive and added to the active entities tracking.
     * 
     * @return Optional<EntityId> The newly created entity ID, or nullopt if capacity is reached.
     */
    [[nodiscard]]
    Optional<EntityId> createEntity() noexcept {
        EntityId id;
        if (freeIdsCount > 0) {
            id = freeIds[--freeIdsCount];
        } else if (occupied >= capacity) {
            return nullopt;
        } else {
            id = occupied++;
        }
        mask[id] = true;
        setEntityTableId(id);
        ++entryCount;
        return id;
    }

    /**
     * @brief Checks if an entity is currently alive.
     * 
     * Determines whether the entity with the given ID is active and has not
     * been removed.
     * 
     * @param id The entity ID to check.
     * @return bool True if the entity is alive, false otherwise.
     */
    [[nodiscard]]
    bool alive(EntityId id) const noexcept {
        return mask[id];
    }

    /**
     * @brief Removes an entity and marks its ID for reuse.
     * 
     * Destroys the entity with the given ID by:
     * 1. Adding the ID to the free list for reuse
     * 2. Marking the ID as not alive in the mask
     * 3. Removing it from the dense array using swap-and-pop
     * 4. Updating the indices mapping
     * 
     * If the entity is already dead, this operation does nothing.
     * 
     * @param id The entity ID to remove.
     */
    void remove(EntityId id) noexcept {
        if (!mask[id]) {
            return;
        }
        freeIds[freeIdsCount++] = id;
        mask[id] = false;
        u32 index = indices[id];
        entries[index] = entries[--entryCount];
        indices[entries[entryCount]] = index;
    }

    /**
     * @brief Retrieves the entity ID at a given dense array index.
     * 
     * Provides direct access to the entity ID stored at a specific position
     * in the dense entries array.
     * 
     * @param index The dense array index.
     * @return EntityId The entity ID at the specified index.
     */
    [[nodiscard]]
    EntityId get(u32 index) const noexcept {
        return entries[index];
    }

    /**
     * @brief Array subscript operator for accessing entity IDs by index.
     * 
     * @param index The dense array index.
     * @return EntityId The entity ID at the specified index.
     */
    [[nodiscard]]
    EntityId operator[](usize index) const noexcept {
        return get(static_cast<u32>(index));
    }
};

END_MODULE_NAMESPACE();
