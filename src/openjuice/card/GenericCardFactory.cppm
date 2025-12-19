/**
 * @file GenericCardFactory.cppm
 * @module openjuice.card.GenericCardFactory
 * @brief Implementation of the GenericCardFactory class.
 *
 * This file contains the implementation of the GenericCardFactory class, which is used to create GenericCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card.GenericCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.generic;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::CardType;
using openjuice::engine::card::spawntypes::GenericCard;

using namespace openjuice::card::generic;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class GenericCardFactory
 * @brief Factory class for creating GenericCard objects.
 *
 * The GenericCardFactory class is a singleton factory class that creates GenericCard objects based on the given ID.
 */
export class GenericCardFactory final {
private:
    UTILITY_CLASS(GenericCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("GenericCardFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a GenericCard object with the given ID.
     *
     * @param type Type of the GenericCard to create
     * @return Shared pointer to the created GenericCard object
     */
    [[nodiscard]]
    static Optional<SharedPointer<GenericCard>> create(CardType type) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating GenericCard of type: {}", type);
        #endif

        switch (type) {
            case CardType::BATTLE:
                return std::mem::make_shared<GenericBattleCard>();
            case CardType::BOOST:
                return std::mem::make_shared<GenericBoostCard>();
            case CardType::TRAP:
                return std::mem::make_shared<GenericTrapCard>();
            case CardType::EVENT:
                return std::mem::make_shared<GenericEventCard>();
            case CardType::GIFT:
                return std::mem::make_shared<GenericGiftCard>();
            case CardType::BANNER:
                return std::mem::make_shared<GenericBannerCard>();
            default:
                std::sys::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();
