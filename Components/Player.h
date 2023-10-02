#ifndef __PLAYER__H
#define __PLAYER__H
#include "SFML/Graphics.hpp"
#include "MyText.h"

class Player{
    private:
        sf::RectangleShape rec;
        sf::Texture playerTexture;
        sf::Sprite playerSprite;
        MyText* playerText;
        std::string playerName;

        float sideLength;
        
    public:
        Player(float, float, const std::string&, sf::Font&);
        ~Player();
        void update(float&, bool&);
        void render(sf::RenderTarget&);

};

#endif