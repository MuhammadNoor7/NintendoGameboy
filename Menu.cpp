#include "wordle.h"
#include "Menu.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;


Menu::Menu()
{
    //Tilesound = new Sounds("tiledrop.wav");
    
    if(!backtexture.loadFromFile("menu.jpg"))
    {
        cout << "Error reading Image . " << endl;
    } 

    else 
        backsprite.setTexture(backtexture);
      

    if(!font.loadFromFile("font.ttf"))
        cout << "Error reading Font ." << endl;
  
titleoption.setFont(font);
titleoption.setCharacterSize(19);
titleoption.setString("MAIN MENU TO PLAY WORDLE:");
titleoption.setFillColor(sf::Color::White);
titleoption.setPosition(30,50);
titleoption.setStyle(sf::Text::Bold);

playgame.setFont(font);
playgame.setCharacterSize(15);
playgame.setString("PLAY GAME(P)");
playgame.setFillColor(sf::Color::White);
playgame.setPosition(120,180);
titleoption.setStyle(sf::Text::Bold);

showscore.setFont(font);
showscore.setCharacterSize(15);
showscore.setString("SCORE(S)");
showscore.setFillColor(sf::Color::White);
showscore.setPosition(120,220);
titleoption.setStyle(sf::Text::Bold);

exit.setFont(font);
exit.setCharacterSize(15);
exit.setString("EXIT GAME(E)");
exit.setFillColor(sf::Color::White);
exit.setPosition(120,260);
titleoption.setStyle(sf::Text::Bold);

pick=0;            // set default pick to 0.
total_picks=3;

if(!tileSound.loadFromFile("tiledrop.wav"))
    return;
tilesnd.setBuffer(tileSound);
 
}

void Menu::show_window(sf::RenderWindow& window)
{
    float xdir = static_cast<float>(window.getSize().x) / (backtexture.getSize().x);   // for precise setting.
    float ydir = static_cast<float>(window.getSize().y) / (backtexture.getSize().y);

    backsprite.setScale(xdir,ydir);

    window.clear();
    window.draw(backsprite);
    window.draw(titleoption);
    window.draw(playgame);
    window.draw(showscore);
    window.draw(exit);

    change_optioncol(window);         // changes col of option on which curses move.
    window.display();

}

void Menu::change_optioncol(sf::RenderWindow& window)
{
    playgame.setFillColor(sf::Color::White);
    showscore.setFillColor(sf::Color::White);
    exit.setFillColor(sf::Color::White);              // resetting color before picking.
    switch(pick)
    {
        case 0:
            playgame.setFillColor(sf::Color::Blue);      
            break;

        case 1:
            showscore.setFillColor(sf::Color::Blue);   
            break;
        
        case 2:
            exit.setFillColor(sf::Color::Blue);           // other options remain white.
            break;
    }
    
}


void Menu::pickoptions(sf::RenderWindow& window, WordleGame& wordle)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        
        else 
        {
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Up:
                        if(pick > 0)
                            pick--;
                            tilesnd.play();
                       //     Tilesound->PlaySound(Tilesound->TileSound);
                        return;

                    case sf::Keyboard::Down:
                        if(pick < total_picks)
                            pick++;
                            tilesnd.play();
                         //   Tilesound->PlaySound(Tilesound->TileSound);          // play sound when movinf up and down
                        return;

                    case sf::Keyboard::P:
                        pick=0;
                        cout << "\nWELCOME TO THE GAME:"  << endl;
                        change_optioncol(window);         // changes col of option on which curses move.
                        tilesnd.play();
                       // wordle.drawGame();
                        return;
                    case sf::Keyboard::S:
                        pick=1;
                        cout << "\nSCORE" << endl;
                        change_optioncol(window); 
                        tilesnd.play();    
                        return;
                    case sf::Keyboard::E:
                        pick=2;
                        cout << "\nEXITING" << endl;
                        change_optioncol(window);   
                        tilesnd.play();     
                        window.close();
                        return;
                }
            }
        }

    }
}

Menu::~Menu()
{
 //   delete Tilesound;
}