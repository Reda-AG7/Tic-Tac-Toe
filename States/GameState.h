#ifndef __GAME_STATE__H
#define __GAME_STATE__H
#include "State.h"
#include "../Components/Button.h"
#include "../Components/Player.h"
#include "../Components/Cart.h"
#include "../Components/Line.h"
#include<chrono>

class GameState : public State{
    private:
        Button* back;
        int* gameID;
        Player* player1,*player2;
        Line* line;

        sf::SoundBuffer sBuffer;
        sf::Sound sound;
        sf::Text* winner;
        sf::Text* gameTime;

        std::string player1Name, player2Name;
        bool player1Turn;
        std::vector<Cart*> carts;
        int gameOver;
        std::chrono::steady_clock::time_point tStart,tEnd;
        unsigned seconds, minutes;
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
        void initWinner();
        void updateWinner();
        int checkState(const std::vector<Cart*>&) const;
        Cart* minimax();
        void initTime();
        void updateTime();
};

#endif