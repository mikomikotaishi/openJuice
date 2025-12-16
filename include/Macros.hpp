/**
 * @file Macros.hpp
 * @brief Macros used throughout the program
 *
 * This file contains all macros that are to be included into every file.
 */

#pragma once

#define throws(...) noexcept(false)

#define extends(...) : public __VA_ARGS__
#define implements(...) : public __VA_ARGS__

/**
 * @brief A utility to begin a namespace matching the current module name.
 * 
 * @param name The name of the namespace to begin, which should match the module.
 */
#define BEGIN_MODULE_NAMESPACE(name) namespace name {

/**
 * @brief A utility to end the namespace that BEGIN_MODULE_NAMESPACE() began.
 */
#define END_MODULE_NAMESPACE() }

/**
 * @brief A utility to build a get method on top of a property.
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the method.
 * @param Name The machine-readable name of the property.
 */
#define GETTER(Type, Method, Name) \
    /** @brief Retrieves the name value for the object. @return The name value of the object. */  \
    [[nodiscard]] \
    Type get##Method() const noexcept { \
        return Name; \
    }

// Helper macros for SETTER overloading
#define SETTER_GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

/**
 * @brief A utility to build a set method on top of a property (void return).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the method.
 * @param Name The machine-readable name of the property.
 */
#define SETTER_3(Type, Method, Name) \
    /** @brief Sets the name value for the object. */  \
    void set##Method(Type value) noexcept { \
        Name = value; \
    }

/**
 * @brief A utility to build a set method on top of a property (fluent return).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the method.
 * @param Name The machine-readable name of the property.
 * @param Fluent If present, enables fluent chaining (return *this).
 */
#define SETTER_4(Type, Method, Name, Fluent) \
    /** @brief Sets the name value for the object. @return The instance of the object. */  \
    auto set##Method(Type value) noexcept -> decltype(*this) { \
        Name = value; \
        return *this; \
    }

/**
 * @brief A utility to build a set method on top of a property.
 * Can be called with 3 arguments (returns void) or 4 arguments (returns *this for fluent chaining).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the method.
 * @param Name The machine-readable name of the property.
 * @param Fluent (Optional) If provided, enables fluent chaining.
 */
#define SETTER(...) SETTER_GET_MACRO(__VA_ARGS__, SETTER_4, SETTER_3)(__VA_ARGS__)

// Helper macros for PROPERTY overloading
#define PROPERTY_GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

/**
 * @brief Utility macro to create getter and setter methods for a property (void setter).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the methods.
 * @param Name The machine-readable name of the property.
 */
#define PROPERTY_3(Type, Method, Name) \
    GETTER(Type, Method, Name) \
    SETTER_3(Type, Method, Name)

/**
 * @brief Utility macro to create getter and setter methods for a property (fluent setter).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the methods.
 * @param Name The machine-readable name of the property.
 * @param Fluent If present, enables fluent chaining for setter.
 */
#define PROPERTY_4(Type, Method, Name, Fluent) \
    GETTER(Type, Method, Name) \
    SETTER_4(Type, Method, Name, Fluent)

/**
 * @brief Utility macro to create getter and setter methods for a property.
 * Can be called with 3 arguments (void setter) or 4 arguments (fluent setter).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the methods.
 * @param Name The machine-readable name of the property.
 * @param Fluent (Optional) If provided, enables fluent chaining for setter.
 */
#define PROPERTY(...) PROPERTY_GET_MACRO(__VA_ARGS__, PROPERTY_4, PROPERTY_3)(__VA_ARGS__)

/**
 * @brief Utility macro to implement the method noop() which must be implemented by
 * all final classes implementing IFinalOnly.
 */
#define IMPLEMENT_NOOP() \
    /** @brief No-operation function, should only be implemented by final classes. */ \
    [[maybe_unused]] \
    void noop() const noexcept final {}

/**
 * @brief Utility macro to set the CARD_KEY and ARTIST_KEY fields in a final class that extended Card (fulfils the concept ExtendsCard).
 * 
 * @param cardKey The string literal that will be passed as the card key to query in TextManager
 * @param artistKey The string literal that will be passed as the artist key to query in TextManager
 */
#define CARD_METADATA(cardKey, artistKey) \
    static constexpr StringView CARD_KEY = cardKey; /** The key belonging to the card to query in TextManager */ \
    static constexpr StringView ARTIST_KEY = artistKey; /** The key belonging to the name of the artist to query in TextManager */

/**
 * @brief Utility macro to set the EFFECT_KEY and ARTIST_KEY fields in a final class that extended Card (fulfils the concept ExtendsMushroomCard).
 * 
 * @param cardKey The string literal that will be passed as the effect key to query in TextManager
 */
#define MUSHROOM_METADATA(effectKey) \
    static constexpr char EFFECT_KEY[] = effectKey; /** The key belonging to the effect to query in TextManager */ \

/**
 * @brief Utility macro to set the UNIT_KEY, ARTIST_KEY, and VOICEACTOR_KEY fields in a final class that extended Unit (fulfils the concept ExtendsUnit).
 * 
 * @param unitKey The string literal that will be passed as the unit key to query in TextManager
 * @param artistKey The string literal that will be passed as the artist key to query in TextManager
 * @param voiceactorKey The string literal that will be passed as the voice actor key to query in TextManager
 */
#define UNIT_METADATA(unitKey, artistKey, voiceactorKey) \
    static constexpr StringView UNIT_KEY = unitKey; /** The key belonging to the card to query in TextManager */ \
    static constexpr StringView ARTIST_KEY = artistKey; /** The key belonging to the name of the artist to query in TextManager */ \
    static constexpr StringView VOICEACTOR_KEY = voiceactorKey; /** The key belonging to the name of the voice actor to query in TextManager */

/**
 * @brief Automatically sets all stats of card.
 */
#define SET_CARD_STATS() \
    Card(ID, CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS)

/**
 * @brief Automatically set all stats of a mushroom card.
 *
 * @param Type The type of the mushroom (Legendary, Battle, Boost)
 * @param Effect The effect enum constant associated with that mushroom
 */
#define SET_MUSHROOM_STATS(Type, Effect) \
    Type##MushroomCard(colour, Type##MushroomType::Effect)

/**
 * @brief Automatically sets all stats of a main character.
 */
#define SET_MAIN_CHARACTER_STATS() \
    MainCharacter(ID, DIFFICULTY, HEALTH, ATTACK, DEFENCE, EVADE, RECOVERY)

/**
 * @brief Automatically sets all stats of a basic enemy.
 */
#define SET_BASIC_ENEMY_STATS() \
    BasicEnemy(ID, HEALTH, ATTACK, DEFENCE, EVADE)

/**
 * @brief Automatically sets all stats of a boss enemy.
 */
#define SET_BOSS_ENEMY_STATS() \
    BossEnemy(ID, HEALTH, ATTACK, DEFENCE, EVADE)

/**
 * @brief Utility macro to set a class that cannot be instantiated, copied, or moved.
 * Use this for static utility classes that should only contain static methods.
 *
 * @param ClassName The name of the class to apply the macro to.
 */
#define UTILITY_CLASS(ClassName) \
public: \
    /** @brief Deleted constructor to prevent instantiation. */ \
    ClassName() = delete; \
    /** @brief Deleted destructor to prevent destruction. */ \
    ~ClassName() = delete; \
    /** @brief Deleted copy constructor to prevent copying. */ \
    ClassName(const ClassName&) = delete; \
    /** @brief Deleted copy assignment operator to prevent copying. */ \
    ClassName& operator=(const ClassName&) = delete; \
    /** @brief Deleted move constructor to prevent copying. */ \
    ClassName(ClassName&&) = delete; \
    /** @brief Deleted move assignment operator to prevent copying. */ \
    ClassName& operator=(ClassName&&) = delete; \
private:

/**
 * @brief Utility macro to set a class with defaulted Big Five operations.
 * This automatically generates default constructor, destructor, copy constructor,
 * copy assignment operator, move constructor, and move assignment operator.
 *
 * @param ClassName The name of the class to apply the macro to.
 */
#define DEFAULT_BIG_FIVE(ClassName) \
public: \
    /** @brief Default constructor. */ \
    ClassName() = default; \
    /** @brief Default destructor. */ \
    ~ClassName() = default; \
    /** @brief Default copy constructor. */ \
    ClassName(const ClassName&) = default; \
    /** @brief Default copy assignment operator. */ \
    ClassName& operator=(const ClassName&) = default; \
    /** @brief Default move constructor. */ \
    ClassName(ClassName&&) = default; \
    /** @brief Default move assignment operator. */ \
    ClassName& operator=(ClassName&&) = default;

/**
 * @brief Utility macro to set a class that is copyable but not movable.
 * This allows copying operations but prevents move operations.
 *
 * @param ClassName The name of the class to apply the macro to.
 */
#define COPYABLE_ONLY(ClassName) \
    /** @brief Default constructor. */ \
    ClassName() = default; \
    /** @brief Default destructor. */ \
    ~ClassName() = default; \
    /** @brief Default copy constructor. */ \
    ClassName(const ClassName&) = default; \
    /** @brief Default copy assignment operator. */ \
    ClassName& operator=(const ClassName&) = default; \
public: \
    /** @brief Deleted move constructor to prevent moving. */ \
    ClassName(ClassName&&) = delete; \
    /** @brief Deleted move assignment operator to prevent moving. */ \
    ClassName& operator=(ClassName&&) = delete; \
private:

/**
 * @brief Utility macro to set a class that is movable but not copyable.
 * This allows move operations but prevents copy operations. Useful for resource-managing classes.
 *
 * @param ClassName The name of the class to apply the macro to.
 */
#define MOVABLE_ONLY(ClassName) \
    /** @brief Default constructor. */ \
    ClassName() = default; \
    /** @brief Default destructor. */ \
    ~ClassName() = default; \
public: \
    /** @brief Deleted copy constructor to prevent copying. */ \
    ClassName(const ClassName&) = delete; \
    /** @brief Deleted copy assignment operator to prevent copying. */ \
    ClassName& operator=(const ClassName&) = delete; \
private: \
    /** @brief Default move constructor. */ \
    ClassName(ClassName&&) = default; \
    /** @brief Default move assignment operator. */ \
    ClassName& operator=(ClassName&&) = default;

/**
 * @brief Utility macro to set a class that cannot be copied or moved.
 * This prevents all copy and move operations while allowing default construction.
 * Useful for singleton base classes or unique resource holders.
 *
 * @param ClassName The name of the class to apply the macro to.
 */
#define NON_COPYABLE_NON_MOVABLE(ClassName) \
    /** @brief Default constructor. */ \
    ClassName() = default; \
    /** @brief Default destructor. */ \
    ~ClassName() = default; \
public: \
    /** @brief Deleted copy constructor to prevent copying. */ \
    ClassName(const ClassName&) = delete; \
    /** @brief Deleted copy assignment operator to prevent copying. */ \
    ClassName& operator=(const ClassName&) = delete; \
    /** @brief Deleted move constructor to prevent moving. */ \
    ClassName(ClassName&&) = delete; \
    /** @brief Deleted move assignment operator to prevent moving. */ \
    ClassName& operator=(ClassName&&) = delete; \
private:

/**
 * @brief Utility macro to set a singleton class pattern.
 * This provides the standard singleton implementation with thread-safe getInstance().
 * The class cannot be copied, moved, or instantiated directly.
 *
 * @param ClassName The name of the singleton class.
 */
#define SINGLETON_CLASS(ClassName) \
    /** @brief Private default constructor for singleton pattern. */ \
    ClassName() = default; \
    /** @brief Default destructor. */ \
    ~ClassName() = default; \
public: \
    /** @brief Deleted copy constructor to prevent copying. */ \
    ClassName(const ClassName&) = delete; \
    /** @brief Deleted copy assignment operator to prevent copying. */ \
    ClassName& operator=(const ClassName&) = delete; \
    /** @brief Deleted move constructor to prevent moving. */ \
    ClassName(ClassName&&) = delete; \
    /** @brief Deleted move assignment operator to prevent moving. */ \
    ClassName& operator=(ClassName&&) = delete; \
public: \
    /** @brief Get the singleton instance. @return Reference to the singleton instance. */ \
    [[nodiscard]] \
    static ClassName& getInstance() { \
        static ClassName instance; \
        return instance; \
    } \
private:

/**
 * @brief A utility to specialise a type in std::formatter. 
 * Requires that Formatter is imported into the current scope.
 * Used as a hack to allow std::fmt::Formatter to be used by stdlib::fmt::format().
 * 
 * @param Typename The type to specialise into the formatter.
 */
#define SPECIALISE_FORMATTER(Typename) \
    template <> \
    struct std::fmt::formatter<Typename> : public Formatter<Typename> {};

/**
 * @brief A utility to specialise a type in std::hash. 
 * Requires that Hash is imported into the current scope.
 * Used as a hack to allow std::core::Hash to be used by hash().
 * 
 * @param Typename The type to specialise into the hash.
 */
#define SPECIALISE_HASH(Typename) \
    template <> \
    struct std::core::hash<Typename> : public Hash<Typename> {};

#ifdef NDEBUG
#define RELEASE_NOEXCEPT noexcept
#define RELEASE_INLINE inline
#define RELEASE_CONSTEXPR constexpr
#else
#define RELEASE_NOEXCEPT
#define RELEASE_INLINE
#define RELEASE_CONSTEXPR
#endif
