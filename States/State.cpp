#include "State.h"

State::State(sf::RenderWindow& window, std::stack<State*>& states)
{
    this->window = &window;
    this->states = &states;
    this->background = new sf::RectangleShape(sf::Vector2f(window.getSize().x,window.getSize().x));
    this->background->setFillColor(sf::Color(28, 40, 65));

    //Fonts
    titleFont = new sf::Font();
    titleFont->loadFromFile("Fonts/Roboto-BoldItalic.ttf");

    regularFont = new sf::Font();
    regularFont->loadFromFile("Fonts/Roboto-Regular.ttf");

}

State::~State(){
    delete background;
    delete regularFont;
    delete titleFont;
}