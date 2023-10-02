#include "Game.h"

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(1000,800),"Tic Tac Toe");
    event = new sf::Event;

    //Initializing MainState
    states.push(new MainState(*window,states));

    sBuffer =  new sf::SoundBuffer();
    sound =  new sf::Sound();
    if(!sBuffer->loadFromFile("Sounds/entro.wav")) 
        throw "ERROR loading sound\n";
    sound->setBuffer(*sBuffer);
    sound->play();
    isPlayed = true;
}
Game::~Game(){
    delete window;
    delete event;
    while(!states.empty()){
        delete states.top();
        states.pop();
    }
}

void Game::updateEvents(){
    while(window->pollEvent(*event)){
        if(event->type == sf::Event::Closed){
            while(!states.empty()){
                delete states.top();
                states.pop();
            }
            window->close();
        }
    }
}
void Game::update(){
    updateDT();
    updateEvents();
    if(states.size() > 1) {
        sound->stop();
        isPlayed = false;
    }
    else if(states.size() == 1){
        if(!isPlayed){
            isPlayed = true;
            sound->play();
        }
    }
    if(!states.empty())
        states.top()->update(dt);
    else window->close();
}

void Game::render(){
    window->clear();
    if(!states.empty())
        states.top()->render(*window);
    window->display();
}

void Game::run(){
    while(window->isOpen()){
        update();
        render();
    }
}

void Game::updateDT()
{
    dt = clock.restart().asMilliseconds();
}
