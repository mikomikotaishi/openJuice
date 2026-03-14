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

import openjuice.engine.card;
import openjuice.engine.card.mushroom;
import openjuice.engine.managers;
import openjuice.card.mushroom;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

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
private:
    UTILITY_CLASS(MushroomCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("MushroomCardFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a MushroomCard object with the given ID.
     *
     * @param id ID of the MushroomCard to create
     * @param colour Colour of the card to create
     * @return Shared pointer to the created MushroomCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<MushroomCard>> create(u8 id, MushroomCard::Colour colour) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating MushroomCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            case NullBattleMushroom::ID:
                return Pointers::shared<NullBattleMushroom>(colour);
            case AttackUpMushroom::ID:
                return Pointers::shared<AttackUpMushroom>(colour);
            case AttackDownMushroom::ID:
                return Pointers::shared<AttackDownMushroom>(colour);
            case DefenceUpMushroom::ID:
                return Pointers::shared<DefenceUpMushroom>(colour);
            case DefenceDownMushroom::ID:
                return Pointers::shared<DefenceDownMushroom>(colour);
            case EvadeUpMushroom::ID:
                return Pointers::shared<EvadeUpMushroom>(colour);
            case EvadeDownMushroom::ID:
                return Pointers::shared<EvadeDownMushroom>(colour);
            case HealMushroom::ID:
                return Pointers::shared<HealMushroom>(colour);
            case DamageMushroom::ID:
                return Pointers::shared<DamageMushroom>(colour);
            case RollOneMushroom::ID:
                return Pointers::shared<RollOneMushroom>(colour);
            case RollSixMushroom::ID:
                return Pointers::shared<RollSixMushroom>(colour);
            case NullBoostMushroom::ID:
                return Pointers::shared<NullBoostMushroom>(colour);
            case MoveUpMushroom::ID:
                return Pointers::shared<MoveUpMushroom>(colour);
            case MoveDownMushroom::ID:
                return Pointers::shared<MoveDownMushroom>(colour);
            case GainStarsMushroom::ID:
                return Pointers::shared<GainStarsMushroom>(colour);
            case LoseStarsMushroom::ID:
                return Pointers::shared<LoseStarsMushroom>(colour);
            case HealthUpMushroom::ID:
                return Pointers::shared<HealthUpMushroom>(colour);
            case HealthDownMushroom::ID:
                return Pointers::shared<HealthDownMushroom>(colour);
            case FrostwalkerMushroom::ID:
                return Pointers::shared<FrostwalkerMushroom>(colour);
            case WarpMushroom::ID:
                return Pointers::shared<WarpMushroom>(colour);
            case ConfusionMushroom::ID:
                return Pointers::shared<ConfusionMushroom>(colour);
            case DrawMushroom::ID:
                return Pointers::shared<DrawMushroom>(colour);
            case DiscardMushroom::ID:
                return Pointers::shared<DiscardMushroom>(colour);
            case WinMushroom::ID:
                return Pointers::shared<WinMushroom>(colour);
            default:
                return nullopt;
        }
    }


    /**
     * @brief Create a LegendaryMushroomCard object with the given ID.
     *
     * @param id ID of the LegendaryMushroomCard to create
     * @param colour Colour of the card to create
     * @return Shared pointer to the created LegendaryMushroomCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<LegendaryMushroomCard>> create(u8 id, LegendaryMushroomCard::Colour colour) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating LegendaryMushroomCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            case LegendaryStarsMushroom::ID:
                return Pointers::shared<LegendaryStarsMushroom>(colour);
            case LegendaryWinsMushroom::ID:
                return Pointers::shared<LegendaryWinsMushroom>(colour);
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
