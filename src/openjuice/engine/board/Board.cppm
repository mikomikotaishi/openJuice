/**
 * @file Board.cppm
 * @module openjuice.engine.boardLBoard
 * @brief Implementation of the Board class.
 *
 * This file contains the implementation of the Board class, which represents the game board and its state.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board:Board;

import stdx;

import :FieldEvent;
import :Panel;

import openjuice.engine.util;

using stdx::collections::Queue;
using stdx::collections::HashMap;
using stdx::collections::Vector;
using stdx::fs::Path;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::ranges::IotaView;

using openjuice::engine::board::Panel;
using openjuice::engine::util::Constants;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class Board
 * @brief Class representing the game board.
 *
 * The Board class represents the game board and its state, including the panels and their connections.
 */
export class [[nodiscard]] Board {
public:
    static constexpr u8 MAX_PLAYERS = Constants::GAME_MAX_PLAYERS; ///< Maximum number of players.
    static constexpr usize GAME_MAX_WIDTH = Constants::GAME_MAX_WIDTH; ///< Maximum game width.
    static constexpr usize GAME_MAX_HEIGHT = Constants::GAME_MAX_HEIGHT; ///< Maximum game height.

    using GameBoard = Array<Array<UniquePointer<Panel>, GAME_MAX_WIDTH>, GAME_MAX_HEIGHT>;

    /**
     * @class Info
     * @brief Struct aggregating key information about boards.
     * 
     * The Info record aggregates key information about boards, such as ID, name, dimensions, and home panels.
     */
    class [[nodiscard]] Info final {
    public:
        static constexpr u8 MAX_PLAYERS = Constants::GAME_MAX_PLAYERS; ///< Maximum number of players.
        static constexpr u8 MAX_FIELD_EVENTS = 3; ///< Maximum number of field events per board.
        using HomePanels = Array<Pair<u8, u8>, MAX_PLAYERS>;
        using FieldEvents = Array<FieldEvent::Data, MAX_FIELD_EVENTS>;
    private:
        const Path path; ///< The path to the board file.
        const String name; ///< The name of the board.
        const HomePanels homePanels; ///< The home panels for each player.
        const FieldEvents fieldEvents; ///< The field events for the board.
        const u32 id; ///< The ID of the board. 0 denotes an error.
        const u8 bossId; ///< The ID of the boss associated with the board.
        const u8 width; ///< The width of the board.
        const u8 height; ///< The height of the board.
    public:
        /**
         * @brief Get the path to the board file
         * @return The board file path
         */
        [[nodiscard]]
        constexpr Path getPath() const noexcept {
            return path;
        }
    
        /**
         * @brief Get the name of the board
         * @return The board's name
         */
        [[nodiscard]]
        constexpr String getName() const noexcept {
            return name;
        }

        /**
         * @brief Get the home panels of the board
         * @return The home panels of the board (array of 4 coordinates)
         */
        [[nodiscard]]
        constexpr HomePanels getHomePanels() const noexcept {
            return homePanels;
        }

        /**
         * @brief Get the field events of the board
         * @return The field events of the board (array of 3 FieldEvent::Data)
         */
        [[nodiscard]]
        constexpr FieldEvents getFieldEvents() const noexcept {
            return fieldEvents;
        }

        /**
         * @brief Get the ID of the board
         * @return The board's ID
         */
        [[nodiscard]]
        constexpr u32 getId() const noexcept {
            return id;
        }

        /**
         * @brief Get the ID of the boss associated with the board
         * @return The boss's ID
         */
        [[nodiscard]]
        constexpr u8 getBossId() const noexcept {
            return bossId;
        }

        /**
         * @brief Get the width of the board
         * @return The board's width
         */
        [[nodiscard]]
        constexpr u8 getWidth() const noexcept {
            return width;
        }

        /**
         * @brief Get the height of the board
         * @return The board's height
         */
        [[nodiscard]]
        constexpr u8 getHeight() const noexcept {
            return height;
        }

        /**
         * @brief Constructor with parameters
         * @param id The board ID
         * @param name The board name
         * @param path The path to the board file
         * @param width The board width
         * @param height The board height
         * @param bossId The ID of the boss associated with the board
         * @param panels The home panels for each player
         * @param events The field events for the board
         */
        constexpr Info(u32 id, StringView name, Path path, u8 width, u8 height, u8 bossId, const HomePanels& panels, const FieldEvents& events):
            path{path}, name{String(name)}, homePanels{panels}, fieldEvents{events}, id{id},
            bossId{bossId}, width{width}, height{height} {}

        /**
         * @brief Destructor
         */
        constexpr ~Info() = default;
    };
private:
    static constexpr Array<Pair<i8, i8>, 4> DIRECTION_OFFSETS = {{
        {-1,  0}, ///< Top
        { 0, -1}, ///< Left
        { 0,  1}, ///< Right
        { 1,  0}, ///< Bottom
    }}; ///< This array defines the offsets for the four cardinal directions (top, left, right, bottom).

    /**
     * @class Graph
     * @brief Internal graph representation for pathfinding and distance calculations.
     *
     * The Graph class is used to handle internal calculations such as finding paths and distances between panels.
     * This is an implementation detail of Board and should not be exposed publicly.
     */
    class [[nodiscard]] Graph {
    private:
        HashMap<SharedPointer<Panel>, Vector<SharedPointer<Panel>>> adjList; ///< Adjacency list for the graph.
        HashMap<SharedPointer<Panel>, Vector<SharedPointer<Panel>>> reverseAdjList; ///< Reverse adjacency list for the graph.

        /**
         * @brief Adds an edge to the Graph.
         * @param from The Panel from which the edge originates.
         * @param to The Panel to which the edge leads.
         */
        void addEdge(const SharedPointer<Panel>& from, const SharedPointer<Panel>& to) {
            #ifndef NDEBUG
            adjList.at(from).push_back(to);
            reverseAdjList.at(to).push_back(from);
            #else
            adjList[from].push_back(to);
            reverseAdjList[to].push_back(from);
            #endif
        }
    public:
        /**
         * @brief Construct a new Graph object.
         * @param gameboard The GameBoard to initialize the Graph with.
         */
        explicit Graph(const GameBoard& gameboard) {
            for (const Array<UniquePointer<Panel>, GAME_MAX_WIDTH>& row: gameboard) {
                for (const UniquePointer<Panel>& panel: row) {
                    if (panel) {
                        for (usize i: IotaView(0uz, DIRECTION_OFFSETS.size())) {
                            SharedPointer<Panel> neighbor = panel->getNeighbor(static_cast<Panel::Direction>(i));
                            if (neighbor) {
                                addEdge(SharedPointer<Panel>(panel.get()), neighbor);
                            }
                        }
                    }
                }
            }
        }

        /**
         * @brief Destroy the Graph object
         */
        ~Graph() = default;

        /**
         * @brief Finds all panels a distance of n panels away.
         * @param start The starting panel.
         * @param n The number of panels to search away from start.
         * @return Vector<SharedPointer<Panel>> The panels at the specified distance.
         */
        [[nodiscard]]
        Vector<SharedPointer<Panel>> atDistance(const SharedPointer<Panel>& start, i8 n) const {
            Vector<SharedPointer<Panel>> result;
            Queue<Pair<SharedPointer<Panel>, i8>> q;
            HashMap<SharedPointer<Panel>, bool> visited;

            q.emplace(start, 0);

            #ifndef NDEBUG
            visited.at(start) = true;
            #else
            visited[start] = true;
            #endif

            while (!q.empty()) {
                auto [current, distance] = q.front();
                q.pop();

                if (distance == n) {
                    result.push_back(current);
                }

                const Vector<SharedPointer<Panel>> neighbors = n > 0
                    ? adjList.at(current)
                    : reverseAdjList.at(current);

                for (const SharedPointer<Panel>& neighbor: neighbors) {
                    #ifndef NDEBUG
                    if (!visited.at(neighbor)) {
                        visited.at(neighbor) = true;
                    }
                    #else
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                    }
                    #endif

                    q.emplace(neighbor, distance + (n > 0 ? 1 : -1));
                }
            }
            return result;
        }
    };

    GameBoard gameBoard; ///< The game board represented as a 2D array of panels.
    Info::HomePanels homePanels; ///< The home panels for each player.
    UniquePointer<Graph> graph; ///< Internal graph representation for pathfinding.
    u8 width; ///< The width of the board.
    u8 height; ///< The height of the board.
public:
    /**
     * @brief Construct a new Board object.
     * @param id The ID of the Board to construct.
     */
    explicit Board(SharedPointer<Info> data):
        homePanels{data->getHomePanels()},
        width{data->getWidth()}, height{data->getHeight()} {
        // need to initialize gameBoard...

        // Initialize the graph after the game board is set up
        graph = Pointers::unique<Graph>(gameBoard);
    }

    /**
     * @brief Destroy the Board object
     */
    ~Board() = default;

    /**
     * @brief Find all panels at a specific distance from a starting panel.
     * @param start The starting panel.
     * @param distance The distance to search (positive for forward, negative for backward).
     * @return A list of panels at the specified distance, or nullopt if there is no instance of graph.
     */
    [[nodiscard]]
    Optional<Vector<SharedPointer<Panel>>> getPanelsAtDistance(const SharedPointer<Panel>& start, i8 distance) const {
        if (!graph) {
            return nullopt;
        }
        return graph->atDistance(start, distance);
    }
};

END_MODULE_NAMESPACE();
