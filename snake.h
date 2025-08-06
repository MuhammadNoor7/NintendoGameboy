#ifndef Snake_H
#define Snake_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
using namespace std;

class Snake {
private:
    static const int maxSnakelength = 100;
    int snakePos[maxSnakelength][2];
    int snakeLength = 4;
    int snakeSpeed = 1;
    int snakeDirectionX = 0;
    int snakeDirectionY = -1;
    int tempSnakeDirectionX = 0;
    int tempSnakeDirectionY = -1;

public:
    Snake();
    void moveSnake();
    void changeDirection(int x, int y);
    void updateDirection();
    void increaseLength();
    int getSnakeLength();
    int getSnakePosX(int i);
    int getSnakePosY(int i);
    int getSnakeSpeed();
    int getSnakeDirectionX();
    int getSnakeDirectionY();
};

class Food {
private:
    static const int maxFoodonScreen = 5;
    int foodPos[maxFoodonScreen][3];

public:
    Food();
    void generateFood();
    int getFoodPosX(int i);
    int getFoodPosY(int i);
    int getFoodStatus(int i);
    void setFoodStatus(int i, int status);
};

class Hurdle {
private:
    static const int maxHurdles = 5;
    int hurdlePos[maxHurdles][2];

public:
    Hurdle();
    void setHurdlePosX(int i, int x);
    void setHurdlePosY(int i, int y);
    int getHurdlePosX(int i);
    int getHurdlePosY(int i);
};

#endif 
