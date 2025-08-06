#include "SnakeGame.h"
#include "game.h"
#include <iostream>
using namespace std;




void SnakeGame::playGame()
{
   
    srand(time(0));
    Snake snake;
    Food food;
    Hurdle hurdle;

    //image adding
    sf::Texture texForHurdle, texForFood;
    
    if (!texForHurdle.loadFromFile("hurdle.png"))
        
    if(!texForFood.loadFromFile("apple.png"))
    
    

    //sound adding
     sf::SoundBuffer buffer, buffer2;
    // if (!buffer.loadFromFile("wow.wav"))
    //     return;
     sf::Sound sound;
    // sound.setBuffer(buffer);

    //another sound for eating
    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("eat.wav"))
        return;
    sf::Sound sound2;
    sound2.setBuffer(buffer2);
    
    int windowWidth = 800;
    int windowHeight = 800;
    int cellSize = 40;
    int score = 0;
    int gameSpeed = 150;
    int GameRunning = 1;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake Game");
     sf::Texture backgroundTexture;
     if (!backgroundTexture.loadFromFile("check.png")) {
         std::cout << "Error loading background image." << std::endl;
     }
     sf::Sprite backgroundSprite(backgroundTexture);
    sf::Clock clock,clock2;
    sf::Time time;
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    cell.setFillColor(sf::Color::Yellow);
    sf::CircleShape foodCell(cellSize / 2);
    foodCell.setFillColor(sf::Color::Red);
    //foodCell.setTexture(&texForFood);
    sf::RectangleShape hurdleCell(sf::Vector2f(cellSize, cellSize));
    hurdleCell.setTexture(&texForHurdle);
    //hurdleCell.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    snake.changeDirection(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    snake.changeDirection(0, 1);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    snake.changeDirection(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    snake.changeDirection(1, 0);
                }
            }
        }

        time = clock.getElapsedTime();
        if (time.asMilliseconds() > gameSpeed) {
            clock.restart();

            if (GameRunning == 1) {
                snake.updateDirection();
                snake.moveSnake();

                for (int i = 0; i < 5; i++) {
                    if (snake.getSnakePosX(0) == food.getFoodPosX(i) && snake.getSnakePosY(0) == food.getFoodPosY(i) && food.getFoodStatus(i) != 0) {
                        snake.increaseLength();
                        sound2.play();
                        food.setFoodStatus(i, 0);  
                        score++;
                    }
                }

                for (int i = 0; i < 5; i++) {
                    if (snake.getSnakePosX(0) == hurdle.getHurdlePosX(i) && snake.getSnakePosY(0) == hurdle.getHurdlePosY(i)) {
                        sound.play();
                        GameRunning = 0;  
                    }
                }


                for (int i = 1; i < snake.getSnakeLength(); i++) {
                    if (snake.getSnakePosX(0) == snake.getSnakePosX(i) && snake.getSnakePosY(0) == snake.getSnakePosY(i)) {
                        sound.play();
                        GameRunning = 0;  
                    }
                }

                if (snake.getSnakePosX(0) < 0 || snake.getSnakePosX(0) >= 20 || snake.getSnakePosY(0) < 0 || snake.getSnakePosY(0) >= 20) {
                    sound.play();
                    GameRunning = 0;  
                }

                

                
            }
        }


    if (clock2.getElapsedTime().asSeconds() > 5.0f) {
    //srand(time(0));
    food.generateFood(); // Regenerate food positions
    for (int i = 0; i < 5; i++) {
        hurdle.setHurdlePosX(i, rand() % 20); // Set new X position for hurdle
        hurdle.setHurdlePosY(i, rand() % 20); // Set new Y position for hurdle
    }
    clock2.restart(); // Reset the clock
}



        // Drawing
        window.clear();
          
        window.draw(backgroundSprite);

        
        for (int i = 0; i < snake.getSnakeLength(); i++) {
            cell.setPosition(snake.getSnakePosX(i) * cellSize, snake.getSnakePosY(i) * cellSize);
            window.draw(cell);
        }

        for (int i = 0; i < 5; i++) {
            if (food.getFoodStatus(i) == 1) {
                foodCell.setPosition(food.getFoodPosX(i) * cellSize, food.getFoodPosY(i) * cellSize);
                window.draw(foodCell);
            }
        }

        for (int i = 0; i < 5; i++) {
            hurdleCell.setPosition(hurdle.getHurdlePosX(i) * cellSize, hurdle.getHurdlePosY(i) * cellSize);
            window.draw(hurdleCell);
        }

        window.display();
    }


}



void SnakeGame::stopGame() {
    std::cout << "Snake Game stopped." << std::endl;
}

void SnakeGame::run() {
    playGame();
}
