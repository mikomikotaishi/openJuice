/**
 * @file Board.cppm
 * @module openjuice.engine.board.Board
 * @brief Implementation of the Board class.
 *
 * This file contains the implementation of the Board class, which represents the game board and its state.
 */

module;

// Standard library headers are necessary here - there is no workaround
#include <cassert>
#include <memory>

#include "Macros.hpp"

export module openjuice.engine.board.Board;

import std;

import openjuice.engine.board.BoardInfo;
import openjuice.engine.board.BoardLibrary;
import openjuice.engine.board.Panel;
import openjuice.engine.util.Constants;
import openjuice.engine.util.Direction;

using std::collections::Queue;
using std::collections::HashMap;
using std::collections::Vector;
using std::mem::SharedPointer;
using std::mem::UniquePointer;
using std::ranges::IotaView;

namespace io = std::io;
namespace mem = std::mem;

using openjuice::engine::board::BoardInfo;
using openjuice::engine::board::Panel;
using openjuice::engine::util::Constants;
using openjuice::engine::util::Direction;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class Board
 * @brief Class representing the game board.
 *
 * The Board class represents the game board and its state, including the panels and their connections.
 */
export class Board {
public:
    static constexpr u8 MAX_PLAYERS = Constants::GAME_MAX_PLAYERS; ///< Maximum number of players.
    static constexpr usize GAME_MAX_WIDTH = Constants::GAME_MAX_WIDTH; ///< Maximum game width.
    static constexpr usize GAME_MAX_HEIGHT = Constants::GAME_MAX_HEIGHT; ///< Maximum game height.

    using GameBoard = Array<Array<UniquePointer<Panel>, GAME_MAX_WIDTH>, GAME_MAX_HEIGHT>;

    /**
     * @brief Direction offsets
     *
     * This array defines the offsets for the four cardinal directions (top, left, right, bottom).
     */
    static constexpr Array<Pair<i8, i8>, 4> DIRECTION_OFFSETS = {{
        {-1,  0}, // Top
        { 0, -1}, // Left
        { 0,  1}, // Right
        { 1,  0}  // Bottom
    }};
private:
    /**
     * @class Graph
     * @brief Internal graph representation for pathfinding and distance calculations.
     *
     * The Graph class is used to handle internal calculations such as finding paths and distances between panels.
     * This is an implementation detail of Board and should not be exposed publicly.
     */
    class Graph {
    private:
        HashMap<SharedPointer<Panel>, Vector<SharedPointer<Panel>>> adjList; ///< Adjacency list for the graph.
        HashMap<SharedPointer<Panel>, Vector<SharedPointer<Panel>>> reverseAdjList; ///< Reverse adjacency list for the graph.

        /**
         * @brief Adds an edge to the Graph.
         *
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
         *
         * @param gameboard The GameBoard to initialise the Graph with.
         */
        explicit Graph(const GameBoard& gameboard) {
            for (const Array<UniquePointer<Panel>, GAME_MAX_WIDTH>& row: gameboard) {
                for (const UniquePointer<Panel>& panel: row) {
                    if (panel) {
                        for (usize i: IotaView(0uz, DIRECTION_OFFSETS.size())) {
                            SharedPointer<Panel> neighbour = panel->getNeighbour(static_cast<Direction>(i));
                            if (neighbour) {
                                addEdge(SharedPointer<Panel>(panel.get()), neighbour);
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
         *
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

                const Vector<SharedPointer<Panel>> neighbours = n > 0
                    ? adjList.at(current)
                    : reverseAdjList.at(current);

                for (const SharedPointer<Panel>& neighbour: neighbours) {
                    #ifndef NDEBUG
                    if (!visited.at(neighbour)) {
                        visited.at(neighbour) = true;
                    }
                    #else
                    if (!visited[neighbour]) {
                        visited[neighbour] = true;
                    }
                    #endif

                    q.emplace(neighbour, distance + (n > 0 ? 1 : -1));
                }
            }
            return result;
        }
    };

    GameBoard gameBoard; ///< The game board represented as a 2D array of panels.
    BoardInfo::HomePanels homePanels; ///< The home panels for each player.
    UniquePointer<Graph> graph; ///< Internal graph representation for pathfinding.
    u8 boardWidth; ///< The width of the board.
    u8 boardHeight; ///< The height of the board.
public:
    /**
     * @brief Construct a new Board object.
     *
     * @param id The ID of the Board to construct.
     */
    explicit Board(u32 id) {
        SharedPointer<BoardInfo> boardData = BoardLibrary::getInstance()[id];

        if (boardData) {
            // need to initialise gameBoard...
            boardWidth = boardData->getWidth();
            boardHeight = boardData->getHeight();
            homePanels = boardData->getHomePanels();

            // Initialise the graph after the game board is set up
            graph = mem::make_unique<Graph>(gameBoard);
        } else {
            // Initialises to 0 at application startup - trivial case
            boardWidth = 0;
            boardHeight = 0;
        }
    }

    /**
     * @brief Destroy the Board object
     */
    ~Board() = default;

    /**
     * @brief Find all panels at a specific distance from a starting panel.
     *
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

    /**
     * @brief Print the board to the terminal.
     */
    void printBoardAscii() const {
        io::println("█");
    }
};

END_MODULE_NAMESPACE();
