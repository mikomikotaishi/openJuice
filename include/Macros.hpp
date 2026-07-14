/**
 * @file Macros.hpp
 * @brief Macros used throughout the program
 *
 * This file contains all macros that are to be included into every file.
 */

#pragma once

#define throws(...) noexcept(__VA_OPT__(!)true)

/**
 * @brief Utility macro to import the stdx::core namespace within the module.
 */
#define STDLIBX_PREPARE_IMPORT_CORE() \
    namespace stdx::core {} \
    using namespace stdx::core;

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
 * @brief Utility macro to set the CARD_KEY and ARTIST_KEY fields in a final class that extends Card.
 * @param CardKey The string literal that will be passed as the card key to query in LocalizationService
 * @param ArtistKey The string literal that will be passed as the artist key to query in LocalizationService
 */
#define CARD_METADATA(CardKey, ArtistKey) \
    static constexpr StringView CARD_KEY = CardKey; /** The key belonging to the card to query in LocalizationService */ \
    static constexpr StringView ARTIST_KEY = ArtistKey; /** The key belonging to the name of the artist to query in LocalizationService */

/**
 * @brief Utility macro to set the EFFECT_KEY and ARTIST_KEY fields in a final class that extends Card.
 * @param EffectKey The string literal that will be passed as the effect key to query in LocalizationService
 */
#define MUSHROOM_METADATA(EffectKey) \
    static constexpr char EFFECT_KEY[] = EffectKey; /** The key belonging to the effect to query in LocalizationService */ \

/**
 * @brief Utility macro to set the UNIT_KEY, ARTIST_KEY, and VOICEACTOR_KEY fields in a final class that extends Unit.
 * @param UnitKey The string literal that will be passed as the unit key to query in LocalizationService
 * @param ArtistKey The string literal that will be passed as the artist key to query in LocalizationService
 * @param VoiceActorKey The string literal that will be passed as the voice actor key to query in LocalizationService
 */
#define UNIT_METADATA(UnitKey, ArtistKey, VoiceActorKey) \
    static constexpr StringView UNIT_KEY = UnitKey; /** The key belonging to the card to query in LocalizationService */ \
    static constexpr StringView ARTIST_KEY = ArtistKey; /** The key belonging to the name of the artist to query in LocalizationService */ \
    static constexpr StringView VOICEACTOR_KEY = VoiceActorKey; /** The key belonging to the name of the voice actor to query in LocalizationService */

/**
 * @brief Automatically sets all stats of card.
 */
#define SET_CARD_STATS() \
    Card(ID, CARD_TYPE, SPAWN_TYPE, RARITY, COST, LEVEL, LIMIT, DECK_POINTS)

/**
 * @brief Automatically set all stats of a mushroom card.
 * @param Type The type of the mushroom (Legendary, Battle, Boost)
 * @param EffectName The effect enum constant associated with that mushroom
 */
#define SET_MUSHROOM_STATS(Type, EffectName) \
    Type##MushroomCard(color, Type##MushroomCard::Effect::EffectName)

/**
 * @brief Automatically sets all stats of a main character.
 */
#define SET_MAIN_CHARACTER_STATS() \
    MainCharacter(ID, DIFFICULTY, HEALTH, ATTACK, DEFENSE, EVADE, RECOVERY)

/**
 * @brief Automatically sets all stats of a basic enemy.
 */
#define SET_BASIC_ENEMY_STATS() \
    BasicEnemy(ID, HEALTH, ATTACK, DEFENSE, EVADE)

/**
 * @brief Automatically sets all stats of a boss enemy.
 */
#define SET_BOSS_ENEMY_STATS() \
    BossEnemy(ID, HEALTH, ATTACK, DEFENSE, EVADE)

/**
 * @brief A utility to specialize a type in std::formatter. 
 * @param Typename The type to specialize into the formatter.
 *
 * Requires that Formatter is imported into the current scope.
 * Used as a hack to allow stdx::fmt::Formatter to be used by stdx::fmt::format().
 */
#define SPECIALIZE_FORMATTER(Typename) \
    template <> \
    struct stdx::fmt::formatter<Typename> : public Formatter<Typename> {};

/**
 * @brief A utility to specialize a type in std::hash. 
 * @param Typename The type to specialize into the hash.
 *
 * Requires that Hash is imported into the current scope.
 * Used as a hack to allow stdx::core::Hash to be used by hash().
 */
#define SPECIALIZE_HASH(Typename) \
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
