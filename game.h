#ifndef game_H
#define game_H

class Game {
public:
    virtual void playGame() = 0;
    virtual void stopGame() = 0;
    virtual ~Game() {}
};

#endif 

