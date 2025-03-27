//
// Created by zycha on 3/27/2025.
//

#ifndef BOMB_H
#define BOMB_H

#include "Item.h"

class Bomb : public Item {
public:
  Bomb();

  bool useItem(Cell* originCell, Player* player);
};

#endif //BOMB_H
