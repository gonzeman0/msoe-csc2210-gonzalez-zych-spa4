cmake_minimum_required(VERSION 3.30)
project(spa4_wumpus_game)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a list of source files
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add the executable target
add_executable(spa4_wumpus_game ${SOURCES})

# Include the header files
target_include_directories(spa4_wumpus_game PRIVATE ${CMAKE_SOURCE_DIR}/include)