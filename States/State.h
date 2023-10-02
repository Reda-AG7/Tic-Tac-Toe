#ifndef __STATE__H
#define __STATE__H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<iostream>
#include<stack>

class State{
    protected:
        sf::RectangleShape* background;
        sf::RenderWindow* window;
        std::stack<State*>* states; //can't this be static and inline
        float dt;
        sf::Font* regularFont,* titleFont;
    public:
        State(sf::RenderWindow&, std::stack<State*>&);
        virtual ~State();
        virtual void update(float&) = 0;
        virtual void render(sf::RenderTarget&) = 0;
};


#endif