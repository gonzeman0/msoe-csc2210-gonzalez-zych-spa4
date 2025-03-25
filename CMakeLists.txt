cmake_minimum_required(VERSION 3.30)
project(spa4_wumpus_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(spa4_wumpus_game src/main.cpp src/map.cpp src/Cell.h)
