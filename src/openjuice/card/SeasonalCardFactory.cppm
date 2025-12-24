/**
 * @file SeasonalCardFactory.cppm
 * @module openjuice.card:SeasonalCardFactory
 * @brief Implementation of the SeasonalCardFactory class.
 *
 * This file contains the implementation of the SeasonalCardFactory class, which is used to create SeasonalCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:SeasonalCardFactory;

import std;
import stdx;

import openjuice.engine.card;
import openjuice.engine.managers;
import openjuice.card.seasonal;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::spawntypes::SeasonalCard;

using namespace openjuice::card::seasonal;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class SeasonalCardFactory
 * @brief Factory class for creating SeasonalCard objects.
 *
 * The SeasonalCardFactory class is a singleton factory class that creates SeasonalCard objects based on the given ID.
 */
export class SeasonalCardFactory final {
private:
    UTILITY_CLASS(SeasonalCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("SeasonalCardFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a SeasonalCard object with the given ID.
     *
     * @param id ID of the SeasonalCard to create
     * @return Shared pointer to the created SeasonalCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<SeasonalCard>> create(u8 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating SeasonalCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            case SweetBattle::ID:
                return std::mem::make_shared<SweetBattle>();
            case SnowballReflector::ID:
                return std::mem::make_shared<SnowballReflector>();
            case GrownupSnowballFight::ID:
                return std::mem::make_shared<GrownupSnowballFight>();
            case MiosFalseCake::ID:
                return std::mem::make_shared<MiosFalseCake>();
            case ChaoticLaunch::ID:
                return std::mem::make_shared<ChaoticLaunch>();
            case ChaosRoost::ID:
                return std::mem::make_shared<ChaosRoost>();
            case ChaosProtect::ID:
                return std::mem::make_shared<ChaosProtect>();
            case FromTheChaoticAbyss::ID:
                return std::mem::make_shared<FromTheChaoticAbyss>();
            case ChaoticRampage::ID:
                return std::mem::make_shared<ChaoticRampage>();
            case ChaosRoulette::ID:
                return std::mem::make_shared<ChaosRoulette>();
            case ChaoticPool::ID:
                return std::mem::make_shared<ChaoticPool>();
            case HoldTheGremlin::ID:
                return std::mem::make_shared<HoldTheGremlin>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
