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
        map.printGrid();

        printCellData(player->getCurrentCell());
        input = promptUser("Player = @. Move ('N', 'E', 'S', 'W'), Use Item(i) or exit ('EXIT'): ");

        if(input[0] == 'i'){
            gameOver = player->useItem();
            std::cin.ignore();
            continue;
        }

        if (input.length() == 1)
            gameOver = player->move(input[0]);
        else if (input == "EXIT")
            gameOver = true;
        else
            std::cerr << "Error in Game::start(): Unrecognized token \"" << input << "\"" << std::endl;
    }
    std::cout << player->getCurrentCell()->getDeathMessage();
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