/**
 * @file BountyHuntCardFactory.cppm
 * @module openjuice.card:BountyHuntCardFactory
 * @brief Implementation of the BountyHuntCardFactory class.
 *
 * This file contains the implementation of the BountyHuntCardFactory class, which is used to create BountyHuntCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:BountyHuntCardFactory;

import stdx;

import openjuice.engine.card;
import openjuice.engine.managers;
import openjuice.card.bountyhunt;

using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::spawn::BountyHuntCard;

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
            // case AdventurersRadar::ID:
            //     return stdx::mem::make_shared<AdventurersRadar>();
            // case CorrosionBlaster::ID:
            //     return stdx::mem::make_shared<CorrosionBlaster>();
            // case CursedSyrup::ID:
            //     return stdx::mem::make_shared<CursedSyrup>();
            // case FluffyShokupan::ID:
            //     return stdx::mem::make_shared<FluffyShokupan>();
            // case HolyWater::ID:
            //     return stdx::mem::make_shared<HolyWater>();
            // case Lure::ID:
            //     return stdx::mem::make_shared<Lure>();
            // case PoisonBlaster::ID:
            //     return stdx::mem::make_shared<PoisonBlaster>();
            // case Shokupan::ID:
            //     return stdx::mem::make_shared<Shokupan>();
            // case Slimebomb::ID:
            //     return stdx::mem::make_shared<Slimebomb>();
            // case SmokeOfTheLostMemories::ID:
            //     return stdx::mem::make_shared<SmokeOfTheLostMemories>();
            // case SparkleBomb::ID:
            //     return stdx::mem::make_shared<SparkleBomb>();
            // case TeleportationPotion::ID:
            //     return stdx::mem::make_shared<TeleportationPotion>();
            // case VenomBlaster::ID:
            //     return stdx::mem::make_shared<VenomBlaster>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
