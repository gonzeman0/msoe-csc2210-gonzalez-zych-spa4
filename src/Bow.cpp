//
// Created by zycha on 3/26/2025.
//

#include "../include/Bow.h"
#include "../include/Arrow.h"

#include <iostream>

Bow::Bow() : Item("bow", 'b') {}

bool Bow::useItem(Cell* originCell, Player* player){
  char choice;
  std::cout << "How do you want to use " << this->name << ". Shoot(s), Throw(t), Cancel(c)" << std::endl;
  std::cin >> choice;

  switch(choice){
    case 's':
      return shoot(originCell, player);
    case 't':
      {
        std::string result = Item::basicThrow(originCell, player);
        if(result == "") useItem(originCell, player);
        std::cout << result << std::endl << std::endl;
        return false;
      }
    case 'c':
      return false;
    default:
      return this->useItem(originCell, player);
  }
}

bool Bow::shoot(Cell* originCell, Player* player){
  if(!player->hasItem('a')){
    std::cout << "You have nothing to shoot" << std::endl;
    return useItem(originCell, player);
  }
  Cell* cell = Item::promptForDirection(originCell, "shoot");
  if(cell == nullptr) useItem(originCell, player);

  player->destroyItem(ItemCharacter::ARROW);
  if(cell->hasWumpus()){
    cell->setHasWumpus(false);
    std::cout << "You hear a yelp in the distance" << std::endl;
    cell->setItem(new Arrow());
  } else if(cell->getType() == BAT){
    cell->setType(ROOM);
    std::cout << "You hear a sqeak and a thud in the distance" << std::endl;
    cell->setItem(new Arrow());
  } else{
    std::cout << cell->getBasicThrowMessage("arrow");
  }
  return false;
}