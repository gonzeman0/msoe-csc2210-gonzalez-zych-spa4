//
// Created by gonzalezem on 3/24/2025.
//

#ifndef CELL_H
#define CELL_H

#include "Item.h"
#include <iostream>
#include <string>

const std::string helpText =
    "========================================\n"
    "HELP GUIDE\n"
    "========================================\n"
    "Goal:\n"
    "Escape the dark cave. Survive.\n"
    "\n"
    "----------------------------------------\n"
    "Hazards:\n"
    "- Wumpus         = Huge, foul, and hungry.\n"
    "- Endless Pit    = Deep... bottomless.\n"
    "- Giant Bat      = Blind, unpredictable\n"
    "- Flammable Gas  = Smells funny. Harmless... right?\n"
    "\n"
    "----------------------------------------\n"
    "Items:\n"
    "- Bow        = Can shoot arrows.\n"
    "- Arrow      = Use with bow.\n"
    "- Dynamite   = Explosive. Very loud.\n"
    "- Rope       = Useful for tying or climbing.\n"
    "\n"
    "Use or throw items wisely to stay alive and uncover secrets.\n"
    "========================================\n";



const std::string mapKey =
    "==================== MAP KEY ====================\n"
    "| #  = Wumpus          | )  = Bow               |\n"
    "| !  = Giant Bat       | >  = Arrow             |\n"
    "| G  = Flammable Gas   | ?  = Rope              |\n"
    "| @  = Endless Pit     | D  = Dynamite          |\n"
    "=================================================\n";



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
    GAS,
    OPEN_EXIT
};

class Item;

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

        std::string getProximityMessage();
        std::string getCurrentCellMessage();
        std::string getDeathMessage();
        std::string getBasicThrowMessage(std::string message);

        Item* pickupItem();
        void setItem(Item* item) { this->item = item; }
        void setHasPlayer(bool has_p);
        void setHasWumpus(bool has_w);
        void setType(CellType type) { this->type = type; };
};

#endif //CELL_H
