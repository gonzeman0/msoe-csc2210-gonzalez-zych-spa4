//
// Created by gonzalezem on 3/24/2025.
//

#ifndef MAP_H
#define MAP_H

#include "Bow.h"
#include "Arrow.h"
#include "Bomb.h"
#include "Rope.h"
#include "cell.h"
#include <cstddef>

// Fixed map size
constexpr size_t ROWS = 6;
constexpr size_t COLS = 10;

// Constants representing the number of hazards in the map:
// - PIT_COUNT: Number of deadly pits (player dies on stepping here).
// - GAS_COUNT: Number of gas hazards (potentially deadly if the player ignites it).
// - BAT_COUNT: Number of non-lethal but unpredictable bats
//   (they can drop the player in any random location, including into other hazards).
constexpr unsigned int PIT_COUNT = 6;
constexpr unsigned int GAS_COUNT = 10;
constexpr unsigned int BAT_COUNT = 8;

// Constants representing the number of items in the map
constexpr unsigned int BOW_COUNT = 1;
constexpr unsigned int ARROW_COUNT = 3;
constexpr unsigned int BOMB_COUNT = 2;
constexpr unsigned int ROPE_COUNT = 1;


/**
 * Represents a 2D map grid composed of cells, which can contain a variety of types such as
 * rooms, hazards, items, and other objects. The Map class supports functionality for the
 * generation, validation, and interaction with the map's cells.
 */
// This map is comprised of `Cell` objects.
//
class Map {
    // Statically allocate default cells
    Cell grid[ROWS][COLS];
    // Statically allocate helper grid
    char flood_grid[ROWS][COLS]{}; // Utilized by findTraversable();

    // Statically allocate Cell pointers. Used for memory management of new Cells.
    Cell* cells[PIT_COUNT + GAS_COUNT + BAT_COUNT]{nullptr};
    // Statically allocate Item pointers. Used for memory management of new Items
    Item* items[BOW_COUNT + ARROW_COUNT + BOMB_COUNT + ROPE_COUNT]{nullptr};

    // Used for the instantiation of dynamic objects.
    void instantiateItems(unsigned int bow_count, unsigned int arrow_count, unsigned int bomb_count, unsigned int rope_count);

    // Map generation methods. Documentation available in Map.cpp
    void initializeGrid(); // Sets defaults cells and connects intra-cell pointers.
    void addRandomHazards(unsigned int pit_count, unsigned int bat_count, unsigned int gas_count);
    void placeItemsRandomly();
    void placeExit();

    // Map validation methods. Documentation available in Map.cpp
    bool isTraversable();
    void findTraversable(size_t row, size_t col, unsigned int& numFound);


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
         * Destructor destroys dynamically instantiated objects.
         * Specifically, non-default cells (hazards) and items.
         */
        ~Map();

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
        * - '+' represents the player
        * - '#' represents the Wumpus
        * - '.' represents an empty ROOM.
        * - '@' represents a PIT hazard.
        * - '!' represents a BAT hazard.
        * - 'G' represents a GAS hazard.
        * - 'E' represents the EXIT.
        * - '_' represents an unknown or unhandled cell state.
        *
        * This function is primarily used for debugging purposes
        * to visualize the grid and the distribution of cell types.
        */
        void printGrid() const;
};



#endif //MAP_H
