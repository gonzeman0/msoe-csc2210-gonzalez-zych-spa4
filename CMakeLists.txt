cmake_minimum_required(VERSION 3.30)
project(spa4_wumpus_game)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(
        spa4_wumpus_game
        src/main.cpp
        src/Cell.cpp
        src/Map.cpp
        src/Game.cpp
        src/Player.cpp
        src/Item.cpp
)
