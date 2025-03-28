#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

// Header-only implementation of promptUser
inline std::string promptUser(const std::string &message) {
    std::cout << message;
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        input.erase(0, input.find_first_not_of(" \t\n\r\f\v")); // Trim leading whitespace
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1); // Trim trailing whitespace
        if (!input.empty()) {
            return input;
        }
    }
}

#endif // UTILS_H
