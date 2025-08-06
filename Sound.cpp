#include "Sound.h"
#include <iostream>
using namespace std;

Sound::Sound() {
    if(soundBuffer.loadFromFile("ss.wav")){
        StartingSound.setBuffer(soundBuffer);
        StartingSound.setLoop(true);
        StartingSound.play();
    }

    if(soundBuffer.loadFromFile("win.wav")){
        WinSound.setBuffer(soundBuffer);
        WinSound.setLoop(true);
        WinSound.play();
    }

    if(soundBuffer.loadFromFile("lose.wav")){
        LoseSound.setBuffer(soundBuffer);
        LoseSound.setLoop(true);
        LoseSound.play();
    }

    if(soundBuffer.loadFromFile("snakeEating.wav")){
        snakeEatingSound.setBuffer(soundBuffer);
        snakeEatingSound.setLoop(true);
        snakeEatingSound.play();
    }
    
}


void Sound :: PlaySound(sf::Sound &sound){
    sound.play();
}

void Sound :: StopSound(sf::Sound &sound){
    sound.stop();
}



