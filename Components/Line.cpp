#include "Line.h"

Line::Line(sf::Vector2f position, float rotation)
{
    width = 500.0f;
    this->position = position;
    this->position.x += 75.0f;
    this->position.y += 75.0f;
    line.setSize(sf::Vector2f(30.0f,width));
    sf::FloatRect lineRec = line.getGlobalBounds();
    line.setOrigin(lineRec.left + lineRec.width/2.0f, lineRec.top + lineRec.height/2.0f);
    line.setPosition(this->position);
    line.setFillColor(sf::Color(255,215,0));
    line.rotate(rotation);

    
}

Line::~Line(){}

void Line::update(float& dt){}
void Line::render(sf::RenderTarget& target){
    target.draw(line);
    
}

void Line::setWidth(float w, float fixRow, float fixColumn)
{
    width = w;
    line.setSize(sf::Vector2f(30.0f, width));
    line.setPosition(line.getPosition().x + fixRow, line.getPosition().y + fixColumn);
}
