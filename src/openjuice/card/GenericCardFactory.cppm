/**
 * @file GenericCardFactory.cppm
 * @module openjuice.card:GenericCardFactory
 * @brief Implementation of the GenericCardFactory class.
 *
 * This file contains the implementation of the GenericCardFactory class, which is used to create GenericCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:GenericCardFactory;

import std;
import stdx;

import openjuice.engine.card;
import openjuice.engine.managers;
import openjuice.card.generic;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::Card;
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
    static Optional<SharedPointer<GenericCard>> create(Card::Type type) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating GenericCard of type: {}", type);
        #endif

        switch (type) {
            case Card::Type::BATTLE:
                return std::mem::make_shared<GenericBattleCard>();
            case Card::Type::BOOST:
                return std::mem::make_shared<GenericBoostCard>();
            case Card::Type::TRAP:
                return std::mem::make_shared<GenericTrapCard>();
            case Card::Type::EVENT:
                return std::mem::make_shared<GenericEventCard>();
            case Card::Type::GIFT:
                return std::mem::make_shared<GenericGiftCard>();
            case Card::Type::BANNER:
                return std::mem::make_shared<GenericBannerCard>();
            default:
                std::sys::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();
