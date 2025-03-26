//
// Created by gonzalezem on 3/25/2025.
//

#include "../include/Player.h"
#include "../include/Cell.h"
#include <iostream>
#include <random>

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


bool Player::move(const char direction) {
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
            return false;
    }

    if (to_cell == nullptr) {
        std::cerr << "ERROR in Player::move(): There's no cell in the specified direction" << std::endl;
        return false;
    }

    current_cell->setHasPlayer(false);
    to_cell->setHasPlayer(true);
    current_cell = to_cell;

    if(isInHazzard(current_cell)) return true;
    return false;
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

bool Player::isInHazzard(Cell* cell){
  if(!cell->hasPlayer()) return false;

  if(cell->hasWumpus()) return true;

  switch(cell->getType()) {
    case PIT:
      return true;
    case BAT:
      randomMove();
      current_cell -> setHasPlayer(true);
      return isInHazzard(cell);
    case GAS:
      return false;
    default:
      return false;
  }
}

void Player::randomMove(){
    current_cell->setHasPlayer(false);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> magnitude(1, 8);
    std::uniform_int_distribution<int> direction(0, 1);

    int xMagnitude = magnitude(gen);
    int yMagnitude = magnitude(gen);
    int xDirection = direction(gen);
    int yDirection = direction(gen);

    for(int i = 0; i < xMagnitude; i++){
      xDirection == 0 ? quickMove('E') : quickMove('W');
    }
    for(int i = 0; i < yMagnitude; i++){
      yDirection == 0 ? quickMove('N') : quickMove('S');
    }
}

bool Player::quickMove(char direction){
  Cell* newCell;
  switch (direction) {
    case 'N':
      newCell = current_cell->getNorthCell();
      break;
    case 'E':
      newCell = current_cell->getEastCell();
      break;
    case 'S':
      newCell = current_cell->getSouthCell();
      break;
    case 'W':
      newCell = current_cell->getWestCell();
      break;
  }
  if(newCell == nullptr) return false;

  current_cell = newCell;
  return true;
}

