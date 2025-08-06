#ifndef Sound_H
#define Sound_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//this class will contain audio bufeer and will load all audios that will be inherited by other classes
class Sound {
    public:
        sf::SoundBuffer soundBuffer;
        sf::Sound snakeEatingSound,WinSound,LoseSound,StartingSound;
        Sound();
        void PlaySound(sf::Sound &sound);
        void StopSound(sf::Sound &sound); 

};





#endif