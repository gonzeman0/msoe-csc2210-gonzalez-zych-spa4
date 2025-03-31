# CSC 2210 | SPA 4

### Team Members:
- Adryan Zych (zycha@msoe.edu)
- Emanuel Gonzalez (gonzalezem@msoe.edu)

### Build Instructions
The repository includes `CMakeList.txt`, which CLion should detect and use to configure the project automatically. Alternatvely, run the following command at the root of the project:
<pre>g++ -std=c++20 -Iinclude src/*.cpp -o game</pre>
This command will generate an executable in the same directory that runs the game. Running this executable in a terminal allows you to play thee game.

### Debugging
There are to main components to the game:
1. Map generation. Creates a grid of Cell objects, links them with pointers, places hazards and items, and verifies that the exit will be accessible by the player.
2. Gameplay. The actual gameplay: player movement, and item/cell interactions. 

Map generation logic starts and ends in the `Game::Game()` constructor. Gameplay logic starts and ends in `Game::start()` method. If you utilize a debugger, it may be helpful to place your breakpoints at the start of these members. 

### Game Description
The player's objective is to escape the cave while avoiding potentially deadly hazards such as the Wumpus, Giant Bats, gas room, or endless pits. The player must traverse carefully traverse cells using the hints in order to avoid any hazards. The player may stumble upon items that will let them defend themselves or access the exit. 

A map can be accessed via 'M' to debug the game. 


