/**
 * @file boost.cppm
 * @module openjuice.card.mushroom.regular.boost
 * @brief Import of all Boost Mushroom Cards.
 *
 * This file imports the modules for all Boost Mushroom Cards.
 */

module;

#include "Macros.hpp"

export module openjuice.card:mushroom.regular.boost;

import stdx;

import openjuice.engine.card;

using openjuice::engine::card::Card;
using openjuice::engine::card::mushroom::BoostMushroomCard;

using namespace openjuice::engine::card::spawn;
using namespace openjuice::engine::card::type;

BEGIN_MODULE_NAMESPACE(openjuice::card::mushroom::regular::boost);

/**
 * @class NullBoostMushroom
 * @brief Class representing the NullBoostMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The NullBoostMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::NULL_BOOST effect in the game.
 */
export class NullBoostMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::NULL_BOOST); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a NullBoostMushroom object.
     */
    NullBoostMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, NULL_BOOST) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class MoveUpMushroom
 * @brief Class representing the MoveUpMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The MoveUpMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::MOVE_UP effect in the game.
 */
export class MoveUpMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_MOVEUP")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::MOVE_UP); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a MoveUpMushroom object.
     */
    MoveUpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, MOVE_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class MoveDownMushroom
 * @brief Class representing the MoveDownMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The MoveDownMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::MOVE_DOWN effect in the game.
 */
export class MoveDownMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_MOVEDOWN")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::MOVE_DOWN); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a MoveDownMushroom object.
     */
    MoveDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, MOVE_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class GainStarsMushroom
 * @brief Class representing the GainStarsMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The GainStarsMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::GAIN_STARS effect in the game.
 */
export class GainStarsMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_GAINSTARS")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::GAIN_STARS); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a GainStarsMushroom object.
     */
    GainStarsMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, GAIN_STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class LoseStarsMushroom
 * @brief Class representing the LoseStarsMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The LoseStarsMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::LOSE_STARS effect in the game.
 */
export class LoseStarsMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_LOSESTARS")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::LOSE_STARS); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a LoseStarsMushroom object.
     */
    LoseStarsMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, LOSE_STARS) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HealthUpMushroom
 * @brief Class representing the HealthUpMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The HealthUpMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::HEALTH_UP effect in the game.
 */
export class HealthUpMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_HEALTHUP")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::HEALTH_UP); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a HealthUpMushroom object.
     */
    HealthUpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, HEALTH_UP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class HealthDownMushroom
 * @brief Class representing the HealthDownMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The HealthDownMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::HEALTH_DOWN effect in the game.
 */
export class HealthDownMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_HEALTHDOWN")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::HEALTH_DOWN); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a HealthDownMushroom object.
     */
    HealthDownMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, HEALTH_DOWN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class FrostwalkerMushroom
 * @brief Class representing the FrostwalkerMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The FrostwalkerMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::FROSTWALKER effect in the game.
 */
export class FrostwalkerMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_FROSTWALKER")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::FROSTWALKER); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a FrostwalkerMushroom object.
     */
    FrostwalkerMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, FROSTWALKER) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class WarpMushroom
 * @brief Class representing the WarpMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The WarpMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::WARP effect in the game.
 */
export class WarpMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_WARP")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::WARP); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a WarpMushroom object.
     */
    WarpMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, WARP) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class ConfusionMushroom
 * @brief Class representing the ConfusionMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The ConfusionMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::CONFUSION effect in the game.
 */
export class ConfusionMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_CONFUSION")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::CONFUSION); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a ConfusionMushroom object.
     */
    ConfusionMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, CONFUSION) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class DrawMushroom
 * @brief Class representing the DrawMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The DrawMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::DRAW effect in the game.
 */
export class DrawMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DRAW")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::DRAW); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a DrawMushroom object.
     */
    DrawMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, DRAW) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class DiscardMushroom
 * @brief Class representing the DiscardMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The DiscardMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::DISCARD effect in the game.
 */
export class DiscardMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_DISCARD")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::DISCARD); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a DiscardMushroom object.
     */
    DiscardMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, DISCARD) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

/**
 * @class WinMushroom
 * @brief Class representing the WinMushroom card.
 *
 * @extends BoostMushroomCard
 *
 * The WinMushroom class extends BoostMushroomCard to represent the card 
 * providing the BoostMushroomCard::Effect::WIN effect in the game.
 */
export class WinMushroom final: public BoostMushroomCard {
private:
    MUSHROOM_METADATA("CARD_SHROOM_WIN")
public:
    static constexpr u16 ID = Ops::to_underlying(BoostMushroomCard::Effect::WIN); ///< The ID of this specific card
    static constexpr Card::Of CARD_TYPE = Card::Of::BOOST; ///< The card type of this specific card
    static constexpr Card::Spawn SPAWN_TYPE = Card::Spawn::MUSHROOM; ///< The spawn type of this specific card
    static constexpr Optional<Card::Rarity> RARITY = nullopt; ///< The rarity of this specific card
    static constexpr Optional<u16> COST = 0; ///< The cost of this specific card
    static constexpr u8 LEVEL = 0; ///< The level of this specific card
    static constexpr Optional<u8> LIMIT = nullopt; ///< The limit of this specific card per deck
    static constexpr Expected<u8, Card::DeckPointError> DECK_POINTS = Unexpected(Card::DeckPointError::NOT_STANDARD_CARD); ///< The deck points of this specific card

    /**
     * @brief Constructor to initialise a WinMushroom object.
     */
    WinMushroom(MushroomCard::Colour colour):
        SET_MUSHROOM_STATS(Boost, WIN) {}

    /**
     * @brief Play the card.
     */
    void play() const noexcept override final {

    }
};

END_MODULE_NAMESPACE();
