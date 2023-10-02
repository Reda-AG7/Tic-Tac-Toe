#ifndef __CART__H
#define __CART__H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Cart{
    private:
        float sideLength; 
        sf::RectangleShape rec;
        sf::Texture cartTexture;
        sf::Sprite cartSprite;
        bool isOccupied;
        char cartID;
        sf::SoundBuffer sBuffer;
        sf::Sound sound;

    public:
        Cart(float, float);
        ~Cart();
        void update(float&, sf::Vector2f&, bool&, int&);
        void render(sf::RenderTarget&);
        bool getIsOccupied() const;
        char getCartID() const;
        sf::Vector2f getCartPosition() const;
        void updateSelected(bool&);
        void setIsOccupied( bool, char);
};

#endif