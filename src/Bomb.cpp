//
// Created by zycha on 3/27/2025.
//

#include "../include/Bomb.h"
#include "../include/Cell.h"
#include "../include/Player.h"

#include <iostream>

Bomb::Bomb() : Item("dynamite", 'd') {}

bool Bomb::useItem(Cell* originCell, Player* player){
  char choice;
  std::cout << "How do you want to use " << this->name << ". Ignite and Throw(t), Cancel(c)" << std::endl;
  std::cin >> choice;

  if(originCell->getType() == GAS) return true;

  switch(choice){
    case 't':
    {
      Cell* cell = Item::promptForDirection(originCell, "throw");
      if(cell == nullptr) useItem(originCell, player);

      player->destroyItem(ItemCharacter::BOMB);
      if(cell->hasWumpus()){
        cell->setHasWumpus(false);
      } else if(cell->getType() == BAT){
        cell->setType(ROOM);
      } else if(cell->getType() == EXIT){
        cell->setType(OPEN_EXIT);
      }

      std::cout << "You hear an explosion in the distance" << std::endl;
      if(cell->getItem() != nullptr) cell->setItem(nullptr);
      return false;
    }
    case 'c':
      return false;
    default:
      return this->useItem(originCell, player);
  }
}
