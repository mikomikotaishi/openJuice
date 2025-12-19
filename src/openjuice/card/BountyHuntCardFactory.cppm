/**
 * @file BountyHuntCardFactory.cppm
 * @module openjuice.card.BountyHuntCardFactory
 * @brief Implementation of the BountyHuntCardFactory class.
 *
 * This file contains the implementation of the BountyHuntCardFactory class, which is used to create BountyHuntCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card.BountyHuntCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.bountyhunt;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::spawntypes::BountyHuntCard;

// using namespace openjuice::card::bountyhunt;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class BountyHuntCardFactory
 * @brief Factory class for creating BountyHuntCard objects.
 *
 * The BountyHuntCardFactory class is a singleton factory class that creates BountyHuntCard objects based on the given ID.
 */
export class BountyHuntCardFactory final {
private:
    UTILITY_CLASS(BountyHuntCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("BountyHuntCardFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a BountyHuntCard object with the given ID.
     *
     * @param id ID of the BountyHuntCard to create
     * @return Shared pointer to the created BountyHuntCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BountyHuntCard>> create(u8 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating BountyHuntCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            // case 1:
            //     return std::mem::make_shared<AdventurersRadar>();
            // case 2:
            //     return std::mem::make_shared<CorrosionBlaster>();
            // case 3:
            //     return std::mem::make_shared<CursedSyrup>();
            // case 4:
            //     return std::mem::make_shared<FluffyShokupan>();
            // case 5:
            //     return std::mem::make_shared<HolyWater>();
            // case 6:
            //     return std::mem::make_shared<Lure>();
            // case 7:
            //     return std::mem::make_shared<PoisonBlaster>();
            // case 8:
            //     return std::mem::make_shared<Shokupan>();
            // case 9:
            //     return std::mem::make_shared<Slimebomb>();
            // case 10:
            //     return std::mem::make_shared<SmokeOfTheLostMemories>();
            // case 11:
            //     return std::mem::make_shared<SparkleBomb>();
            // case 12:
            //     return std::mem::make_shared<TeleportationPotion>();
            // case 13:
            //     return std::mem::make_shared<VenomBlaster>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
