/**
 * @file CoopCardFactory.cppm
 * @module openjuice.card.CoopCardFactory
 * @brief Implementation of the CoopCardFactory class.
 *
 * This file contains the implementation of the CoopCardFactory class, which is used to create CoopCard objects.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.card.CoopCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.coop;
import openjuice.card.seasonal;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fmt = std::fmt;
namespace mem = std::mem;
namespace sys = std::sys;

using openjuice::engine::card::spawntypes::CoopCard;

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
private:
    UTILITY_CLASS(CoopCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("CoopCardFactory"); ///< The logger instance.
public:
    /** 
     * @enum SecondaryType
     * @brief The secondary type, used to specify to the factory what the ID is in relation to.
     */
    enum class SecondaryType: u8 {
        STANDARD, ///< A CoopCard of standard variety
        ROLE, ///< A CoopCard of role variety
        SEASONAL ///< A CoopCard of seasonal variety
    };

    /**
     * @brief Create a CoopCard object with the given ID.
     *
     * @param id ID of the CoopCard to create
     * @return Shared pointer to the created CoopCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<CoopCard>> create(u8 id, SecondaryType type = SecondaryType::STANDARD) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating CoopCard of ID: {}, secondary type: {}", id, type);
        #endif

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
                    case 1:
                        return mem::make_shared<UltimateWeaponInTheSun>();
                    case 2:
                        return mem::make_shared<LifeguardOnTheWhiteBeach>();
                    case 3:
                        return mem::make_shared<GuardianOfBloomingFlowers>();
                    case 4:
                        return mem::make_shared<UnforgivingAvenger>();
                    case 5:
                        return mem::make_shared<SummerGames>();
                    default:
                        return nullopt;
                }
            case SecondaryType::SEASONAL:
                switch (id) {
                    case 0:
                        return nullptr;
                    case 1:
                        return mem::make_shared<SeasonalUltimateWeaponInTheSun>();
                    case 2:
                        return mem::make_shared<SeasonalLifeguardOnTheWhiteBeach>();
                    case 3:
                        return mem::make_shared<SeasonalGuardianOfBloomingFlowers>();
                    case 4:
                        return mem::make_shared<SeasonalUnforgivingAvenger>();
                    default:
                        return nullopt;
                }
            default:
                sys::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();

using openjuice::card::CoopCardFactory;

template <>
struct Formatter<CoopCardFactory::SecondaryType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(CoopCardFactory::SecondaryType type, FormatContext& ctx) {
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
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(CoopCardFactory::SecondaryType);
