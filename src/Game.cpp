//
// Created by gonzalezem on 3/25/2025.
//

#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Cell.h"
#include "../include/Item.h"
#include <iostream>
#include <random>
#include <vector>

Game::Game(): map(), gameOver(false), player(new Player(map.spawnPlayer())){}

void Game::start() {
    std::string input;
    map.spawnWumpus();
    while (!gameOver) {

        printCellData(player->getCurrentCell());
        input = promptUser("Action: N)orth, E)ast, S)outh, W)est, I)nventory, M)ap, H)elp:  ");

        // All commands are a single character.
        if (input.length() != 1) {
            std::cout << "INPUT ERROR: Unrecognized token \"" << input << "\"" << std::endl;
            continue;
        }

        // Actions
        switch (input[0]) {
            case 'M':
                map.printGrid();
                break;
            case 'H':
                std::cout << mapKey << helpText;
                break;
            case 'I':
                gameOver = player->useItem();
                std::cin.ignore();
                break;
            case 'N':
            case 'E':
            case 'S':
            case 'W':
                gameOver = player->move(input[0]);
                break;
            default:
                std::cout << "INPUT ERROR: Unrecognized token \"" << input << "\"" << std::endl;
                break;
        }
    }
    std::cerr << player->getCurrentCell()->getDeathMessage();
}

std::string promptUser(const std::string& message) {
    std::cout << message;
    std::string userInput;
    std::getline(std::cin, userInput);
    return userInput;
}

void Game::printCellData(Cell* cell){
    Cell* northCell = cell->getNorthCell();
    Cell* southCell = cell->getSouthCell();
    Cell* eastCell = cell->getEastCell();
    Cell* westCell = cell->getWestCell();

    std::vector<std::string> messages(5, "");

    addToRandomPosition(messages, cell->getCurrentCellMessage());
    if(northCell != nullptr) addToRandomPosition(messages, northCell->getProximityMessage());
    if(southCell != nullptr) addToRandomPosition(messages, southCell->getProximityMessage());
    if(eastCell != nullptr) addToRandomPosition(messages, eastCell->getProximityMessage());
    if(westCell != nullptr) addToRandomPosition(messages, westCell->getProximityMessage());

    for(int i = 0; i < messages.size(); i++){
      std::cout << messages[i];
    }
}

void Game::addToRandomPosition(std::vector<std::string>& array, std::string message){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random(0, 4);
    int index = random(gen);

    while(!array[index].empty()){ index = random(gen);}
    array[index] = message;
}