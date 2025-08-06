#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "gameboy.h"

int main() {
    srand(time(0));
    GameBoy gameBoy;

    gameBoy.menu(); // Show the GameBoy menu
    gameBoy.start(); // Start the selected game (if any)

    return 0;
}
