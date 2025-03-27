//
// Created by zycha on 3/26/2025.
//

#ifndef BOW_H
#define BOW_H

#include "item.h"
#include "cell.h"
#include "player.h"
#include <string>
#include <iostream>

class Bow : public Item {
public:
  Bow(std::string name, char useCharacter);

  bool useItem(Cell* originCell, Player* player);
  void shoot(Cell* originCell);
};

#endif //BOW_H
