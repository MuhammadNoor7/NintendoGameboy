#ifndef gameboy_H
#define gameboy_H

#include <SFML/Graphics.hpp>
#include "game.h"
#include "Sound.h"



class GameBoy {
private:
    sf::RenderWindow window;
    sf::Texture mainMenuTexture;
    sf::Sprite mainMenuSprite;
    Game* SelectedGame; // Pointer to the selected game (polymorphic behavior)
    Sound sounds;

public:
    GameBoy();
    void menu();  // Displays the menu and sets SelectedGame
    void start(); // Starts the selected game
    void stop();  // Stops the selected game
};

#endif
