cmake_minimum_required(VERSION 3.30)
project(spa4_wumpus_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        spa4_wumpus_game
        src/main.cpp
        src/Cell.cpp
        src/Map.cpp
        src/Game.cpp
        src/Player.cpp
        src/Item.cpp
        src/Bow.cpp
        src/Arrow.cpp
)

target_include_directories(spa4_wumpus_game PRIVATE ${CMAKE_SOURCE_DIR}/include)
