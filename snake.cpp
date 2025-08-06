#include "snake.h"
#include <cstdlib>
#include <ctime>

// Snake class implementation
Snake::Snake() {
    snakePos[0][0] = 10;
    snakePos[0][1] = 10;
    snakePos[1][0] = 10;
    snakePos[1][1] = 11;
    snakePos[2][0] = 10;
    snakePos[2][1] = 12;
    snakePos[3][0] = 10;
    snakePos[3][1] = 13;
}

void Snake::moveSnake() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snakePos[i][0] = snakePos[i - 1][0];
        snakePos[i][1] = snakePos[i - 1][1];
    }
    snakePos[0][0] += snakeDirectionX;
    snakePos[0][1] += snakeDirectionY;
}

void Snake::changeDirection(int x, int y) {
    if (snakeDirectionX != -x || snakeDirectionY != -y) {  
        tempSnakeDirectionX = x;
        tempSnakeDirectionY = y;
    }
}

void Snake::updateDirection() {
    snakeDirectionX = tempSnakeDirectionX;
    snakeDirectionY = tempSnakeDirectionY;
}

void Snake::increaseLength() {
    snakeLength++;
}

int Snake::getSnakeLength() { return snakeLength; }

int Snake::getSnakePosX(int i) { return snakePos[i][0]; }

int Snake::getSnakePosY(int i) { return snakePos[i][1]; }

int Snake::getSnakeSpeed() { return snakeSpeed; }

int Snake::getSnakeDirectionX() { return snakeDirectionX; }

int Snake::getSnakeDirectionY() { return snakeDirectionY; }


// Food class implementation
Food::Food() {
    for (int i = 0; i < maxFoodonScreen; i++) {
        foodPos[i][0] = rand() % 20;
        foodPos[i][1] = rand() % 20;
        foodPos[i][2] = 1; 
    }
}

void Food::generateFood() {
    for (int i = 0; i < maxFoodonScreen; i++) {
        if (foodPos[i][2] == 0) {  
            foodPos[i][0] = rand() % 20;
            foodPos[i][1] = rand() % 20;
            foodPos[i][2] = 1;  
        }
    }
}

int Food::getFoodPosX(int i) { return foodPos[i][0]; }

int Food::getFoodPosY(int i) { return foodPos[i][1]; }

int Food::getFoodStatus(int i) { return foodPos[i][2]; }

void Food::setFoodStatus(int i, int status) { foodPos[i][2] = status; }


// Hurdle class implementation
Hurdle::Hurdle() {
    for (int i = 0; i < maxHurdles; i++) {
        hurdlePos[i][0] = rand() % 20;
        hurdlePos[i][1] = rand() % 20;
    }
}

void Hurdle::setHurdlePosX(int i, int x) { hurdlePos[i][0] = x; }
void Hurdle::setHurdlePosY(int i, int y) { hurdlePos[i][1] = y; }

int Hurdle::getHurdlePosX(int i) { return hurdlePos[i][0]; }

int Hurdle::getHurdlePosY(int i) { return hurdlePos[i][1]; }
