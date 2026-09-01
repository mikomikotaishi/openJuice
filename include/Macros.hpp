/**
 * @file Macros.hpp
 * @brief Macros used throughout the program
 *
 * This file contains all macros that are to be included into every file.
 */

#pragma once

#ifdef __cpp_lib_reflection
#define THROWS(...) [[=Throws<__VA_ARGS__>]]
#else
#define THROWS(...)
#endif

/**
 * @brief A utility to begin a namespace matching the current module name.
 * @param Name The name of the namespace to begin, which should match the module.
 */
#define BEGIN_MODULE_NAMESPACE(Name) namespace Name {

/**
 * @brief A utility to end the namespace that BEGIN_MODULE_NAMESPACE() began.
 */
#define END_MODULE_NAMESPACE() }

/**
 * @brief Automatically sets all stats of card.
 */
#define SET_CARD_STATS() \
    Card(ID, CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS, METADATA)

/**
 * @brief Automatically set all stats of a mushroom card.
 * @param Type The type of the mushroom (Legendary, Battle, Boost)
 * @param EffectName The effect enum constant associated with that mushroom
 */
#define SET_MUSHROOM_STATS(Type, EffectName) \
    Card(static_cast<u16>(Type##MushroomCard::Effect::EffectName), CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS, Metadata { \
        .cardKey = typeToKey(Type##MushroomCard::Effect::EffectName), \
        .artistKey = colorToArtistKey(color), \
    }), \
    Type##MushroomCard(color, Type##MushroomCard::Effect::EffectName)

/**
 * @brief Automatically sets all stats of a main character.
 */
#define SET_MAIN_CHARACTER_STATS() \
    MainCharacter(ID, DIFFICULTY, HEALTH, ATTACK, DEFENSE, EVADE, RECOVERY, METADATA)

/**
 * @brief Automatically sets all stats of a basic enemy.
 */
#define SET_BASIC_ENEMY_STATS() \
    BasicEnemy(ID, HEALTH, ATTACK, DEFENSE, EVADE, METADATA)

/**
 * @brief Automatically sets all stats of a boss enemy.
 */
#define SET_BOSS_ENEMY_STATS() \
    BossEnemy(ID, HEALTH, ATTACK, DEFENSE, EVADE, METADATA)

/**
 * @brief A utility to specialize a type in std::formatter. 
 * @param Typename The type to specialize into the formatter.
 *
 * Requires that Formatter is imported into the current scope.
 * Used as a hack to allow stdx::fmt::Formatter to be used by stdx::fmt::format().
 */
#define SPECIALIZE_FORMATTER(Typename) \
    template <> \
    struct stdx::fmt::formatter<Typename> : public stdx::fmt::Formatter<Typename> {};

/**
 * @brief A utility to specialize a type in std::hash. 
 * @param Typename The type to specialize into the hash.
 *
 * Requires that Hash is imported into the current scope.
 * Used as a hack to allow stdx::core::Hash to be used by hash().
 */
#define SPECIALIZE_HASH(Typename) \
    template <> \
    struct stdx::core::hash<Typename> : public stdx::core::Hash<Typename> {};

#ifdef NDEBUG
#define RELEASE_NOEXCEPT noexcept
#define RELEASE_INLINE inline
#define RELEASE_CONSTEXPR constexpr
#else
#define RELEASE_NOEXCEPT
#define RELEASE_INLINE
#define RELEASE_CONSTEXPR
#endif
