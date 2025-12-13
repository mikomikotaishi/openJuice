/**
 * @file MushroomCardFactory.cppm
 * @module openjuice.card.MushroomCardFactory
 * @brief Implementation of the MushroomCardFactory class.
 *
 * This file contains the implementation of the MushroomCardFactory class, which is used to create MushroomCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card.MushroomCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.card.mushroom.LegendaryMushroomCard;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.mushroom;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fmt = std::fmt;
namespace mem = std::mem;

using openjuice::engine::card::LegendaryMushroomColour;
using openjuice::engine::card::MushroomColour;
using openjuice::engine::card::mushroom::LegendaryMushroomCard;
using openjuice::engine::card::spawntypes::MushroomCard;

using namespace openjuice::card::mushroom::legendary;
using namespace openjuice::card::mushroom::regular::battle;
using namespace openjuice::card::mushroom::regular::boost;

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
            case 1:
                return mem::make_shared<SweetBattle>();
            case 2:
                return mem::make_shared<SnowballReflector>();
            case 3:
                return mem::make_shared<GrownupSnowballFight>();
            case 4:
                return mem::make_shared<MiosFalseCake>();
            case 5:
                return mem::make_shared<ChaoticLaunch>();
            case 6:
                return mem::make_shared<ChaosRoost>();
            case 7:
                return mem::make_shared<ChaosProtect>();
            case 8:
                return mem::make_shared<FromTheChaoticAbyss>();
            case 9:
                return mem::make_shared<ChaoticRampage>();
            case 10:
                return mem::make_shared<ChaosRoulette>();
            case 11:
                return mem::make_shared<ChaoticPool>();
            case 12:
                return mem::make_shared<HoldTheGremlin>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
