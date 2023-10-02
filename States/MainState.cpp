#include "MainState.h"

MainState::MainState(sf::RenderWindow& window, std::stack<State *>& states) : State(window, states)
{
    gameID = -1;
    onePlayerPressed = false;
    std::string title = "Tic Tac Toe";
    float center = window.getSize().x/2.0f;
    gameTitle = new MyText(center,100.0f, title,*titleFont,60.0f,sf::Color::White);

    difficulty = new MyText(center, 400.0f,"Difficulty",*regularFont,25u,sf::Color::White);
    initButtons();
    initLogo();
}
MainState::~MainState(){
    delete gameTitle; delete difficulty;
    delete onePlayer; delete twoPlayers;
    delete easy; delete medium; delete hard;
    delete logoTexture; delete logoSprite;
}
void MainState::update(float& dt){
    sf::Vector2f mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x),
    static_cast<float>(sf::Mouse::getPosition(*window).y));
    //std::cout<<"Inside MainState : "<<gameID<<std::endl;
    
    onePlayer->update(dt,mousePosition);
    twoPlayers->update(dt,mousePosition);
    exit->update(dt,mousePosition);
    if(onePlayer->isButtonClicked()) onePlayerPressed = true; 
    else if(twoPlayers->isButtonClicked()) gameID = 1;
    else if(exit->isButtonClicked()) states->pop();
    
    if(onePlayerPressed){
        easy->update(dt,mousePosition);
        medium->update(dt,mousePosition);
        hard->update(dt,mousePosition);
        back->update(dt,mousePosition);

        if(easy->isButtonClicked()) gameID = 2;
        else if(medium->isButtonClicked()) gameID = 3;
        else if(hard->isButtonClicked()) gameID = 4;
        else if(back->isButtonClicked()) onePlayerPressed = false;
    }
    if(gameID != -1) {
        states->push(new GameState(*window,*states,gameID));
        onePlayerPressed = false;
    }
}

void MainState::render(sf::RenderTarget& target){
    target.draw(*background);
    gameTitle->render(target);
    target.draw(*logoSprite);

    onePlayer->render(target);
    twoPlayers->render(target);
    exit->render(target);
    if(onePlayerPressed){
        easy->render(target);
        medium->render(target);
        hard->render(target);
        back->render(target);
    }
    
    
}

void MainState::initButtons()
{
    float start = 500.0f;
    onePlayer = new Button(window->getSize().x/2.0f,start, 180.0f,50.0f,"One Player",*regularFont,25u,sf::Color::White);
    twoPlayers = new Button(window->getSize().x/2.0f,start+65.0f, 180.0f,50.0f,"Two Players",*regularFont,25u,sf::Color::White);
    exit = new Button(window->getSize().x/2.0f,start+130.0f, 180.0f,50.0f,"Exit",*regularFont,25u,sf::Color::White);
    easy = new Button(window->getSize().x/2.0f + 200.0f,start, 180.0f,50.0f,"Easy",*regularFont,25u,sf::Color::White);
    medium = new Button(window->getSize().x/2.0f+ 200.0f,start+60.0f, 180.0f,50.0f,"Medium",*regularFont,25u,sf::Color::White);
    hard = new Button(window->getSize().x/2.0f+ 200.0f,start+120.0f, 180.0f,50.0f,"Hard",*regularFont,25u,sf::Color::White);
    back = new Button(window->getSize().x/2.0f+ 200.0f,start+180.0f, 180.0f,50.0f,"Return",*regularFont,25u,sf::Color::White);
}

void MainState::initLogo()
{
    logoTexture = new sf::Texture();
    logoTexture->loadFromFile("images/logo.png");
    logoSprite = new sf::Sprite(*logoTexture);
    sf::FloatRect logoRec = logoSprite->getGlobalBounds();
    logoSprite->setOrigin(logoRec.left + logoRec.width/2.0f, logoRec.top + logoRec.height/2.0f);
    logoSprite->setPosition(window->getSize().x/2.0f, 300.0f);
    logoSprite->setScale(300.0f/(float)logoTexture->getSize().x,300.0f/(float)logoTexture->getSize().y);
}
