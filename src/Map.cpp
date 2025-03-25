//
// Created by gonzalezem on 3/24/2025.
//

#include "Map.h"
#include <cstdlib>
#include <iostream>


// Constants representing the number of hazards in the map:
// - PIT_COUNT: Number of deadly pits (player dies on stepping here).
// - GAS_COUNT: Number of gas hazards (potentially deadly if the player ignites it).
// - BAT_COUNT: Number of non-lethal but unpredictable bats
//   (they can drop the player in any random location, including into other hazards).
constexpr unsigned int PIT_COUNT = 6;
constexpr unsigned int GAS_COUNT = 10;
constexpr unsigned int BAT_COUNT = 8;

// Constructor initializes the grid
Map::Map() {
    initializeGrid();
    addRandomHazards(PIT_COUNT, BAT_COUNT, GAS_COUNT);
    placeExit();
}


// Initialize the grid with default values for each cell.
// This includes setting the type to ROOM, setting player and Wumpus presence to false,
// and establishing pointers to adjacent cells if available.
void Map::initializeGrid() {
    for (size_t row = 0; row < row_count; row++) {
        for (size_t col = 0; col < col_count; col++) {
            grid[row][col].type = ROOM; // Initialize as ROOM by default
            grid[row][col].has_player = false;
            grid[row][col].has_wumpus = false;

            // Set adjacent cells if within bounds
            if (row > 0) grid[row][col].north_cell = &grid[row - 1][col];
            if (row < row_count - 1) grid[row][col].south_cell = &grid[row + 1][col];
            if (col > 0) grid[row][col].west_cell = &grid[row][col - 1];
            if (col < col_count - 1) grid[row][col].east_cell = &grid[row][col + 1];
        }
    }
}


// This function places hazards randomly on the grid.
// The types of hazards are:
// - PIT: Deadly, falling here ends the game.
// - GAS: Potentially explodes if triggered by the player.
// - BAT: Non-lethal, can displace the player to a random location, which might be hazardous.
//
// Parameters:
// - pit_count: Number of PIT hazards to place.
// - bat_count: Number of BAT hazards to place.
// - gas_count: Number of GAS hazards to place.
//
// Ensures that the total number of hazards does not exceed the available grid cells.
// Re-checks cells to avoid overwriting hazards already placed.
void Map::addRandomHazards(unsigned int pit_count, unsigned int bat_count, unsigned int gas_count) {
    if ((pit_count + bat_count + gas_count) > (row_count * col_count)) {
        std::cerr << "ERROR in Map.addRandomHazards(): Not enough cells to place all hazards!";
    }
    
    // Keep placing hazards until the required count is reached
    while (pit_count > 0 || bat_count > 0 || gas_count > 0) {
        // Generate random location
        const size_t row = std::rand() % row_count;
        const size_t col = std::rand() % col_count;

        // Check if the cell is already occupied by a hazard
        if (grid[row][col].type != ROOM)
            continue;

        // Place the hazards based on the required counts
        if (pit_count > 0) {
            grid[row][col].type = PIT;
            pit_count--;
        } else if (bat_count > 0) {
            grid[row][col].type = BAT;
            bat_count--;
        } else if (gas_count > 0) {
            grid[row][col].type = GAS;
            gas_count--;
        }
    }
}

// https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
bool Map::isTraversable() {
    // Convert generated cell grid into character grid to prep for flood fill
    for (size_t row = 0; row < row_count; row++) {
        for (size_t col = 0; col < col_count; col++) {
            if (grid[row][col].type == ROOM || grid[row][col].type == GAS)
                flood_grid[row][col] = 'T'; // 'T' for TRAVERSABLE
            else
                flood_grid[row][col] = 'N'; // 'N' for NOT TRAVERSABLE
        }
    }

    // Find a traversable cell and begin flood fill at its location
    unsigned int traversable_cells_found = 0; // The number of traversable cells found by the floodfill.
    bool foundStart = false; // Utilized to break out row-iterating loop
    for (size_t row = 0; row < row_count && !foundStart; row++) {
        for (size_t col = 0; col < col_count; col++) {
            if (flood_grid[row][col] == 'T') {
                // Begin flood fill here
                findTraversable(row, col, traversable_cells_found);
                foundStart = true;
                break;
            }
        }
    }

    // Traversable cells include ROOM cells and GAS cells
    const unsigned int traversable_cells_count = (row_count * col_count) - PIT_COUNT - BAT_COUNT;

    return traversable_cells_found == traversable_cells_count;
}

void Map::findTraversable(const size_t row, const size_t col, unsigned int& numFound) {
    if (row >= row_count || col >= col_count) // Base case 1: Out of bounds
        return;
    if (flood_grid[row][col] == 'V') // Base case 2: Already visited
        return;
    if (flood_grid[row][col] == 'N') // Base case 3: Not traversable
        return;

    flood_grid[row][col] = 'V'; // Mark as visited
    numFound++; // Count this traversable cell

    // Recurse in four directions
    findTraversable(row - 1, col, numFound);
    findTraversable(row + 1, col, numFound);
    findTraversable(row, col - 1, numFound);
    findTraversable(row, col + 1, numFound);
}




