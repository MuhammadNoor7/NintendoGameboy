#ifndef SnakeGame_H
#define SnakeGame_H

#include "game.h"
#include "snake.h"
#include <SFML/Graphics.hpp>

class SnakeGame : public Game, public Snake {
private:
    Food food;
    Hurdle hurdle;

public:
    void playGame() override;
    void stopGame() override;
    void run(); 
};

#endif
