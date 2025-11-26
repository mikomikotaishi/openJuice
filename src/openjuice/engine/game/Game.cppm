/**
 * @file Game.cppm
 * @module openjuice.engine.game.Game
 * @brief Module file for game operations.
 *
 * This file contains the implementation of the game operations, including state management
 * and thread-safe access to game components.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.Game;

import std;

import openjuice.card.HyperCardFactory;
import openjuice.card.StandardCardFactory;
import openjuice.chat;
import openjuice.engine.board.Board;
import openjuice.engine.entity.Mob;
import openjuice.engine.entity.Player;
import openjuice.engine.game.GamePhase;
import openjuice.engine.game.ecs.Components;
import openjuice.engine.game.ecs.Registry;
import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.unit.Enemy;
import openjuice.engine.unit.Playable;
import openjuice.engine.unit.Unit;
import openjuice.engine.util.Colours;
import openjuice.engine.util.Exceptions;
import openjuice.engine.util.Logging;
import openjuice.unit.BasicEnemyFactory;
import openjuice.unit.BossEnemyFactory;
import openjuice.unit.CharacterFactory;

using std::collections::Vector;
using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::mem::SharedPointer;
using std::mem::UniquePointer;
using std::ranges::IotaView;

namespace fmt = std::fmt;
namespace mem = std::mem;
namespace sys = std::sys;

using openjuice::engine::board::Board;
using openjuice::engine::entity::Player;
using openjuice::engine::game::ecs::EntityId;
using openjuice::engine::game::ecs::Registry;
using openjuice::engine::game::ecs::RegistryError;
using openjuice::engine::managers::GlobalSettings;
using openjuice::engine::unit::Playable;
using openjuice::unit::CharacterFactory;

using namespace openjuice::engine::game::ecs::components;
using namespace openjuice::engine::util::logging;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game);

/**
 * @class Game
 * @brief Class representing the game, including state management.
 *
 * This class unifies game logic and state management with thread-safe access
 * for UI and game threads.
 */
export class Game {
public:
    static constexpr u8 MAX_PLAYERS = Board::MAX_PLAYERS; ///< Maximum number of players.
private:
    static inline const Logger& LOGGER = Logger::getInstance(); ///< The logger instance.

    // Game board and ECS components
    SharedPointer<Board> gameBoard; ///< The game board.
    UniquePointer<Registry> registry; ///< The ECS registry
    Array<EntityId, MAX_PLAYERS> playerEntities; ///< Store player entity IDs

    // Game state variables
    f32 deltaTime;
    GamePhase currentPhase = GamePhase::SETUP;
    u8 currentPlayerIndex = 0;
    u8 chapterNumber = 1;
    Array<SharedPointer<Player>, MAX_PLAYERS> players;
    Vector<EntityId> mobEntities;
    EntityId activeBattleAttacker = 0;
    EntityId activeBattleDefender = 0;
    bool battleInProgress = false;
    String statusMessage;

    /**
     * @brief Advances the game to the next player.
     */
    void advanceToNextPlayer() noexcept {
        currentPlayerIndex = (currentPlayerIndex + 1) % MAX_PLAYERS;
        if (currentPlayerIndex == 0) {
            ++chapterNumber;
        }
    }

public:
    /**
     * @brief Constructor for the Game class.
     */
    Game():
        gameBoard{mem::make_shared<Board>(0)},
        registry{mem::make_unique<Registry>(1000)},
        playerEntities{{}},
        deltaTime{GlobalSettings::getInstance().getDeltaTime()} {

        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Creating Game object");
        #endif
    }

    /**
     * @brief Destructor for the Game class.
     */
    ~Game() {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Destroying Game object");
        #endif
    }

    /**
     * @brief Initialise the game state and prepare for running
     */
    [[nodiscard]]
    Expected<void, RegistryError> init() {
        for (u8 i: IotaView(u8{0}, MAX_PLAYERS)) {
            Optional<EntityId> playerOpt = registry->entity(
                PlayerTag(),
                PlayerComponent(),
                StarComponent(0),
                HandComponent()
            );
            
            if (!playerOpt.has_value()) {
                return Unexpected(RegistryError::ENTITY_CREATE_FAILURE);
            }
            EntityId player = playerOpt.value();
            
            #ifndef NDEBUG
            playerEntities.at(i) = player;
            #else
            playerEntities[i] = player;
            #endif
        }

        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Game initialised");
        #endif

        return {};
    }

    /**
     * @brief Update game state for one frame
     */
    void update() {
        
    }

    /**
     * @brief Sets the character for a player.
     *
     * @param playerNumber The player number.
     * @param characterID The character ID.
     *
     * @throws OutOfRangeException if playerNumber is out of range.
     */
    void setPlayerCharacter(u8 playerNumber, u8 characterId) throws(OutOfRangeException) {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Setting player {} to character of ID {}", playerNumber, characterId);
        #endif

        if (playerNumber >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid player number!");
        }

        EntityId player = getPlayerEntity(playerNumber);
        SharedPointer<Playable> character; 
        if (Optional<SharedPointer<Playable>> ch = CharacterFactory::create(characterId); ch.has_value()) {
            character = *ch;
        } else {
            throw OutOfRangeException(fmt::format("Error: {} is not a valid character ID!", characterId));
        }
        
        registry->emplace<UnitComponent>(player, character);
        registry->emplace<HealthComponent>(player, character->getHealth(), character->getHealth());

        SharedPointer<Player> playerWrapper = mem::make_shared<Player>(*registry, character);

        #ifndef NDEBUG
        players.at(playerNumber) = playerWrapper;
        #else
        players[playerNumber] = playerWrapper;
        #endif
    }

    /**
     * @brief Get the Player Entity object.
     *
     * @param playerNumber Player index.
     * @return EntityId ID of the player entity.
     * 
     * @throws OutOfRangeException if playerNumber is out of range.
     */
    [[nodiscard]]
    EntityId getPlayerEntity(u8 playerNumber) throws(OutOfRangeException) {
        if (playerNumber >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid player number!");
        }

        #ifndef NDEBUG
        return playerEntities.at(playerNumber);
        #else
        return playerEntities[playerNumber];
        #endif
    }

    /**
     * @brief Runs the game.
     */
    void run() {
        LOGGER.log(LogLevel::INFO, "Beginning game");

        currentPhase = GamePhase::PLAYER_TURN;
    }

    /**
     * @brief Get current player.
     *
     * @return SharedPointer<Player> Current player object.
     */
    [[nodiscard]]
    SharedPointer<Player> getCurrentPlayer() const RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        return players.at(currentPlayerIndex);
        #else
        return players[currentPlayerIndex];
        #endif
    }

    /**
     * @brief Get player by index
     *
     * @param index Player index
     * @return Player object at index
     *
     * @throws OutOfRangeException if index is out of range
     */
    [[nodiscard]]
    SharedPointer<Player> getPlayer(u8 index) const throws(OutOfRangeException) {
        if (index >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid index!");
        }

        #ifndef NDEBUG
        return players.at(index);
        #else
        return players[index];
        #endif
    }

    /**
     * @brief Get current game phase
     * @return Current phase
     */
    [[nodiscard]]
    GamePhase getCurrentPhase() const noexcept {
        return currentPhase;
    }

    /**
     * @brief Set current game phase
     * @param phase New phase
     */
    void setCurrentPhase(GamePhase phase) noexcept {
        currentPhase = phase;
    }

    /**
     * @brief Get chapter number
     * @return Current chapter number
     */
    [[nodiscard]]
    u8 getChapterNumber() const noexcept {
        return chapterNumber;
    }

    /**
     * @brief End current player's turn
     */
    void endTurn() noexcept {
        advanceToNextPlayer();
    }

    /**
     * @brief Start a battle between two entities
     *
     * @param attacker The attacking entity
     * @param defender The defending entity
     * @return True if battle started successfully
     */
    bool startBattle(EntityId attacker, EntityId defender) {
        if (battleInProgress) {
            return false;
        }

        activeBattleAttacker = attacker;
        activeBattleDefender = defender;
        battleInProgress = true;
        currentPhase = GamePhase::BATTLE_PHASE;

        return true;
    }

    /**
     * @brief Execute the current battle
     */
    void executeBattle() {
        if (!battleInProgress) {
            return;
        }

        endBattle();
    }

    /**
     * @brief End current battle
     */
    void endBattle() noexcept {
        battleInProgress = false;
        activeBattleAttacker = 0;
        activeBattleDefender = 0;
        currentPhase = GamePhase::PLAYER_TURN;
    }

    /**
     * @brief Check if battle is in progress
     *
     * @return True if battle is ongoing
     */
    [[nodiscard]]
    bool isBattleInProgress() const noexcept {
        return battleInProgress;
    }

    /**
     * @brief Get current battle attacker
     *
     * @return Entity ID of attacker
     */
    [[nodiscard]]
    EntityId getBattleAttacker() const noexcept {
        return activeBattleAttacker;
    }

    /**
     * @brief Get current battle defender
     *
     * @return Entity ID of defender
     */
    [[nodiscard]]
    EntityId getBattleDefender() const noexcept {
        return activeBattleDefender;
    }

    /**
     * @brief Set status message
     *
     * @param message New status message
     */
    void setStatusMessage(const String& message) noexcept {
        statusMessage = message;
    }

    /**
     * @brief Get status message
     *
     * @return Current status message
     */
    [[nodiscard]]
    String getStatusMessage() const noexcept {
        return statusMessage;
    }

    /**
     * @brief Get game board
     *
     * @return Reference to game board
     */
    [[nodiscard]]
    SharedPointer<Board> getBoard() const noexcept {
        return gameBoard;
    }

    /**
     * @brief Add a mob entity to the game
     *
     * @param entityId The mob's entity ID
     */
    void addMob(EntityId entityId) {
        mobEntities.push_back(entityId);
    }

    /**
     * @brief Get all mob entities
     *
     * @return Vector of mob entity IDs
     */
    [[nodiscard]]
    const Vector<EntityId>& getMobs() const noexcept {
        return mobEntities;
    }

    /**
     * @brief Get the ECS registry
     *
     * @return Pointer to the registry
     */
    [[nodiscard]]
    Registry* getRegistry() noexcept {
        return registry.get();
    }

    /**
     * @brief Convert game state to string representation
     *
     * @return String representation of game state
     */
    [[nodiscard]]
    String toString() const {
        String result = fmt::format(
            "Chapter: {} | Current Player: {} | Phase: {} | Battle: {}",
            chapterNumber,
            currentPlayerIndex,
            currentPhase,
            battleInProgress ? "Yes" : "No"
        );

        if (!statusMessage.empty()) {
            result = fmt::format("{} | {}", result, statusMessage);
        }

        return result;
    }
};

END_MODULE_NAMESPACE();
