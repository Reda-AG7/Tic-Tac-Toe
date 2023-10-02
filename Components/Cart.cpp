#include "Cart.h"
#include <random>
Cart::Cart(float pos_x, float pos_y)
{
    isOccupied = false;
    cartID = 'n';
    sideLength = 150.0f;
    rec.setFillColor(sf::Color(211, 211, 211));
    rec.setPosition(pos_x,pos_y);
    rec.setSize(sf::Vector2f(sideLength,sideLength));
    cartTexture.loadFromFile("images/players.png");
    cartSprite.setColor(sf::Color(211, 211, 211));
    cartSprite.setPosition(pos_x,pos_y);
    cartSprite.setScale(sideLength,sideLength);

    sBuffer.loadFromFile("Sounds/blip.wav");
    sound.setBuffer(sBuffer);
}

Cart::~Cart()
{
}

void Cart::update(float& dt, sf::Vector2f& mousePosition, bool& turn, int& gameID)
{
    if(turn) {
        if(!isOccupied && (rec.getGlobalBounds().contains(mousePosition) || cartSprite.getGlobalBounds().contains(mousePosition)) ){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                cartSprite.setTexture(cartTexture);
                cartSprite.setTextureRect(sf::IntRect(0,0,cartTexture.getSize().x/2.0f,cartTexture.getSize().y));
                turn = false;
                cartID = 'x';
                isOccupied = true;
                //cartSprite.setScale(sideLength*2/cartTexture.getSize().x, sideLength/cartTexture.getSize().y);
                sound.play();
            }
        }

    }
    else{
        if(gameID == 1){
            if(!isOccupied && (rec.getGlobalBounds().contains(mousePosition) || cartSprite.getGlobalBounds().contains(mousePosition)) ){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    cartSprite.setTexture(cartTexture);
                    cartSprite.setTextureRect(sf::IntRect(cartTexture.getSize().x/2.0f,0,cartTexture.getSize().x/2.0f,cartTexture.getSize().y));
                    turn = true;
                    cartID = 'o';
                    isOccupied = true;
                    sound.play();
                }
            }
        }
        else if(gameID == 2){
            //Easy Mode
            
        }
        else if(gameID == 3){}
        else if(gameID == 4){}
    }
    cartSprite.setScale(sideLength*2/cartTexture.getSize().x, sideLength/cartTexture.getSize().y);
}

void Cart::render(sf::RenderTarget& target) 
{
    target.draw(cartSprite);
    if(!isOccupied) target.draw(rec);
}

bool Cart::getIsOccupied() const
{
    return isOccupied;
}

char Cart::getCartID() const
{
    return cartID;
}

sf::Vector2f Cart::getCartPosition() const
{
    return rec.getPosition();
}

void Cart::updateSelected(bool& turn)
{
    cartSprite.setTexture(cartTexture);
    cartSprite.setTextureRect(sf::IntRect(cartTexture.getSize().x/2.0f,0,cartTexture.getSize().x/2.0f,cartTexture.getSize().y));
    turn = true;
    cartID = 'o';
    isOccupied = true;
}

void Cart::setIsOccupied( bool v, char player)
{
    isOccupied = v;
    cartID = player;
}
