//
// Created by gonzalezem on 3/24/2025.
//

#include "../include/Map.h"
#include <iostream>
#include <cstdlib>  // For random number generation
#include <ctime>    // For random number generation



Map::Map() {
    // Set random seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Instantiate dynamic Cell and Item objects.
    instantiateItems(BOW_COUNT, ARROW_COUNT, BOMB_COUNT, ROPE_COUNT);

    // Generate a map until a valid one is found.
    bool valid_map_created = false;
    while (!valid_map_created) {
        initializeGrid();
        addRandomHazards(PIT_COUNT, BAT_COUNT, GAS_COUNT);
        valid_map_created = isTraversable();
    }

    placeItemsRandomly(); // TODO
    placeExit();
}

Map::~Map() {
    // Go through the grid and delete any items that haven't been deleted yet
    for (size_t row = 0; row < row_count; ++row) {
        for (size_t col = 0; col < col_count; ++col) {
            if (grid[row][col].item != nullptr) {
                delete grid[row][col].item; // Free the dynamically allocated memory
                grid[row][col].item = nullptr; // Set the pointer to nullptr to avoid dangling references
            }
        }
    }

}

void Map::printGrid() const {
    // Print column headers for better readability
    std::cout << "    ";
    for (size_t col = 0; col < col_count; ++col) {
        std::cout << col << " ";
    }
    std::cout << "\n";

    // Print a row separator
    std::cout << "  +-";
    for (size_t col = 0; col < col_count; ++col) {
        std::cout << "--";
    }
    std::cout << "+\n";

    // Iterate through each row of the grid
    for (size_t row = 0; row < row_count; ++row) {
        // Print row header
        std::cout << row << " | ";

        // Iterate through each cell in the current row
        for (size_t col = 0; col < col_count; ++col) {
            char displayChar;

            // Define display characters for each cell type
            switch (grid[row][col].type) {
                case ROOM:
                    displayChar = '.'; // Empty room
                break;
                case PIT:
                    displayChar = '@'; // Pit
                break;
                case BAT:
                    displayChar = '!'; // Bat
                break;
                case GAS:
                    displayChar = 'G'; // Gas
                break;
                case EXIT:
                    displayChar = 'E'; // Exit
                break;
                case OPEN_EXIT:
                    displayChar = 'O'; // Exit
                break;
                default:
                    displayChar = '_'; // Unknown or special case
                break;
            }

            // In order of display priority.
            if (grid[row][col].has_wumpus) {
                displayChar = '#';
            } else if (grid[row][col].has_player) {
                displayChar = '+';
            } else if(grid[row][col].item != nullptr) {
                displayChar = grid[row][col].getItem()->getCharacter();
            }

            // Print the character for this cell
            std::cout << displayChar << " ";
        }

        // End of the row
        std::cout << "|\n";
    }

    // Print the bottom border
    std::cout << "  +-";
    for (size_t col = 0; col < col_count; ++col) {
        std::cout << "--";
    }
    std::cout << "+\n";
}

/**
 * Populates the map's item array with the specified quantities of bows, arrows, bombs, and ropes.
 * Items are added one by one in the provided order until the requested quantities are filled.
 *
 * @param bow_count The number of Bow items to instantiate.
 * @param arrow_count The number of Arrow items to instantiate.
 * @param bomb_count The number of Bomb items to instantiate.
 * @param rope_count The number of Rope items to instantiate.
 */
void Map::instantiateItems(unsigned int bow_count, unsigned int arrow_count, unsigned int bomb_count, unsigned int rope_count) {
    size_t index = 0;
    while (bow_count > 0 || arrow_count > 0 || bomb_count > 0 || rope_count > 0) {
        if (bow_count > 0) {
            items[index] = new Bow();
            bow_count--;
        } else if (arrow_count > 0) {
            items[index] = new Arrow();
            arrow_count--;
        } else if (bomb_count > 0) {
            items[index] = new Bomb();
            bomb_count--;
        } else if (rope_count > 0) {
            items[index] = new Rope();
            rope_count--;
        }
        index++;
    }
}



/**
 * Initializes the grid for the map by setting all cells to a default state and configuring
 * adjacency relationships between cells. Each cell is initialized as a ROOM and is set
 * to not contain a player or Wumpus. The adjacency pointers (north, south, east, west)
 * are established only if the neighboring cells are within the grid bounds.
 */
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


/**
 * Adds random hazards (pits, bats, and gas) to the map until the specified counts are met.
 * The hazards are placed in random unoccupied cells in the grid.
 * If the total number of hazards exceeds the available number of cells in the grid,
 * an error message is displayed.
 *
 * @param pit_count The number of pit hazards to be placed on the map.
 * @param bat_count The number of bat hazards to be placed on the map.
 * @param gas_count The number of gas hazards to be placed on the map.
 */
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


void Map::placeItemsRandomly() {
    size_t items_placed = 0;
    const size_t item_count = BOMB_COUNT + ARROW_COUNT + BOW_COUNT + ROPE_COUNT;
    while (items_placed < item_count) {
        // Generate random location
        const size_t row = std::rand() % row_count;
        const size_t col = std::rand() % col_count;

        // Check if the cell is already occupied
        if (grid[row][col].type != ROOM || grid[row][col].item != nullptr)
            continue;

        // Place item
        grid[row][col].item = items[items_placed];
        items_placed++;
    }
}

/**
 * This function determines whether all traversable cells (ROOM or GAS)
 * in the generated map are connected. It uses flood fill to verify
 * connectivity between traversable cells.
 *
 * @return true if all traversable cells are connected; false otherwise.
 */
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
    if (!foundStart) {
        std::cerr << "ERROR in Map.isTraversable(): Found no traversable cells!";
    }

    // Traversable cells include ROOM cells and GAS cells
    const unsigned int traversable_cells_count = (row_count * col_count) - PIT_COUNT - BAT_COUNT;

    return traversable_cells_found == traversable_cells_count;
}

/**
 * Performs a flood fill operation to count the number of traversable cells
 * starting from the specified coordinates in a 2D grid.
 *
 * @param row The current row index in the grid.
 * @param col The current column index in the grid.
 * @param numFound A reference to the count of traversable cells found so far.
 *                 This value is incremented as traversable cells are discovered.
 *
 *  See https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
 */
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

void Map::placeExit() {
    while (true) {
        // Generate random row and column
        const size_t row = std::rand() % ROWS;
        const size_t col = std::rand() % COLS;

        // Get the cell at the random coordinates
        Cell* cell = &grid[row][col];
        if (cell->type == ROOM && !cell->hasPlayer() && !cell->hasWumpus()) {
            cell->type = EXIT;
            return;
        }
    }
}


Cell& Map::spawnWumpus() {
    while (true) {
        // Generate random row and column
        const size_t row = std::rand() % ROWS;
        const size_t col = std::rand() % COLS;

        // Get the cell at the random coordinates
        Cell* cell = &grid[row][col];
        if(cell->getType() == PIT || cell->getType() == BAT || cell->getType() == EXIT) continue;
        if (!cell->hasPlayer() && !cell->hasWumpus()) {
            cell->setHasWumpus(true);
            return *cell;
        }
    }
}

Cell& Map::spawnPlayer() {
    // Seed the random number generator if needed (optional, depending on the application setup)
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (true) {
        // Generate random row and column
        const size_t row = std::rand() % ROWS;
        const size_t col = std::rand() % COLS;

        // Get the cell at the random coordinates
        Cell* cell = &grid[row][col];
        if (cell->type == ROOM && !cell->hasPlayer() && !cell->hasWumpus() && cell->getItem() == nullptr) {
            cell->setHasPlayer(true);
            return *cell;
        }
    }
}

Cell* Map::getCell(size_t row, size_t col) {
    // Check if the row and column are within the valid range
    if (row < ROWS && col < COLS) {
        return &grid[row][col]; // Return a pointer to the cell
    }
    return nullptr; // Coordinates are out of bounds
}




