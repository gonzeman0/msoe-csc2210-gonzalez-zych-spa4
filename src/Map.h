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

class Map {
    Cell grid[ROWS][COLS];
    char flood_grid[ROWS][COLS]; // Utilized by isTraversible();

    // Map generation methods.
    void initializeGrid();
    void addRandomHazards(unsigned int pit_count, unsigned int bat_count, unsigned int gas_count);
    bool isTraversable();
    void findTraversable(size_t row, size_t col, unsigned int& numFound);

    void placeExit();

public:
        const size_t row_count = ROWS;
        const size_t col_count = COLS;

        Map();
        Cell& getCell(size_t row, size_t col);
};



#endif //MAP_H
