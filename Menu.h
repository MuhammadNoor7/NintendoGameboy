#ifndef MENU_H
#define MENU_H

#include <iostream>             
#include <string>
#include <SFML/Graphics.hpp>                       
#include "SFML/Audio.hpp"                          
using namespace std; 


class WordleGame;                                    // forward declaration of wordleGame class.

class Menu{
private:
//Sounds* Tilesound;                                  // dynamic tilesound object.
sf::Texture backtexture;
sf::Sprite backsprite;
sf::Font font;
sf::Text titleoption;                               // text objects for menu class.
sf::Text playgame;
sf::Text showscore;
sf::Text exit;


public:
    sf::SoundBuffer tileSound;
    sf::Sound tilesnd;
    int pick;                                      
    int total_picks;                                // total number of menu options.
    Menu();
   ~Menu();                                       
    void show_window(sf::RenderWindow& window);     // menu method to display menu options.
    void change_optioncol(sf::RenderWindow& window);  // changes colour when cursor moves on it.

    void pickoptions(sf::RenderWindow& window, WordleGame& wordle);  // to pick menu options.
};

#endif