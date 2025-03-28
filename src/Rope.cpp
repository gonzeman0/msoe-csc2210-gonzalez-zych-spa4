//
// Created by zycha on 3/27/2025.
//

#include "../include/Rope.h"
#include "../include/Cell.h"
#include "../include/Player.h"



Rope::Rope() : Item("rope", '?') {}

bool Rope::useItem(Cell* originCell, Player* player){
  char choice;
  std::cout << "How do you want to use " << this->name << ". Knot Yourslef(k), Throw(t), Cancel(c)" << std::endl;
  std::cin >> choice;

  switch(choice){
    case 'k':
      if(originCell->getType() == CellType::EXIT) return true;
      player->setUsingRope(true);
      std::cout << "You tie the rope around you" << std::endl;
      return false;
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
