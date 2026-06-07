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

import stdx;

import :generic;

import openjuice.engine.card;
import openjuice.engine.managers;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::Card;
using openjuice::engine::card::spawn::GenericCard;

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
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("GenericCardFactory"); ///< The logger instance.
public:
    GenericCardFactory() = delete("GenericCardFactory is a utility class and cannot be instantiated.");

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
                return Pointers::shared<GenericBattleCard>();
            case Card::Type::BOOST:
                return Pointers::shared<GenericBoostCard>();
            case Card::Type::TRAP:
                return Pointers::shared<GenericTrapCard>();
            case Card::Type::EVENT:
                return Pointers::shared<GenericEventCard>();
            case Card::Type::GIFT:
                return Pointers::shared<GenericGiftCard>();
            case Card::Type::BANNER:
                return Pointers::shared<GenericBannerCard>();
            default:
                Ops::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();
