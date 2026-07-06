/**
 * @file MushroomCardFactory.cppm
 * @module openjuice.card:MushroomCardFactory
 * @brief Implementation of the MushroomCardFactory class.
 *
 * This file contains the implementation of the MushroomCardFactory class, which is used to create MushroomCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:MushroomCardFactory;

import stdx;

import :mushroom;

import openjuice.engine.card;
import openjuice.engine.card.mushroom;
import openjuice.engine.services;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::mushroom::LegendaryMushroomCard;
using openjuice::engine::card::spawn::MushroomCard;

using namespace openjuice::card::mushroom::legendary;
using namespace openjuice::card::mushroom::regular::battle;
using namespace openjuice::card::mushroom::regular::boost;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class MushroomCardFactory
 * @brief Factory class for creating MushroomCard objects.
 *
 * The MushroomCardFactory class is a singleton factory class that creates MushroomCard and LegendaryMushroomCard objects based on the given ID.
 */
export class MushroomCardFactory final {
public:
    MushroomCardFactory() = delete("MushroomCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a MushroomCard object with the given ID.
     *
     * @param id ID of the MushroomCard to create
     * @param color Color of the card to create
     * @return Shared pointer to the created MushroomCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<MushroomCard>> create(u8 id, MushroomCard::Color color) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            case NullBattleMushroom::ID:
                return Pointers::shared<NullBattleMushroom>(color);
            case AttackUpMushroom::ID:
                return Pointers::shared<AttackUpMushroom>(color);
            case AttackDownMushroom::ID:
                return Pointers::shared<AttackDownMushroom>(color);
            case DefenseUpMushroom::ID:
                return Pointers::shared<DefenseUpMushroom>(color);
            case DefenseDownMushroom::ID:
                return Pointers::shared<DefenseDownMushroom>(color);
            case EvadeUpMushroom::ID:
                return Pointers::shared<EvadeUpMushroom>(color);
            case EvadeDownMushroom::ID:
                return Pointers::shared<EvadeDownMushroom>(color);
            case HealMushroom::ID:
                return Pointers::shared<HealMushroom>(color);
            case DamageMushroom::ID:
                return Pointers::shared<DamageMushroom>(color);
            case RollOneMushroom::ID:
                return Pointers::shared<RollOneMushroom>(color);
            case RollSixMushroom::ID:
                return Pointers::shared<RollSixMushroom>(color);
            case NullBoostMushroom::ID:
                return Pointers::shared<NullBoostMushroom>(color);
            case MoveUpMushroom::ID:
                return Pointers::shared<MoveUpMushroom>(color);
            case MoveDownMushroom::ID:
                return Pointers::shared<MoveDownMushroom>(color);
            case GainStarsMushroom::ID:
                return Pointers::shared<GainStarsMushroom>(color);
            case LoseStarsMushroom::ID:
                return Pointers::shared<LoseStarsMushroom>(color);
            case HealthUpMushroom::ID:
                return Pointers::shared<HealthUpMushroom>(color);
            case HealthDownMushroom::ID:
                return Pointers::shared<HealthDownMushroom>(color);
            case FrostwalkerMushroom::ID:
                return Pointers::shared<FrostwalkerMushroom>(color);
            case WarpMushroom::ID:
                return Pointers::shared<WarpMushroom>(color);
            case ConfusionMushroom::ID:
                return Pointers::shared<ConfusionMushroom>(color);
            case DrawMushroom::ID:
                return Pointers::shared<DrawMushroom>(color);
            case DiscardMushroom::ID:
                return Pointers::shared<DiscardMushroom>(color);
            case WinMushroom::ID:
                return Pointers::shared<WinMushroom>(color);
            default:
                return nullopt;
        }
    }


    /**
     * @brief Create a LegendaryMushroomCard object with the given ID.
     *
     * @param id ID of the LegendaryMushroomCard to create
     * @param color Color of the card to create
     * @return Shared pointer to the created LegendaryMushroomCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<LegendaryMushroomCard>> create(u8 id, LegendaryMushroomCard::Color color) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            case LegendaryStarsMushroom::ID:
                return Pointers::shared<LegendaryStarsMushroom>(color);
            case LegendaryWinsMushroom::ID:
                return Pointers::shared<LegendaryWinsMushroom>(color);
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
