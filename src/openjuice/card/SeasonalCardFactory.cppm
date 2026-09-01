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

import :seasonal;

import stdx;

import openjuice.engine.card;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::spawn::SeasonalCard;

using namespace openjuice::card::seasonal;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class SeasonalCardFactory
 * @brief Factory class for creating SeasonalCard objects.
 *
 * The SeasonalCardFactory class is a singleton factory class that creates SeasonalCard objects based on the given ID.
 */
export class SeasonalCardFactory final {
public:
    SeasonalCardFactory() = delete("SeasonalCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a SeasonalCard object with the given ID.
     * @param id ID of the SeasonalCard to create
     * @return Shared pointer to the created SeasonalCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static constexpr Optional<SharedPointer<SeasonalCard>> create(u8 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            case SweetBattle::ID:
                return Pointers::shared<SweetBattle>();
            case SnowballReflector::ID:
                return Pointers::shared<SnowballReflector>();
            case GrownupSnowballFight::ID:
                return Pointers::shared<GrownupSnowballFight>();
            case MiosFalseCake::ID:
                return Pointers::shared<MiosFalseCake>();
            case ChaoticLaunch::ID:
                return Pointers::shared<ChaoticLaunch>();
            case ChaosRoost::ID:
                return Pointers::shared<ChaosRoost>();
            case ChaosProtect::ID:
                return Pointers::shared<ChaosProtect>();
            case FromTheChaoticAbyss::ID:
                return Pointers::shared<FromTheChaoticAbyss>();
            case ChaoticRampage::ID:
                return Pointers::shared<ChaoticRampage>();
            case ChaosRoulette::ID:
                return Pointers::shared<ChaosRoulette>();
            case ChaoticPool::ID:
                return Pointers::shared<ChaoticPool>();
            case HoldTheGremlin::ID:
                return Pointers::shared<HoldTheGremlin>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
