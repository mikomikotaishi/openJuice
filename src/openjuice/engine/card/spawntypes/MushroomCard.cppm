/**
 * @file MushroomCard.cppm
 * @module openjuice.engine.card.SpawnTypes:MushroomCard
 * @brief Definition of the MushroomCard abstract class.
 *
 * This file contains the definition of the MushroomCard abstract class, which represents a Mushroom card in the game.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.card.SpawnTypes:MushroomCard;

import std;

import openjuice.engine.card.Card;

using std::meta::IsBaseOfValue;

using openjuice::engine::card::Card;

BEGIN_MODULE_NAMESPACE(openjuice::engine::card::spawntypes);

/**
 * @class MushroomCard
 * @brief Abstract class representing a Mushroom card.
 *
 * @extends Card
 * 
 * The MushroomCard abstract class extends the Card abstract class and represents a Mushroom card with specific attributes.
 */
export class MushroomCard: virtual public Card {
protected:
    // Uses "CARD_SHROOM_BLUE" because all (regular) mushroom cards have the same description.
    static constexpr char EFFECT_KEY[] = "CARD_SHROOM_BLUE"; ///< The key belonging to the effect to query in TextManager

    /**
     * @brief Default constructor for MushroomCard.
     */
    MushroomCard() = default;
public:
    static constexpr u8 NUM_MUSHROOMS = 10; ///< The number of mushroom cards in the game
    static constexpr u8 NUM_LEGENDARY_MUSHROOMS = 2; ///< The number of legendary mushroom cards in the game
};

/**
 * @concept ExtendsMushroomCard
 * @brief Concept that checks if a type extends the MushroomCard class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsMushroomCard = IsBaseOfValue<MushroomCard, T>;

END_MODULE_NAMESPACE();
