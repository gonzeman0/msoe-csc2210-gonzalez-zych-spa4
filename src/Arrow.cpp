//
// Created by zycha on 3/27/2025.
//
#include "../include/Arrow.h"

Arrow::Arrow() : Item("arrow", 'a') {}

bool Arrow::useItem(Cell* originCell, Player* player){
  return Item::useItem(originCell, player);
}