#ifndef __GAME__H
#define __GAME__H

#include<iostream>
#include "States/MainState.h"

class Game{
    private:
        sf::RenderWindow* window;
        float dt;
        std::stack<State*> states;
        sf::Event* event;
        sf::Clock clock;
        sf::SoundBuffer* sBuffer;
        sf::Sound* sound;
        bool isPlayed;
        
    public:
        Game();
        ~Game();
        void updateEvents();
        void update();
        void render();
        void run();
        void updateDT();

};


#endif