/**
 * @file CoopCardFactory.cppm
 * @module openjuice.card:CoopCardFactory
 * @brief Implementation of the CoopCardFactory class.
 *
 * This file contains the implementation of the CoopCardFactory class, which is used to create CoopCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:CoopCardFactory;

import stdx;

import :coop;

import openjuice.engine.card;
import openjuice.engine.services;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::spawn::CoopCard;

using namespace openjuice::card::coop;
using namespace openjuice::card::coop::role;
using namespace openjuice::card::coop::seasonal;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class CoopCardFactory
 * @brief Factory class for creating CoopCard objects.
 *
 * The CoopCardFactory class is a singleton factory class that creates CoopCard objects based on the given ID.
 */
export class CoopCardFactory final {
public:
    /** 
     * @enum SecondaryType
     * @brief The secondary type, used to specify to the factory what the ID is in relation to.
     */
    enum class SecondaryType: u8 {
        STANDARD, ///< A CoopCard of standard variety
        ROLE, ///< A CoopCard of role variety
        SEASONAL, ///< A CoopCard of seasonal variety
    };
private:
    [[nodiscard]]
    static constexpr String secondaryTypeToString(SecondaryType type) noexcept {
        switch (type) {
            case CoopCardFactory::SecondaryType::STANDARD:
                return "Standard";
            case CoopCardFactory::SecondaryType::ROLE:
                return "Role";
            case CoopCardFactory::SecondaryType::SEASONAL:
                return "Seasonal";
        }
        Ops::unreachable();
    }
public:
    CoopCardFactory() = delete("CoopCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a CoopCard object with the given ID.
     *
     * @param id ID of the CoopCard to create
     * @return Shared pointer to the created CoopCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<CoopCard>> create(u8 id, SecondaryType type = SecondaryType::STANDARD) noexcept {
        switch (type) {
            case SecondaryType::STANDARD:
                switch (id) {
                    case 0:
                        return nullptr;

                    default:
                        return nullopt;
                }
            case SecondaryType::ROLE:
                switch (id) {
                    case 0:
                        return nullptr;
                    case UltimateWeaponInTheSun::ID:
                        return Pointers::shared<UltimateWeaponInTheSun>();
                    case LifeguardOnTheWhiteBeach::ID:
                        return Pointers::shared<LifeguardOnTheWhiteBeach>();
                    case GuardianOfBloomingFlowers::ID:
                        return Pointers::shared<GuardianOfBloomingFlowers>();
                    case UnforgivingAvenger::ID:
                        return Pointers::shared<UnforgivingAvenger>();
                    case SummerGames::ID:
                        return Pointers::shared<SummerGames>();
                    default:
                        return nullopt;
                }
            case SecondaryType::SEASONAL:
                switch (id) {
                    case 0:
                        return nullptr;
                    case SeasonalUltimateWeaponInTheSun::ID:
                        return Pointers::shared<SeasonalUltimateWeaponInTheSun>();
                    case SeasonalLifeguardOnTheWhiteBeach::ID:
                        return Pointers::shared<SeasonalLifeguardOnTheWhiteBeach>();
                    case SeasonalGuardianOfBloomingFlowers::ID:
                        return Pointers::shared<SeasonalGuardianOfBloomingFlowers>();
                    case SeasonalUnforgivingAvenger::ID:
                        return Pointers::shared<SeasonalUnforgivingAvenger>();
                    default:
                        return nullopt;
                }
        }
        Ops::unreachable();
    }
};

END_MODULE_NAMESPACE();

using openjuice::card::CoopCardFactory;

template <>
struct Formatter<CoopCardFactory::SecondaryType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(CoopCardFactory::SecondaryType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case CoopCardFactory::SecondaryType::STANDARD:
                name = "Standard";
                break;
            case CoopCardFactory::SecondaryType::ROLE:
                name = "Role";
                break;
            case CoopCardFactory::SecondaryType::SEASONAL:
                name = "Seasonal";
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(CoopCardFactory::SecondaryType);
