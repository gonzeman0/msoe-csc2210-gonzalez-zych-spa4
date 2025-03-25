//
// Created by gonzalezem on 3/24/2025.
//

#ifndef MAP_H
#define MAP_H

#include "cell.h"
#include <cstddef>

// Fixed map size
constexpr size_t ROWS = 8;
constexpr size_t COLS = 8;


//
// The `Map` class represents a fixed-size grid-based map used in the game.
// This map is comprised of `Cell` objects.
//
class Map {
    Cell grid[ROWS][COLS];
    char flood_grid[ROWS][COLS]; // Utilized by findTraversible();

    // Map generation methods. Documentation available in Map.cpp
    void initializeGrid();
    void addRandomHazards(unsigned int pit_count, unsigned int bat_count, unsigned int gas_count);
    bool isTraversable();
    void findTraversable(size_t row, size_t col, unsigned int& numFound);
    void placeExit();

public:
        // The number of rows composing the map
        const size_t row_count = ROWS;

        // The number of columns composing the map
        const size_t col_count = COLS;

        /**
        * This constructor generates a traversable map of cells with a mixture of:
        * - Empty rooms (ROOM).
        * - Hazardous cells (PIT, BAT, GAS).
        *
        * The grid will ensure that there are paths available to traverse the map
        * from various points. Hazards are randomly distributed across the grid, but
        * the logic ensures some level of traverseability.
        */
        Map();

        /**
        * This method places a Wumpus on a randomly selected cell within the grid.
        * The Wumpus can spawn on any type of cell, including hazardous cells
        * (e.g., PIT, BAT, GAS), unless already occupied by the Player.
        *
        * @return The `Cell` object the Wumpus has been placed.
        */
        Cell& spawnWumpus();

        /**
        * This method places the Player on a randomly selected cell within the grid.
        * The player can spawn on any non-hazardous cell, unless already occupied
        * by a Wumpus or is the exit.
        *
        * @return The `Cell` where the Player has been placed.
        */
        Cell& spawnPlayer();

        /**
         * This method returns a pointer to the 'Cell' object at the specified location.
         *
         * @return Cell* A pointer to the specified 'Cell' object, or nullptr if out of bounds.
         */
        Cell* getCell(size_t row, size_t col);

        /**
        * This function displays the grid with column and row headers
        * for easier visualization. It uses different symbols to represent
        * various cell types:
        *
        * - '.' represents an empty ROOM.
        * - 'P' represents a PIT hazard.
        * - 'B' represents a BAT hazard.
        * - 'G' represents a GAS hazard.
        * - 'E' represents the EXIT.
        * - '?' represents an unknown or unhandled cell state.
        *
        * This function is primarily used for debugging purposes
        * to visualize the grid and the distribution of cell types.
        */
        void printGrid() const;
};



#endif //MAP_H
