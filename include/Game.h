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

const std::string helpText =
    "========================================\n"
    "HELP GUIDE\n"
    "========================================\n"
    "Goal:\n"
    "Escape the dark cave. Survive.\n"
    "\n"
    "----------------------------------------\n"
    "Hazards:\n"
    "- Wumpus         = Huge, foul, and hungry.\n"
    "- Endless Pit    = Deep... bottomless.\n"
    "- Giant Bat      = Blind, unpredictable\n"
    "- Flammable Gas  = Smells funny. Harmless... right?\n"
    "\n"
    "----------------------------------------\n"
    "Items:\n"
    "- Bow        = Can shoot arrows.\n"
    "- Arrow      = Use with bow.\n"
    "- Dynamite   = Explosive. Very loud.\n"
    "- Rope       = Useful for tying or climbing.\n"
    "\n"
    "Use or throw items wisely to stay alive and uncover secrets.\n"
    "========================================\n";



const std::string mapKey =
    "==================== MAP KEY ====================\n"
    "| #  = Wumpus          | )  = Bow               |\n"
    "| !  = Giant Bat       | >  = Arrow             |\n"
    "| G  = Flammable Gas   | ?  = Rope              |\n"
    "| @  = Endless Pit     | D  = Dynamite          |\n"
    "| E  = Exit            | O  = Open Exit         |\n"
    "=================================================\n";

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
