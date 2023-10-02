#include "Player.h"

Player::Player(float pos_x, float pos_y, const std::string& playerID, sf::Font& font)
{
    sideLength = 100.0f;
    playerName = playerID;

    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineThickness(3u);
    rec.setSize(sf::Vector2f(150.0f,150.0f));
    rec.setPosition(pos_x,pos_y);
    rec.setOutlineColor(sf::Color::Transparent);

    
    playerText = new MyText(rec.getGlobalBounds().left+rec.getGlobalBounds().width/2.0f,rec.getGlobalBounds().top+20,playerID,font,25u, sf::Color::White);

    playerTexture.loadFromFile("images/players.png");
    playerSprite.setTexture(playerTexture);
    if(playerID == "Player 1" || playerID == "You")
        playerSprite.setTextureRect(sf::IntRect(0,0,playerTexture.getSize().x/2.0f,playerTexture.getSize().y));
    else playerSprite.setTextureRect(sf::IntRect(playerTexture.getSize().x/2.0f,0,playerTexture.getSize().x/2.0f,playerTexture.getSize().y));

    playerSprite.setScale(sideLength/(float)playerTexture.getSize().x*2,sideLength/(float)playerTexture.getSize().y);
    playerSprite.setPosition(rec.getGlobalBounds().left + rec.getGlobalBounds().width/2.0f - sideLength/2.0f,rec.getGlobalBounds().top+40.0f);
    
        
}

Player::~Player(){
    delete playerText;
}

void Player::update(float& dt, bool& turn){
    if((turn && (playerName == "Player 1" || playerName == "You")) ||
        (!turn && (playerName == "Player 2" || playerName == "Computer" || playerName == "AI")))
        rec.setOutlineColor(sf::Color::Yellow);
    else rec.setOutlineColor(sf::Color::Transparent);
}

void Player::render(sf::RenderTarget& target){
    target.draw(rec);
    playerText->render(target);
    target.draw(playerSprite);
}