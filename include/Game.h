//
// Created by gonzalezem on 3/25/2025.
//

#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Cell.h"
#include <string>
#include <vector>

#include "Player.h"

class Game {
    Map map;
    bool gameOver;
    Player* player;

    public:
        Game();
        void start();
        void displayMap();
        void printCellData(Cell* cell);
        void addToRandomPosition(std::vector<std::string>& array, std::string message);
};

/**
 * Prompts the user with a specified message and retrieves input from the user.
 *
 * @param message The message to display to the user as a prompt.
 * @return The input entered by the user as a string.
 */
std::string promptUser(const std::string& message);

#endif //GAME_H
