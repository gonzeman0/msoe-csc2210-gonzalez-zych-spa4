//
// Created by gonzalezem on 3/25/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.h"
#include <map>
#include <string>


class Player {
    Cell* current_cell;                     // Pointer to the cell the player is currently in
    std::map<std::string, int> inventory;   // Map of the item name to item count

    public:
        /**
         * Constructs a Player object with the specified starting cell.
         *
         * This constructor initializes the Player at a designated starting cell,
         * provided the cell meets specific criteria. The starting cell must have
         * been assigned to the player using the Map::spawnPlayer() method, and it
         * must be of type ROOM. If either of these conditions is not met, an error
         * is logged, and the player is not initialized at that cell.
         *
         * @param starting_cell A pointer to the Cell object where the player starts.
         *                      The cell must already have the player assigned using
         *                      Map::spawnPlayer(), and it must be of type ROOM.
         */
        Player(Cell& startingCell);

        /**
        * Moves the player to an adjacent cell based on the given direction.
        *
        * This method updates the player's current cell to an adjacent cell
        * in the specified direction. It's the responsibility of the caller to
        * verify that the given direction is valid and the cell is traversable.
        *
        * @param direction The direction to move the player in. Valid directions are:
        *                  'N' for North, 'E' for East, 'S' for South, and 'W' for West.
        *                  Any other input is considered invalid and logs an error.
        */
        void move(char direction);

        /**
         * Adds an item to the player's inventory or increases its count if it already exists.
         *
         * @param item Pointer to the item to be added to the inventory. If the pointer is null, the method does nothing.
         */
        void pickup(Item* item);

        // Returns a reference to the player's inventory.
        std::map<std::string, int>& getInventory() { return inventory; };

        // Returns a pointer to the players current cell.
        Cell* getCurrentCell() const { return current_cell; }

};



#endif //PLAYER_H
