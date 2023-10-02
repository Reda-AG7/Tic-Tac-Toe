#ifndef __GAME_STATE__H
#define __GAME_STATE__H
#include "State.h"
#include "../Components/Button.h"
#include "../Components/Player.h"
#include "../Components/Cart.h"
#include "../Components/Line.h"

class GameState : public State{
    private:
        Button* back,*quit;
        int* gameID;
        Player* player1,*player2;
        std::string player1Name, player2Name;
        bool player1Turn;
        std::vector<Cart*> carts;
        Line* line;
        int gameOver;

        sf::SoundBuffer sBuffer;
        sf::Sound sound;

        sf::Sprite* gameOverSprite;
        sf::Texture* gameOverTexture;
        //private method
    private: 
        std::pair<int,int> miniMax(std::vector<Cart*>&, bool);
    public:
        GameState(sf::RenderWindow&, std::stack<State*>&,int&);
        ~GameState();
        void update(float&);
        void render(sf::RenderTarget&);
        void initButtons();
        void initPlayers();
        void initCarts();
        void checkGame();
        Cart* easyMode() const;
        
        void initGameOverSprite();
        void updateGameOverSprite();
        int checkState(const std::vector<Cart*>&) const;
        Cart* minimax();
       

};

#endif