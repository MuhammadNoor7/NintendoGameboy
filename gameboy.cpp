#include "gameboy.h"
#include "SnakeGame.h" // Include SnakeGame header
#include "wordle.h" // Include WordleGame header
#include "Sound.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

GameBoy::GameBoy() : window(sf::VideoMode(339, 480), "Nintendo Gameboy") {
    if (mainMenuTexture.loadFromFile("final.png")) {
        mainMenuSprite.setTexture(mainMenuTexture);
    }
    sounds.PlaySound(sounds.StartingSound);
    SelectedGame = nullptr;
}

void GameBoy::menu() {
    sf::Event event;
    bool menuDisplayStatus = true;

    while (menuDisplayStatus) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; // Exit the menu
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    SelectedGame = new SnakeGame(); // Dynamically allocate SnakeGame
                    sounds.StopSound(sounds.StartingSound);
                    //SnakeGame* snakeGame = new SnakeGame();
                    SelectedGame->playGame();// Set the selected game
                    menuDisplayStatus = false;      // Exit menu
                }
                if (event.key.code == sf::Keyboard::W) {
                    SelectedGame = new WordleGame(); // Dynamically allocate WordleGame
                    sounds.StopSound(sounds.StartingSound);
                    window.close();
                    menuDisplayStatus = false; // Exit menu
                    SelectedGame->playGame(); // Set the selected game
                }
                else if (event.key.code == sf::Keyboard::E) {
                    window.close();
                    menuDisplayStatus = false; // Exit menu
                }
            }
        }

        // Render the main menu
        window.clear();
        window.draw(mainMenuSprite);
        window.display();
    }
}

void GameBoy::start() {
    if (SelectedGame != nullptr) {
        SelectedGame->playGame(); // Start the selected game
    } else {
        std::cout << "No game selected!" << std::endl;
    }
}

void GameBoy::stop() {
    if (SelectedGame != nullptr) {
        SelectedGame->stopGame(); // Stop the selected game
        delete SelectedGame;      // Free the allocated memory
        SelectedGame = nullptr;   // Reset the pointer
    }
}
