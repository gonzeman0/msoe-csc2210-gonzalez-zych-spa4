//
// Created by zycha on 3/26/2025.
//

#include "../include/Bow.h"

#include "../include/Cell.h"
#include <iostream>

Bow::Bow(std::string name, char useCharacter) : Item(name, useCharacter) {}

bool Bow::useItem(Cell* originCell, Player* player){
  char choice;
  std::cout << "How do you want to use " << this->name << ". Shoot(s), Throw(t), Cancel(c)" << std::endl;
  std::cin >> choice;

  switch(choice){
    case 's':

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

void Bow::shoot(Cell* originCell){

}