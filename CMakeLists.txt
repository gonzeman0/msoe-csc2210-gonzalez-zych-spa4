cmake_minimum_required(VERSION 3.16)
project(spa4_wumpus LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers from "include/"
include_directories(include)

# Add all source files from "src/"
file(GLOB SOURCES "src/*.cpp")

# Define the executable
add_executable(spa4_wumpus ${SOURCES})
