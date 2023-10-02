#ifndef __MAIN_STATE__
#define __MAIN_STATE__
#include "GameState.h"
#include "../Components/Button.h"

class MainState : public State{
    private:
        int gameID;
        MyText* gameTitle;
        Button* onePlayer,*twoPlayers,*easy,*medium,*hard,*exit,*back;
        MyText* difficulty;

        sf::Sprite* logoSprite;
        sf::Texture* logoTexture;
        bool onePlayerPressed;
        
    public:
        MainState(sf::RenderWindow&, std::stack<State*>&);
        ~MainState();
        void update(float&);
        void render(sf::RenderTarget&);
        void initButtons();
        void initLogo();
};

#endif