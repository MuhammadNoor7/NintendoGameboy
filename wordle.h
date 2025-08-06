#ifndef WORDLE_H
#define WORDLE_H

#include "game.h"
#include "gameboy.h"
//#include "Sound.h"             // for sound effect
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

class Word;
class Dictionary;
// -------------------------------------- // 

class PlayingKeyboard         
{

public:
    static int present_row;
    char guessing_power[6][5];                        // input entered from user.
    PlayingKeyboard();                              // constructor for Keyboard
    void getInput(sf::RenderWindow& window, Word& word, Dictionary& dictionary,WordleGame& game);              
}; 


class Grid 
{
private:
    const int grid_length;
    const int grid_height;

public:
    Grid();
    void drawGrid(sf::RenderWindow& window,sf::Font& font, PlayingKeyboard& keyboard,Word& word);                     
};


// ------------------------------------- // 

class Dictionary 
{
private:
    string words[14860];                           // whole txt file would be read in it.
    static int count;

public : 
    Dictionary();                             
    string Load_Dictionary(const string& filename);                 // to import dictionary from txt file
    string getString();                                              // to get a random word for guessing.

}; 


// -------------------------------------- // 

class Word             
{
private:
    int word_similarity;                        
  //  static int word_score;                            // updates score on basis of correction.
    string rndm_word;                                  // to get a random word for guessing from the imported txt.
    bool word_guessed[6];                                           

public:
    static int word_score;                            // updates score on basis of correction.
    sf::Color col_array [6][5] ;                              // char array to sore colours.
    Word();                             
    void checkGuess(sf::RenderWindow& window, Dictionary& dictionary, PlayingKeyboard& keyboard , WordleGame& game);   
    string random_setter(const string& word_imported);        // random word to be set in the word class from the dictionary.           
}; 

// ------------------------------------- // 

class WordleGame : public Game                           // inherits gameboy class
{
protected:
    Grid grid;
    sf::RenderWindow window;
    Dictionary dictionary; 
    Menu menu;
    PlayingKeyboard keyboard;
    Word word;
    string word_imported;          
    bool paused ;           // initilly paused set to false.
    const int total_attempts = 3;         // updates each time the attempt is incremented.
    const float max_gametime = 0.5*60;    // to convert mins to seconds.
   
public:
    static int attempts_played;                  // to keep check of each attempt.
   
    WordleGame();                       
    void drawGame() ;      
    void playGame() override;       // to play the game
    void stopGame()override;       // to stop the game

};

// -------------------------------------- // 

#endif