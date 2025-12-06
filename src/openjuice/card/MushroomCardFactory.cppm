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
    static Optional<SharedPointer<MushroomCard>> create(u8 id, MushroomColour colour) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating MushroomCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            case 1:
                return mem::make_shared<NullBattleMushroom>(colour);
            case 2:
                return mem::make_shared<AttackUpMushroom>(colour);
            case 3:
                return mem::make_shared<AttackDownMushroom>(colour);
            case 4:
                return mem::make_shared<DefenceUpMushroom>(colour);
            case 5:
                return mem::make_shared<DefenceDownMushroom>(colour);
            case 6:
                return mem::make_shared<EvadeUpMushroom>(colour);
            case 7:
                return mem::make_shared<EvadeDownMushroom>(colour);
            case 8:
                return mem::make_shared<HealMushroom>(colour);
            case 9:
                return mem::make_shared<DamageMushroom>(colour);
            case 10:
                return mem::make_shared<RollOneMushroom>(colour);
            case 11:
                return mem::make_shared<RollSixMushroom>(colour);
            case 12:
                return mem::make_shared<NullBoostMushroom>(colour);
            case 13:
                return mem::make_shared<MoveUpMushroom>(colour);
            case 14:
                return mem::make_shared<MoveDownMushroom>(colour);
            case 15:
                return mem::make_shared<GainStarsMushroom>(colour);
            case 16:
                return mem::make_shared<LoseStarsMushroom>(colour);
            case 17:
                return mem::make_shared<HealthUpMushroom>(colour);
            case 18:
                return mem::make_shared<HealthDownMushroom>(colour);
            case 19:
                return mem::make_shared<FrostwalkerMushroom>(colour);
            case 20:
                return mem::make_shared<WarpMushroom>(colour);
            case 21:
                return mem::make_shared<ConfusionMushroom>(colour);
            case 22:
                return mem::make_shared<DrawMushroom>(colour);
            case 23:
                return mem::make_shared<DiscardMushroom>(colour);
            case 24:
                return mem::make_shared<WinMushroom>(colour);
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
    static Optional<SharedPointer<LegendaryMushroomCard>> create(u8 id, LegendaryMushroomColour colour) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating LegendaryMushroomCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            case 1:
                return mem::make_shared<LegendaryStarsMushroom>(colour);
            case 2:
                return mem::make_shared<LegendaryWinsMushroom>(colour);
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
