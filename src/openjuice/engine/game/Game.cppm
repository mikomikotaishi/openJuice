/**
 * @file Game.cppm
 * @module openjuice.engine.game:Game
 * @brief Module file for game operations.
 *
 * This file contains the implementation of the game operations, including state management
 * and thread-safe access to game components.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game:Game;

import stdx;

import openjuice.card;
import openjuice.chat;
import openjuice.engine.board;
import openjuice.engine.entity;
import openjuice.engine.settings;
import openjuice.engine.unit;
import openjuice.unit;

using stdx::collections::Vector;
using stdx::fmt::Formatter;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::ranges::IotaView;
using stdx::time::Milliseconds;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::board::Board;
using openjuice::engine::entity::Combatant;
using openjuice::engine::entity::Mob;
using openjuice::engine::entity::Player;
using openjuice::engine::settings::SettingsService;
using openjuice::engine::unit::Playable;
using openjuice::unit::CharacterFactory;

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
    static constexpr u8 MAX_PLAYERS = Board::Info::MAX_PLAYERS; ///< Maximum number of players.

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
    SharedPointer<Logger> logger; ///< The logger instance.

    // Game state (ordered by size for optimal padding)
    Array<SharedPointer<Player>, MAX_PLAYERS> players; ///< Player array
    String statusMessage; ///< Status message
    Vector<SharedPointer<Mob>> mobs; ///< The mobs currently on the board
    SharedPointer<Board> gameBoard; ///< The game board (null until a board is loaded for a match)
    Milliseconds deltaTime; ///< Delta time
    SharedPointer<Combatant> activeBattleAttacker; ///< Battle attacker
    SharedPointer<Combatant> activeBattleDefender; ///< Battle defender
    Phase currentPhase = Phase::SETUP; ///< Current phase
    u8 currentPlayerIndex = 0; ///< Current player index
    u8 chapterNumber = 1; ///< Chapter number
    bool battleInProgress = false; ///< Battle in progress flag
    // TODO: Add a spectator list

    /**
     * @brief Puts every player slot back to a freshly created player with no character assigned.
     */
    void resetPlayers() {
        for (u8 i: IotaView(u8{0}, MAX_PLAYERS)) {
            #ifndef NDEBUG
            players.at(i) = Pointers::shared<Player>();
            #else
            players[i] = Pointers::shared<Player>();
            #endif
        }
    }

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
     * @param loggerFactory The injected logger factory.
     * @param settings The injected settings service, used to determine the frame delta-time.
     */
    Game(SharedPointer<LoggerFactory> loggerFactory, SharedPointer<SettingsService> settings):
        logger{loggerFactory->of("Game")},
        deltaTime{settings->getDeltaTime()} {
        resetPlayers();

        #ifndef NDEBUG
        logger->debug("Created Game!");
        #endif
    }

    /**
     * @brief Destructor for the Game class.
     */
    ~Game() {
        #ifndef NDEBUG
        logger->debug("Destroying Game...");
        #endif

        #ifndef NDEBUG
        logger->debug("Game shutdown complete!");
        #endif
    }

    /**
     * @brief Initialize the game state and prepare for running
     *
     * Discards any state left over from a previous match, so this doubles as the reset for starting a new game.
     */
    void init() {
        #ifndef NDEBUG
        logger->debug("Initializing Game...");
        #endif

        resetPlayers();
        mobs.clear();
        endBattle();
        currentPhase = Phase::SETUP;
        currentPlayerIndex = 0;
        chapterNumber = 1;

        #ifndef NDEBUG
        logger->debug("Game initialized!");
        #endif
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
     * @param num The player number.
     * @param id The character ID.
     * @throws OutOfRangeException if playerNumber is out of range.
     */
    THROWS(OutOfRangeException)
    void setPlayerCharacter(u8 num, u8 id) {
        #ifndef NDEBUG
        logger->debug("Setting player {} to character of ID {}...", num, id);
        #endif

        if (num >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid player number");
        }

        SharedPointer<Playable> character;
        if (Optional<SharedPointer<Playable>> ch = CharacterFactory::create(id); ch.has_value()) {
            character = *ch;
        } else {
            throw OutOfRangeException(Ops::fmt("Error: {} is not a valid character ID!", id));
        }

        #ifndef NDEBUG
        players.at(num)->setUnit(character);
        #else
        players[num]->setUnit(character);
        #endif
    }

    /**
     * @brief Runs the game.
     */
    void run() {
        logger->info("Beginning game...");

        currentPhase = Phase::PLAYER_TURN;
    }

    /**
     * @brief Get current player.
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
     * @param index Player index
     * @return Player object at index
     * @throws OutOfRangeException if index is out of range
     */
    [[nodiscard]]
    THROWS(OutOfRangeException)
    SharedPointer<Player> getPlayer(u8 index) const {
        if (index >= MAX_PLAYERS) {
            throw OutOfRangeException("Invalid index");
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
     * @param attacker The attacking entity
     * @param defender The defending entity
     * @return True if battle started successfully
     */
    bool startBattle(const SharedPointer<Combatant>& attacker, const SharedPointer<Combatant>& defender) {
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
        activeBattleAttacker = nullptr;
        activeBattleDefender = nullptr;
        currentPhase = Phase::PLAYER_TURN;
    }

    /**
     * @brief Check if battle is in progress
     * @return True if battle is ongoing
     */
    [[nodiscard]]
    bool isBattleInProgress() const noexcept {
        return battleInProgress;
    }

    /**
     * @brief Get current battle attacker
     * @return The attacking entity, or null when no battle is in progress
     */
    [[nodiscard]]
    SharedPointer<Combatant> getBattleAttacker() const noexcept {
        return activeBattleAttacker;
    }

    /**
     * @brief Get current battle defender
     * @return The defending entity, or null when no battle is in progress
     */
    [[nodiscard]]
    SharedPointer<Combatant> getBattleDefender() const noexcept {
        return activeBattleDefender;
    }

    /**
     * @brief Set status message
     * @param message New status message
     */
    void setStatusMessage(const String& message) noexcept {
        statusMessage = message;
    }

    /**
     * @brief Get status message
     * @return Current status message
     */
    [[nodiscard]]
    String getStatusMessage() const noexcept {
        return statusMessage;
    }

    /**
     * @brief Get game board
     * @return Reference to game board
     */
    [[nodiscard]]
    SharedPointer<Board> getBoard() const noexcept {
        return gameBoard;
    }

    /**
     * @brief Add a mob to the game
     * @param mob The mob to add
     */
    void addMob(const SharedPointer<Mob>& mob) {
        mobs.push_back(mob);
    }

    /**
     * @brief Get all mobs
     * @return The mobs currently on the board
     */
    [[nodiscard]]
    const Vector<SharedPointer<Mob>>& getMobs() const noexcept {
        return mobs;
    }

    /**
     * @brief Convert game state to string representation
     * @return String representation of game state
     */
    [[nodiscard]]
    String toString() const {
        String result = Ops::fmt(
            "Chapter: {} | Current Player: {} | Phase: {} | Battle: {}",
            chapterNumber,
            currentPlayerIndex,
            phaseName(currentPhase),
            battleInProgress ? "Yes" : "No"
        );

        if (!statusMessage.empty()) {
            result = Ops::fmt("{} | {}", result, statusMessage);
        }

        return result;
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::game::Game;

namespace stdx::fmt {
    template <>
    struct Formatter<Game::Phase> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(Game::Phase phase, FormatContext& ctx) {
            return format_to(ctx.out(), "{}", Game::phaseName(phase));
        }
    };
}

SPECIALIZE_FORMATTER(Game::Phase);
