//
// Created by gonzalezem on 3/25/2025.
//

#ifndef GAME_H
#define GAME_H

#include "Cell.h"
#include <string>
#include <vector>
#include "Player.h"
#include "Map.h"

class Game {
    Map map;
    bool gameOver;
    Player* player;

    public:
        Game();
        void start();
        void printCellData(Cell* cell);
        void addToRandomPosition(std::vector<std::string>& array, std::string message);
};


#endif //GAME_H
