//
// Created by gonzalezem on 3/25/2025.
//

#include "Player.h"
#include "Cell.h"
#include <iostream>

Player::Player(Cell& starting_cell): inventory() {
    if (!starting_cell.hasPlayer()) {
        std::cerr << "ERROR in Player(): Starting cell must be previously assigned via Map::spawnPlayer()" << std::endl;
        return;
    }
    if (starting_cell.getType() != ROOM) {
        std::cerr << "ERROR in Player(): Assigned cell should be of type ROOM. Verify Map::spawnPlayer() implementation" << std::endl;
        return;
    }

    current_cell = &starting_cell;
    current_cell->setHasPlayer(true);
}


void Player::move(const char direction) {
    Cell* to_cell;
    switch (direction) {
        case 'N':
            to_cell = current_cell->getNorthCell();
            break;
        case 'E':
            to_cell = current_cell->getEastCell();
            break;
        case 'S':
            to_cell = current_cell->getSouthCell();
            break;
        case 'W':
            to_cell = current_cell->getWestCell();
            break;
        default:
            std::cerr << "ERROR in Player::move(): Undefined direction '" << direction << "'" << std::endl;
            return;
    }

    if (to_cell == nullptr) {
        std::cerr << "ERROR in Player::move(): There's no cell in the specified direction" << std::endl;
        return;
    }

    current_cell->setHasPlayer(false);
    to_cell->setHasPlayer(true);
    current_cell = to_cell;
}

void Player::pickup(Item* item) {
    if (item == nullptr)
        return;
    auto it = inventory.find(item->name);
    if (it != inventory.end()) {
        // If the item exists in inventory, increment the count
        it->second++;
    } else {
        // If the item does not exist, add it with a count of 1
        inventory[item->name] = 1;
    }
}

