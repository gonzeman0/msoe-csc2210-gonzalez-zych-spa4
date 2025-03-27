//
// Created by zycha on 3/27/2025.
//

#ifndef ARROW_H
#define ARROW_H

#include <string>
#include "Item.h"

class Arrow : public Item {
  public:
  Arrow();

  bool useItem(Cell* originCell, Player* player);
};

#endif //ARROW_H
