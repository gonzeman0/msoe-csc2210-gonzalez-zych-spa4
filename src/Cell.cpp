
#include "../include/Cell.h"
#include <iostream>

/**
 * This method retrieves the item currently stored in the cell and
 * sets the cell's item to nullptr, effectively removing it.
 *
 * @return A pointer to the item that was stored in the cell.
 *         Returns nullptr if no item was stored.
 */
Item* Cell::pickupItem() {
    Item* ret = item;
    item = nullptr;
    return ret;
}

void Cell::setHasPlayer(const bool has_p) {
    if (has_p == false) { // This action is always allowed
        this->has_player = has_p;
        return;
    }

    // If action is legal, perform
    this->has_player = true;
}

void Cell::setHasWumpus(const bool has_w) {
    if (has_w == false) { // This action is always allowed
        this->has_wumpus = has_w;
        return;
    }

    // Check for illegal actions
    if (this->has_player) {
        std::cerr << "ERROR in Cell::setHasWumpus(): Wumpus and player can't share a cell. Game should handle this logic" << std::endl;
        return;
    }

    // If action is legal, perform
    this->has_wumpus = true;
}