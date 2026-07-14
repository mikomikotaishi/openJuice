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
import openjuice.engine.services;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

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
public:
    GenericCardFactory() = delete("GenericCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a GenericCard object with the given ID.
     * @param type Type of the GenericCard to create
     * @return Shared pointer to the created GenericCard object
     */
    [[nodiscard]]
    static constexpr SharedPointer<GenericCard> create(Card::Of type) noexcept {
        switch (type) {
            case Card::Of::BATTLE:
                return Pointers::shared<GenericBattleCard>();
            case Card::Of::BOOST:
                return Pointers::shared<GenericBoostCard>();
            case Card::Of::TRAP:
                return Pointers::shared<GenericTrapCard>();
            case Card::Of::EVENT:
                return Pointers::shared<GenericEventCard>();
            case Card::Of::GIFT:
                return Pointers::shared<GenericGiftCard>();
            case Card::Of::BANNER:
                return Pointers::shared<GenericBannerCard>();
        }
        Ops::unreachable();
    }
};

END_MODULE_NAMESPACE();
