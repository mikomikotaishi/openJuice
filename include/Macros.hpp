/**
 * @file Macros.hpp
 * @brief Macros used throughout the program
 *
 * This file contains all macros that are to be included into every file.
 */

#pragma once

#define throws(...) noexcept(__VA_OPT__(!)true)

#define extends public
#define implements public

/**
 * @brief Utility macro to import the stdx::core namespace within the module.
 */
#define STDLIBX_PREPARE_IMPORT_CORE() \
    namespace stdx::core {} \
    using namespace stdx::core;

/**
 * @brief A utility to begin a namespace matching the current module name.
 * 
 * @param Name The name of the namespace to begin, which should match the module.
 */
#define BEGIN_MODULE_NAMESPACE(Name) namespace Name {

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
#define SETTER_NO_FLUENT(Type, Method, Name) \
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
#define SETTER_FLUENT(Type, Method, Name, Fluent) \
    /** @brief Sets the name value for the object. @return The instance of the object. */  \
    decltype(*this) set##Method(Type value) noexcept { \
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
#define SETTER(...) SETTER_GET_MACRO(__VA_ARGS__, SETTER_FLUENT, SETTER_NO_FLUENT)(__VA_ARGS__)

// Helper macros for PROPERTY overloading
#define PROPERTY_GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

/**
 * @brief Utility macro to create getter and setter methods for a property (void setter).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the methods.
 * @param Name The machine-readable name of the property.
 */
#define PROPERTY_NO_FLUENT(Type, Method, Name) \
    GETTER(Type, Method, Name) \
    SETTER_NO_FLUENT(Type, Method, Name)

/**
 * @brief Utility macro to create getter and setter methods for a property (fluent setter).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the methods.
 * @param Name The machine-readable name of the property.
 * @param Fluent If present, enables fluent chaining for setter.
 */
#define PROPERTY_FLUENT(Type, Method, Name, Fluent) \
    GETTER(Type, Method, Name) \
    SETTER_FLUENT(Type, Method, Name, Fluent)

/**
 * @brief Utility macro to create getter and setter methods for a property.
 * Can be called with 3 arguments (void setter) or 4 arguments (fluent setter).
 *
 * @param Type The type of the property.
 * @param Method The human-readable name for the methods.
 * @param Name The machine-readable name of the property.
 * @param Fluent (Optional) If provided, enables fluent chaining for setter.
 */
#define PROPERTY(...) PROPERTY_GET_MACRO(__VA_ARGS__, PROPERTY_FLUENT, PROPERTY_NO_FLUENT)(__VA_ARGS__)

/**
 * @brief Utility macro to set the CARD_KEY and ARTIST_KEY fields in a final class that extended Card (fulfils the concept ExtendsCard).
 * 
 * @param CardKey The string literal that will be passed as the card key to query in TextManager
 * @param ArtistKey The string literal that will be passed as the artist key to query in TextManager
 */
#define CARD_METADATA(CardKey, ArtistKey) \
    static constexpr StringView CARD_KEY = CardKey; /** The key belonging to the card to query in TextManager */ \
    static constexpr StringView ARTIST_KEY = ArtistKey; /** The key belonging to the name of the artist to query in TextManager */

/**
 * @brief Utility macro to set the EFFECT_KEY and ARTIST_KEY fields in a final class that extended Card (fulfils the concept ExtendsMushroomCard).
 * 
 * @param EffectKey The string literal that will be passed as the effect key to query in TextManager
 */
#define MUSHROOM_METADATA(EffectKey) \
    static constexpr char EFFECT_KEY[] = EffectKey; /** The key belonging to the effect to query in TextManager */ \

/**
 * @brief Utility macro to set the UNIT_KEY, ARTIST_KEY, and VOICEACTOR_KEY fields in a final class that extended Unit (fulfils the concept ExtendsUnit).
 * 
 * @param UnitKey The string literal that will be passed as the unit key to query in TextManager
 * @param ArtistKey The string literal that will be passed as the artist key to query in TextManager
 * @param VoiceActorKey The string literal that will be passed as the voice actor key to query in TextManager
 */
#define UNIT_METADATA(UnitKey, ArtistKey, VoiceActorKey) \
    static constexpr StringView UNIT_KEY = UnitKey; /** The key belonging to the card to query in TextManager */ \
    static constexpr StringView ARTIST_KEY = ArtistKey; /** The key belonging to the name of the artist to query in TextManager */ \
    static constexpr StringView VOICEACTOR_KEY = VoiceActorKey; /** The key belonging to the name of the voice actor to query in TextManager */

/**
 * @brief Automatically sets all stats of card.
 */
#define SET_CARD_STATS() \
    Card(ID, CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS)

/**
 * @brief Automatically set all stats of a mushroom card.
 *
 * @param Type The type of the mushroom (Legendary, Battle, Boost)
 * @param EffectName The effect enum constant associated with that mushroom
 */
#define SET_MUSHROOM_STATS(Type, EffectName) \
    Type##MushroomCard(colour, Type##MushroomCard::Effect::EffectName)

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
 * @brief A utility to specialise a type in std::formatter. 
 * Requires that Formatter is imported into the current scope.
 * Used as a hack to allow std::fmt::Formatter to be used by stdlib::fmt::format().
 * 
 * @param Typename The type to specialise into the formatter.
 */
#define SPECIALISE_FORMATTER(Typename) \
    template <> \
    struct stdx::fmt::formatter<Typename> : public Formatter<Typename> {};

/**
 * @brief A utility to specialise a type in std::hash. 
 * Requires that Hash is imported into the current scope.
 * Used as a hack to allow std::core::Hash to be used by hash().
 * 
 * @param Typename The type to specialise into the hash.
 */
#define SPECIALISE_HASH(Typename) \
    template <> \
    struct stdx::core::hash<Typename> : public Hash<Typename> {};

#ifdef NDEBUG
#define RELEASE_NOEXCEPT noexcept
#define RELEASE_INLINE inline
#define RELEASE_CONSTEXPR constexpr
#else
#define RELEASE_NOEXCEPT
#define RELEASE_INLINE
#define RELEASE_CONSTEXPR
#endif

#ifdef __GNUC__
STDLIBX_PREPARE_IMPORT_CORE();
#endif
