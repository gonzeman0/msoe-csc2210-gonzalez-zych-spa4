//
// Created by gonzalezem on 3/24/2025.
//

#ifndef CELL_H
#define CELL_H

#include "item.h"


/// - ROOM: A cell that can contain items and the player.
/// - EXIT: A cell that represents the exit point of the game; its behavior is defined in the game logic.
/// - PIT: A hazard; its behavior is defined in the game logic.
/// - BAT: A hazard; its behavior is defined in the game logic.
/// - GAS: A hazard; its behavior is defined in the game logic.
enum CellType {
    ROOM,
    EXIT,
    PIT,
    BAT,
    GAS
};

/// Represents a single cell in the game, which maintains its type, 
/// connections to adjacent cells, any item it contains, 
/// and whether it has the player or the Wumpus.
class Cell {
    CellType type;
    Cell* north_cell = nullptr;  // Adjacent cell to the north, nullptr indicates no adjacent cell.
    Cell* east_cell = nullptr;   // Adjacent cell to the east, nullptr indicates no adjacent cell.
    Cell* south_cell = nullptr;  // Adjacent cell to the south, nullptr indicates no adjacent cell.
    Cell* west_cell = nullptr;   // Adjacent cell to the west, nullptr indicates no adjacent cell.
    Item* item = nullptr;        // Pointer to the item in the cell, nullptr indicates no item.
    bool has_player;
    bool has_wumpus;

    // Grant Map access to this class's private members.
    friend class Map;

    public:
        CellType getType() const { return type; }
        Cell* getNorthCell() const { return north_cell; }
        Cell* getEastCell() const { return east_cell; }
        Cell* getSouthCell() const { return south_cell; }
        Cell* getWestCell() const { return west_cell; }
        Item* getItem() const { return item; }
        bool hasPlayer() const { return has_player; }
        bool hasWumpus() const { return has_wumpus; }

        Item* pickupItem() { Item* ret = item; item = nullptr; return ret; }
        void setHasPlayer(const bool has_p) { this->has_player = has_p; }
        void setHasWumpus(const bool has_w) { this->has_wumpus = has_w; }


};



#endif //CELL_H
