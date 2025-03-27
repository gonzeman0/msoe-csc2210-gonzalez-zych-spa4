//
// Created by gonzalezem on 3/24/2025.
//

#ifndef ITEM_H
#define ITEM_H


#include <string>
#include <iostream>

class Cell;
class Player;

enum ItemCharacter{
  BOW = 'b',
  ARROW = 'a',
  ROPE = 'r',
  BOMB = 'd'
};

class Item {
public:
    std::string getName() const { return name; }
    char getCharacter() const { return useCharacter; }

    Item(std::string name, char useCharacter);

    std::string name;
    char useCharacter;

    virtual bool useItem(Cell* originCell, Player* player);

    std::string basicThrow(Cell* originCell, Player* player);

    Cell* promptForDirection(Cell* originCell, std::string message);
};



#endif //ITEM_H
