//
// Created by zycha on 3/27/2025.
//

#ifndef ROPE_H
#define ROPE_H

#include "Item.h"

class Rope : public Item {
public:
  Rope();

  bool useItem(Cell* originCell, Player* player);
};

#endif //ROPE_H
