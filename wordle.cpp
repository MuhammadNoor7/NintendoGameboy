#include "wordle.h"
#include "Menu.h"

#include <iostream>
#include <string>
#include <cstdlib>   
#include <ctime>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>              // both for reading and writing
using namespace std;


// All static declared here.
int Dictionary::count =0;
int PlayingKeyboard::present_row = 0;
int WordleGame::attempts_played=0;
int Word::word_score=0;




WordleGame::WordleGame()
{
    dictionary.Load_Dictionary("dictionary.txt");   // to load the dictionary,
    paused = false;
}




void WordleGame::playGame()
{

    sf::RenderWindow Wordlewindow(sf::VideoMode(339, 480), "Wordle Menu");
    Menu menu; // to call menu

    Wordlewindow.setFramerateLimit(60); // runs the game in 60 fps for smoother response.
    while (Wordlewindow.isOpen())
    {
        sf::Event event;
        while (Wordlewindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Wordlewindow.close();
        }
        Wordlewindow.clear();
        menu.show_window(Wordlewindow);        // shows the menu .
        menu.pickoptions(Wordlewindow, *this); // this wordle ref passed.

        if (menu.pick == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            Wordlewindow.close(); // wordle menu closed.
            sf::Texture mainMenuTexture;
            sf::Sprite mainMenuSprite;
            sf::RenderWindow gameWindow(sf::VideoMode(339, 480), "Wordle Game");
            attempts_played = 0;

            gameWindow.setFramerateLimit(60);       // runs the game in 60 fps for smoother response.
            word_imported = dictionary.getString(); // imports a random word from the dictionary.
            cout << "\n-----------Random Word for User to guess :" << word_imported << "------------" << endl;
            word.random_setter(word_imported);

            if (mainMenuTexture.loadFromFile("play.png"))
            {
                mainMenuSprite.setTexture(mainMenuTexture);
                float xdir = static_cast<float>(gameWindow.getSize().x) / (mainMenuTexture.getSize().x); // for precise setting.
                float ydir = static_cast<float>(gameWindow.getSize().y) / (mainMenuTexture.getSize().y);
                /

                    mainMenuSprite.setScale(xdir, ydir);
            }

            sf::Font font;
            if (!font.loadFromFile("font.ttf"))
            {
                cout << "Error loading font" << endl;
                return;
            }
            // adding clock

            sf::Clock clock;

            while (gameWindow.isOpen())
            {
                sf::Event event;
                while (gameWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        gameWindow.close();

                    keyboard.getInput(gameWindow, word, dictionary, *this);

                    if (event.key.code == sf::Keyboard::Space)
                        paused = true; // reversed to its transition state.

                    if (event.key.code == sf::Keyboard::Escape)
                        paused = false; // reversed again to its transition state.
                }
                // validation if user plays more than 3 times under 15 mins.
                if (attempts_played > total_attempts)
                {
                    sf::Text attempts_info;
                    attempts_info.setFont(font);
                    attempts_info.setCharacterSize(16);
                    attempts_info.setFillColor(sf::Color::White);
                    attempts_info.setPosition(20, 90);
                    attempts_info.setString("Maximum Attempts Reached / 15 Mins.");
                    attempts_info.setStyle(sf::Text::Bold);
                    gameWindow.draw(attempts_info);
                    gameWindow.close();
                }
                // validation if clock time exceeds 900 seconds
                else if (clock.getElapsedTime().asSeconds() > max_gametime)
                {
                    sf::Text clocktime;
                    clocktime.setFont(font);
                    clocktime.setCharacterSize(16);
                    clocktime.setFillColor(sf::Color::White);
                    clocktime.setPosition(20, 100);
                    clocktime.setString("Maximum Time Limit Reached (15 mins)");
                    clocktime.setStyle(sf::Text::Bold);
                    gameWindow.draw(clocktime);
                    gameWindow.close();
                }
                else if (!paused)
                {
                    gameWindow.clear();
                    gameWindow.draw(mainMenuSprite);
                    grid.drawGrid(gameWindow, font, keyboard, word); // new grid made on window.
                }
                else if (paused)
                {
                    sf::Text Paused;
                    Paused.setFont(font);
                    Paused.setCharacterSize(16);
                    Paused.setFillColor(sf::Color::White);
                    Paused.setPosition(20, 80);
                    Paused.setString("Game Paused.Press ESC to Contimue:");
                    Paused.setStyle(sf::Text::Bold);
                    gameWindow.draw(Paused);
                }
                else
                    cout << "Good to go.";
                gameWindow.display(); // to display new window with grid.
            }
            return;
        }
        Wordlewindow.display(); // to display new window with grid.
    }
   
            
}


void WordleGame::stopGame()
{
    cout << "Stop Game" << endl;
}

// --------------------- Grid class -------------------- // 

Grid::Grid() : grid_length(6), grid_height(5)  
{
 // const always initialized in member initialization.
}

void Grid::drawGrid(sf::RenderWindow& window, sf::Font& font,PlayingKeyboard& keyboard, Word& word)
{
    float cell_size = 25.0f;     // each cell size
    float padding = 20.0f;       // padding between cells for text.


    for (int i=0 ; i<grid_length ; i++)
    {
        for (int j=0 ; j< grid_height ; j++)
        {
            sf::RectangleShape rectangle(sf::Vector2f(cell_size,cell_size));  // grid structure
            rectangle.setPosition(100+j*cell_size,200+i*cell_size);
            rectangle.setFillColor(word.col_array[i][j]);          // filling col in grid.
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setOutlineThickness(1.4f); 

            window.draw(rectangle);                  // to draw the grid.

           sf::Text Guess;
           Guess.setFont(font);
           Guess.setCharacterSize(15);
           Guess.setFillColor(sf::Color::Red);
           Guess.setString(std::string(1,keyboard.guessing_power[i][j]));     // to show only one letter is placed.
           Guess.setPosition((100+j*cell_size+ cell_size/4) , (200+i*cell_size + cell_size/4));
           Guess.setStyle(sf::Text::Bold);
           window.draw(Guess);
           
        }
    }

}


// --------------------- Dictionary class -------------------- // 

Dictionary::Dictionary()
{
    srand(time(NULL));
}


string Dictionary::Load_Dictionary(const string& filename)
{
    ifstream inFile("dictionary.txt");
    if (!inFile.is_open())
    {
        cerr << "Error in Opening Dictionary File" << endl;
    }
    
    string oneline;
    while(getline(inFile,oneline) && count < 14860)
    {
        words[count] = oneline ;             // to add all words in this array.
        count++;                                       // to keep track.
    }

    inFile.close();               
    return "Dictionary Reading Successful. \n";
}

string Dictionary::getString()
{
    int random_index = rand()% count;
    string random_word = words[random_index];
    return random_word;
}


// --------------------- Keyboard class -------------------- // 


PlayingKeyboard::PlayingKeyboard()
{
    for(int i =0 ; i < 6 ; i++)
    {
        for (int j=0 ; j<5 ; j++)
        {
            guessing_power[i][j] = '?';
        }
    }
}


void PlayingKeyboard::getInput(sf::RenderWindow& window,Word& word, Dictionary& dictionary, WordleGame& game)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        
        else if (event.type == sf::Event::TextEntered)
        {
            if(((event.text.unicode >= 'A') && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z'))
            {
                if(present_row < 6)
                {
                    for (int j=0; j<5;j++)
                    {
                        if(guessing_power[present_row][j]=='?')
                        {
                            guessing_power[present_row][j] = static_cast<char>(event.text.unicode);

                            if(j==4)              // current row finishing, so move towards new row.
                            {
                                word.checkGuess(window,dictionary,*this,game);        // checks the word and colours.
                                present_row++;           // updated .
                            }
                           break;
                        }

                    }
                }
                
            }

            /*else if((event.text.unicode == sf::Keyboard::Backspace))
            {
            
                for (int j=4;j>=0; j--)                              // enitre row clears, flexible enough.
                {

                    guessing_power[present_row][j] = '?' ;          // if user wants to press backspace and choose another word.
                }
            } */
        }
    }
}


// --------------------- Word class -------------------- // 

Word::Word()
{
    word_similarity = 0;
    for(int i=0 ; i < 6 ; i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            col_array[i][j] = sf::Color::White;                   // initializing color array with white.
        }
    }
}

string Word::random_setter(const string& word_imported)
{
    rndm_word = word_imported;
    return rndm_word;
}

void Word::checkGuess(sf::RenderWindow& window, Dictionary& dictionary, PlayingKeyboard& keyboard, WordleGame& game)
{
    word_similarity = 0 ;            // for the next guess.
    word_guessed[5] = {false};          // initialized to 0 initially.
   
        for(int j=0 ; j<5 ; j++)
        {
           
            if(rndm_word[j] == keyboard.guessing_power[PlayingKeyboard::present_row][j])     // present row accessed as it was static member of the keyboard class.
            {
                //cout << "Well Done !! You guessed the random word  Right and at the Right index." << endl;  // green shade.
                word_similarity++;
                col_array[PlayingKeyboard::present_row][j] = sf::Color::Green;     // green added.
                word_guessed[j] = true;
        
            }
        }

        for(int j=0 ; j < 5 ; j++)
        {
            if(!word_guessed[j])
            {
                for(int k=0 ; k<5 ; k++)
                {
                    if(rndm_word[j] == keyboard.guessing_power[PlayingKeyboard::present_row][k]&& !word_guessed[k])
                    {
                      //  cout << "Sorry!! You  did  guess the random word  Right and not  at the  Right Spot."<<endl;  // yellow shade. 
                        col_array[PlayingKeyboard::present_row][j] = sf::Color::Yellow;    
                        word_similarity++;
                        word_guessed[k]=true;
                    }
                }
            }
        }
        for(int j=0 ; j<5; j++)
        {
            if(!word_guessed[j])
            {
              //  cout << "Oops!! You  did not guess the random word  Right and at the  Right Spot."<<endl;  // gray shade. "
                col_array[PlayingKeyboard::present_row][j]= sf::Color::Cyan;
            }

        }
        sf::Text score_screen;
        sf::Font font;



        if(word_similarity == 5)
        {
            word_score = word_similarity*20;

            if(!font.loadFromFile("font.ttf"))
                cout << "Error loading font";
            score_screen.setFont(font);
            score_screen.setCharacterSize(30);
            score_screen.setOutlineColor(sf::Color::Black);
            score_screen.setFillColor(sf::Color::White);
            score_screen.setPosition(50,200);
            score_screen.setString("Your final score:" + to_string(word_score) + "\nCONGRATULATIONS! You guessed the Wordle correctly.");
            window.clear();
            window.draw(score_screen);
            window.display();

            WordleGame::attempts_played++;

        }
}

