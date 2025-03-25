//
// Created by gonzalezem on 3/25/2025.
//

#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game(): map(), gameOver(false), player(map.spawnPlayer()) {}

void Game::start() {
    std::string input;
    while (!gameOver) {
        map.printGrid();
        input = promptUser("Player = @. Move ('N', 'E', 'S', 'W') or exit ('EXIT'): ");
        if (input.length() == 1)
            player.move(input[0]);
        else if (input == "EXIT")
            gameOver = true;
        else
            std::cerr << "Error in Game::start(): Unrecognized token '" << input << '"';

    }
}

std::string promptUser(const std::string& message) {
    std::cout << message;
    std::string userInput;
    std::getline(std::cin, userInput);
    return userInput;
}