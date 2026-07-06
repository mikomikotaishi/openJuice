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

import stdx;

import :GamePhase;

import openjuice.card;
import openjuice.chat;
import openjuice.engine.board;
import openjuice.engine.entity;
import openjuice.engine.game.ecs;
import openjuice.engine.services;
import openjuice.engine.unit;
import openjuice.engine.util;
import openjuice.unit;

using stdx::collections::Vector;
using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::ranges::IotaView;
using stdx::time::Milliseconds;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::board::Board;
using openjuice::engine::entity::Player;
using openjuice::engine::game::ecs::EntityId;
using openjuice::engine::game::ecs::Registry;
using openjuice::engine::services::ConfigurationService;
using openjuice::engine::unit::Playable;
using openjuice::engine::util::Constants;
using openjuice::unit::CharacterFactory;

using namespace openjuice::engine::game::ecs::components;

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
    static constexpr u8 MAX_PLAYERS = Constants::GAME_MAX_PLAYERS; ///< Maximum number of players.

    /**
     * @enum Phase
     * @brief Enumeration of game phases
     */
    enum class Phase: u8 {
        SETUP, ///< Initial game setup
        PLAYER_TURN, ///< Player taking their turn
        BATTLE_PHASE, ///< Battle in progress
        CHAPTER_PHASE, ///< Chapter event in progress
        END_GAME, ///< Game completed
        PAUSED, ///< Game paused
    };
private:
    friend class Formatter<Phase>;
    SharedPointer<LoggerFactory> loggerFactory; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The logger instance.

    // Game board and ECS components (ordered by size for optimal padding)
    Array<SharedPointer<Player>, MAX_PLAYERS> players; ///< Player array
    String statusMessage; ///< Status message
    Vector<EntityId> mobEntities; ///< Mob entities
    SharedPointer<Board> gameBoard; ///< The game board (null until a board is loaded for a match)
    Array<EntityId, MAX_PLAYERS> playerEntities; ///< Store player entity IDs
    UniquePointer<Registry> registry; ///< The ECS registry
    Milliseconds deltaTime; ///< Delta time
    EntityId activeBattleAttacker = 0; ///< Battle attacker
    EntityId activeBattleDefender = 0; ///< Battle defender
    Phase currentPhase = Phase::SETUP; ///< Current phase
    u8 currentPlayerIndex = 0; ///< Current player index
    u8 chapterNumber = 1; ///< Chapter number
    bool battleInProgress = false; ///< Battle in progress flag
    // TODO: Add a spectator list

    /**
     * @brief Advances the game to the next player.
     */
    void advanceToNextPlayer() noexcept {
        currentPlayerIndex = (currentPlayerIndex + 1) % MAX_PLAYERS;
        if (currentPlayerIndex == 0) {
            ++chapterNumber;
        }
    }

    [[nodiscard]]
    constexpr static StringView phaseName(Phase phase) noexcept {
        switch (phase) {
            case Phase::SETUP:
                return "Setup";
            case Phase::PLAYER_TURN:
                return "Player Turn";
            case Phase::BATTLE_PHASE:
                return "Battle";
            case Phase::CHAPTER_PHASE:
                return "Chapter Event";
            case Phase::END_GAME:
                return "End Game";
            case Phase::PAUSED:
                return "Paused";
        }
        Ops::unreachable();
    }
public:
    /**
     * @brief Constructor for the Game class.
     *
     * @param loggerFactory The injected logger factory.
     * @param config The injected configuration service, used to determine the frame delta-time.
     */
    explicit Game(SharedPointer<LoggerFactory> loggerFactory, SharedPointer<ConfigurationService> config):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("Game")},
        playerEntities{{}},
        registry{Pointers::unique<Registry>(1000)},
        deltaTime{config->getDeltaTime()} {

        #ifndef NDEBUG
        logger->debug("Creating Game object");
        #endif
    }

    /**
     * @brief Destructor for the Game class.
     */
    ~Game() {
        #ifndef NDEBUG
        logger->debug("Destroying Game object");
        #endif
    }

    /**
     * @brief Initialize the game state and prepare for running
     */
    [[nodiscard]]
    Expected<void, Registry::Error> init() {
        for (u8 i: IotaView(u8{0}, MAX_PLAYERS)) {
            Optional<EntityId> playerOpt = registry->entity(
                PlayerTag(),
                PlayerComponent(),
                StarComponent(0),
                HandComponent()
            );
            
            if (!playerOpt.has_value()) {
                return Unexpected(Registry::Error::ENTITY_CREATE_FAILURE);
            }
            EntityId player = playerOpt.value();
            
            #ifndef NDEBUG
            playerEntities.at(i) = player;
            #else
            playerEntities[i] = player;
            #endif
        }

        #ifndef NDEBUG
        logger->debug("Game initialized");
        #endif

        return {};
    }

    /**
     * @brief Update game state for one frame
     */
    void update() {
        
    }

    [[nodiscard]]
    Phase getCurrentPhase() const noexcept {
        return currentPhase;
    }

    [[nodiscard]]
    u8 getChapterNumber() const noexcept {
        return chapterNumber;
    }

    /**
     * @brief Sets the character for a player.
     *
     * @param num The player number.
     * @param id The character ID.
     *
     * @throws OutOfRangeException if playerNumber is out of range.
     */
    void setPlayerCharacter(u8 num, u8 id) throws (OutOfRangeException) {
        #ifndef NDEBUG
        logger->debug("Setting player {} to character of ID {}", num, id);
        #endif

        if (num >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid player number!");
        }

        EntityId player = getPlayerEntity(num);
        SharedPointer<Playable> character; 
        if (Optional<SharedPointer<Playable>> ch = CharacterFactory::create(id); ch.has_value()) {
            character = *ch;
        } else {
            throw OutOfRangeException(stdx::fmt::format("Error: {} is not a valid character ID!", id));
        }
        
        registry->emplace<UnitComponent>(player, character);
        registry->emplace<HealthComponent>(player, character->getHealth(), character->getHealth());

        SharedPointer<Player> playerWrapper = Pointers::shared<Player>(*registry, character);

        #ifndef NDEBUG
        players.at(num) = playerWrapper;
        #else
        players[num] = playerWrapper;
        #endif
    }

    /**
     * @brief Get the Player Entity object.
     *
     * @param num Player index.
     * @return EntityId ID of the player entity.
     * 
     * @throws OutOfRangeException if playerNumber is out of range.
     */
    [[nodiscard]]
    EntityId getPlayerEntity(u8 num) throws (OutOfRangeException) {
        if (num >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid player number!");
        }

        #ifndef NDEBUG
        return playerEntities.at(num);
        #else
        return playerEntities[num];
        #endif
    }

    /**
     * @brief Runs the game.
     */
    void run() {
        logger->info("Beginning game");

        currentPhase = Phase::PLAYER_TURN;
    }

    /**
     * @brief Get current player.
     *
     * @return SharedPointer<Player> Current player object.
     * @throws OutOfRangeException if currentPlayerIndex is out of range.
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
     * @throws OutOfRangeException if index is out of range
     */
    [[nodiscard]]
    SharedPointer<Player> getPlayer(u8 index) const throws (OutOfRangeException) {
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
        currentPhase = Phase::BATTLE_PHASE;

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
        currentPhase = Phase::PLAYER_TURN;
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
     * @param id The mob's entity ID
     */
    void addMob(EntityId id) {
        mobEntities.push_back(id);
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
     * @return Reference to the registry
     */
    [[nodiscard]]
    Registry& getRegistry() noexcept {
        return *registry;
    }

    /**
     * @brief Convert game state to string representation
     *
     * @return String representation of game state
     */
    [[nodiscard]]
    String toString() const {
        String result = stdx::fmt::format(
            "Chapter: {} | Current Player: {} | Phase: {} | Battle: {}",
            chapterNumber,
            currentPlayerIndex,
            phaseName(currentPhase),
            battleInProgress ? "Yes" : "No"
        );

        if (!statusMessage.empty()) {
            result = stdx::fmt::format("{} | {}", result, statusMessage);
        }

        return result;
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::game::Game;

template <>
struct Formatter<Game::Phase> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(Game::Phase phase, FormatContext& ctx) {
        return stdx::fmt::format_to(ctx.out(), "{}", Game::phaseName(phase));
    }
};

SPECIALISE_FORMATTER(Game::Phase);
