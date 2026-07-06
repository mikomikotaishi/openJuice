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

import :bountyhunt;

import openjuice.engine.card;
import openjuice.engine.services;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

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
public:
    BountyHuntCardFactory() = delete("BountyHuntCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a BountyHuntCard object with the given ID.
     *
     * @param id ID of the BountyHuntCard to create
     * @return Shared pointer to the created BountyHuntCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BountyHuntCard>> create(u8 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            // case AdventurersRadar::ID:
            //     return Pointers::shared<AdventurersRadar>();
            // case CorrosionBlaster::ID:
            //     return Pointers::shared<CorrosionBlaster>();
            // case CursedSyrup::ID:
            //     return Pointers::shared<CursedSyrup>();
            // case FluffyShokupan::ID:
            //     return Pointers::shared<FluffyShokupan>();
            // case HolyWater::ID:
            //     return Pointers::shared<HolyWater>();
            // case Lure::ID:
            //     return Pointers::shared<Lure>();
            // case PoisonBlaster::ID:
            //     return Pointers::shared<PoisonBlaster>();
            // case Shokupan::ID:
            //     return Pointers::shared<Shokupan>();
            // case Slimebomb::ID:
            //     return Pointers::shared<Slimebomb>();
            // case SmokeOfTheLostMemories::ID:
            //     return Pointers::shared<SmokeOfTheLostMemories>();
            // case SparkleBomb::ID:
            //     return Pointers::shared<SparkleBomb>();
            // case TeleportationPotion::ID:
            //     return Pointers::shared<TeleportationPotion>();
            // case VenomBlaster::ID:
            //     return Pointers::shared<VenomBlaster>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
