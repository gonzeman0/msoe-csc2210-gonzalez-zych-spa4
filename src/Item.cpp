//
// Created by gonzalezem on 3/24/2025.
//

#include "../include/Item.h"

#include "../include/Player.h"
#include "../include/Cell.h"
#include <string>


Item::Item(std::string name, char useCharacter) : name(name), useCharacter(useCharacter){}

bool Item::useItem(Cell* originCell, Player* player){
  char choice;
  std::cout << "How do you want to use " << this->name << ". Throw(t), Cancel(c)" << std::endl;
  std::cin >> choice;

  switch(choice){
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

std::string Item::basicThrow(Cell* originCell, Player* player) {
  Cell* cell = this->promptForDirection(originCell, "throw");
  if(cell == nullptr) return"";

  player->destroyItem(this->getCharacter());
  return cell->getBasicThrowMessage(this->getName());
}

Cell* Item::promptForDirection(Cell* originCell, std::string message){
  std::cout << "Which direction do you want to " + message + " ('N', 'E', 'S', 'W') or Cancel(c)" << std::endl;
  char direction;
  std::cin >> direction;

  Cell* cell;
  switch(direction) {
    case 'c':
      return nullptr;
    case 'N':
      cell = originCell->getNorthCell();
      break;
    case 'E':
      cell = originCell->getEastCell();
      break;
    case 'S':
      cell = originCell->getSouthCell();
      break;
    case 'W':
      cell = originCell->getWestCell();
      break;
    default:
      cell = nullptr;
  }

  if(cell == nullptr){
    std::cout << "There is nothing that direction" << std::endl;
    return this->promptForDirection(originCell ,message);
  }
  return cell;
}