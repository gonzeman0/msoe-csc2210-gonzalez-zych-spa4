
#include "../include/Cell.h"
#include <iostream>
#include <string>

/**
 * This method retrieves the item currently stored in the cell and
 * sets the cell's item to nullptr, effectively removing it.
 *
 * @return A pointer to the item that was stored in the cell.
 *         Returns nullptr if no item was stored.
 */
Item* Cell::pickupItem() {
    Item* ret = item;
    item = nullptr;
    return ret;
}

void Cell::setHasPlayer(const bool has_p) {
    if (has_p == false) { // This action is always allowed
        this->has_player = has_p;
        return;
    }

    // If action is legal, perform
    this->has_player = true;
}

void Cell::setHasWumpus(const bool has_w) {
    if (has_w == false) { // This action is always allowed
        this->has_wumpus = has_w;
        return;
    }

    // Check for illegal actions
    if (this->has_player) {
        std::cerr << "ERROR in Cell::setHasWumpus(): Wumpus and player can't share a cell. Game should handle this logic" << std::endl;
        return;
    }

    // If action is legal, perform
    this->has_wumpus = true;
}

std::string Cell::getProximityMessage(){
  if(this->hasWumpus()) return "You smell something very rancid\n";

  switch (this->getType()){
      case EXIT:
        return "You see a nearby light\n";
      case PIT:
        return "You feel a light breeze\n";
      case BAT:
        return "You hear a squeak in the distance\n";
      case GAS:
        return "You smell something funny\n";
      default:
        return "";
  }
}

std::string Cell::getCurrentCellMessage(){
  switch (this->getType()){
    case ROOM:
      if(this->getItem() == nullptr) return "";
      return "You pick up a item\n";
    case EXIT:
      return "There is a bright light up above you\n";
    case BAT:
      return "A gaint bad comes out of nowhere and picks you up. You then get flown somewhere else\n";
    case GAS:
      return "You smell something funny\n";
    default:
      return "";
  }
}

std::string Cell::getDeathMessage(){
  if(this->hasWumpus()) return "You get eaten by a big hungry wumpus\n";
  switch (this->getType()){
    case PIT:
      return "You fall down an endless pit for eternity\n";
    case GAS:
      return "You ignite a flammable gas at get incinerated\n";
    default:
      return "You died";
  }
}

std::string Cell::getBasicThrowMessage(std::string name){
  if(this->hasWumpus()) return "You hear a growl in the distance\n";
  switch (this->getType()){
    case PIT:
      return "You hear nothing\n";
    case BAT:
      return "You hear flapping wings in the distance\n";
    default:
      return "You hear " + name + " hit the floor and break\n";
  }
}

