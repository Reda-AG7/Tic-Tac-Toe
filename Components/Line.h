#ifndef __LINE__H
#define __LINE__H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Line{
    private:
        sf::RectangleShape line;
        sf::Vector2f position;
        float width;
        sf::SoundBuffer sBuffer;
        sf::Sound sound;

    public:
        Line(sf::Vector2f, float);
        ~Line();
        void update(float&);
        void render(sf::RenderTarget&);
        void setWidth(float, float, float);
};


#endif