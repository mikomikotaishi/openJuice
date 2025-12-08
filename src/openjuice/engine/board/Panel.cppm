/**
 * @file Panel.cppm
 * @module openjuice.engine.board.Panel
 * @brief Implementation of the Panel class.
 *
 * This file contains the implementation of the Panel class, which represents a panel on the game board.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board.Panel;

export import :PanelType;

import std;

import openjuice.engine.util.Direction;

using std::collections::BitSet;
using std::mem::SharedPointer;
using std::mem::WeakPointer;

using openjuice::engine::util::Direction;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class Panel
 * @brief Class representing a panel on the game board.
 *
 * The Panel class represents a panel on the game board with attributes such as type, neighbours, and entry/exit directions.
 */
export class Panel {
public:
    using Neighbours = Array<WeakPointer<Panel>, 4>;
private:
    Neighbours neighbours; ///< The neighbouring panels.
    BitSet<4> enters; ///< The directions from which the panel can be entered.
    BitSet<4> exits; ///< The directions from which the panel can be exited.
    u16 id; ///< The ID of the panel.
    PanelType type; ///< The type of the panel.
    PanelType alternativeType = PanelType::NEUTRAL; ///< The alternative type of the panel.
public:
    /**
     * @brief Constructor to initialise a Panel object.
     *
     * @param id The ID of the panel.
     * @param type The type of the panel.
     * @param enters The directions from which the panel can be entered.
     * @param exits The directions from which the panel can be exited.
     * @param alternativeType The alternative type of the panel (if any).
     */
    Panel(u16 id, PanelType type, PanelType alternativeType, const BitSet<4>& enters, const BitSet<4>& exits):
        neighbours{}, enters{enters}, exits{exits}, id{id}, type{type}, alternativeType{alternativeType} {}

    GETTER(u16, Id, id);
    PROPERTY(PanelType, Type, type);
    PROPERTY(PanelType, AlternativeType, alternativeType);
    GETTER(BitSet<4>, Enters, enters);
    GETTER(BitSet<4>, Exits, exits);
    GETTER(Neighbours, Neighbours, neighbours);

    /**
     * @brief Set the neighbour of the panel in a specific direction.
     *
     * @param direction The direction of the neighbour.
     * @param neighbour The neighbouring panel.
     */
    void setNeighbour(Direction direction, const SharedPointer<Panel>& neighbour) RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        neighbours.at(static_cast<usize>(direction)) = neighbour;
        #else
        neighbours[static_cast<usize>(direction)] = neighbour;
        #endif
    }

    /**
     * @brief Get the neighbour of the panel in a specific direction.
     *
     * @param direction The direction of the neighbour.
     * @return The neighbouring panel.
     */
    [[nodiscard]]
    SharedPointer<Panel> getNeighbour(Direction direction) const RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        return neighbours.at(static_cast<usize>(direction)).lock();
        #else
        return neighbours[static_cast<usize>(direction)].lock();
        #endif
    }
};

END_MODULE_NAMESPACE();
