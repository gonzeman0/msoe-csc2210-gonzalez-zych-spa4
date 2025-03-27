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
  Bow();

  bool useItem(Cell* originCell, Player* player);
  bool shoot(Cell* originCell, Player* player);
};

#endif //BOW_H
