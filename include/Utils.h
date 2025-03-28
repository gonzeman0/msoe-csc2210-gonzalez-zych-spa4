#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

// Header-only implementation of promptUser
inline std::string promptUser(const std::string& message) {
    std::cout << message;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

#endif // UTILS_H
