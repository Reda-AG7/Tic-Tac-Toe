#include "GameState.h"

//Constructors
GameState::GameState(sf::RenderWindow& window, std::stack<State *>& states,int& gameID) : State(window, states)
{
    this->gameID = &gameID;
    player1Turn = true;
    gameOver = -1;
    seconds = minutes = 0u;
    initButtons();
    initPlayers();
    initCarts();

    sBuffer.loadFromFile("Sounds/winning.wav");
    sound.setBuffer(sBuffer);

    initWinner();
    initTime();
}

//Destructor
GameState::~GameState()
{
    delete player1;
    delete player2;
    delete background;
    delete winner;
    delete line; delete gameTime;
    for(auto c:carts) delete c;
}

//Updator
void GameState::update(float& dt)
{
    sf::Vector2f mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x),
    static_cast<float>(sf::Mouse::getPosition(*window).y));
    Cart* selected = nullptr;
    back->update(dt,mousePosition);
    updateTime();
    if(back->isButtonClicked()) {
        *gameID = -1;
        states->pop();
    }
    if(gameOver >= 0)
        updateWinner();
    if(gameOver == -1){
        if(!player1Turn && *gameID == 2) {
            selected = easyMode();
            selected->updateSelected(player1Turn);
        }
        else if(!player1Turn && *gameID == 3) {
            selected = easyMode();
            selected->updateSelected(player1Turn);
        }
        else if(!player1Turn && *gameID == 4) {
            selected = minimax();
            selected->updateSelected(player1Turn);
        }
        for(auto c: carts)
            c->update(dt, mousePosition, player1Turn, *gameID);
        checkGame();
        if(gameOver >=0) {
            player1Turn = player1Turn ? false : true;
            if(gameOver == 2 || gameOver == 0){
                sBuffer.loadFromFile("Sounds/failing.wav");
                sound.setBuffer(sBuffer);
            }
            sound.play();
        }
        player1->update(dt, player1Turn);
        player2->update(dt, player1Turn);
    }  
}

void GameState::updateWinner()
{
    if(gameOver == 0)
        winner->setString("Draw Game");
    else if(gameOver == 1)
        winner->setString(player1Name + "\n Won !!!");
    else if(gameOver == 2)
        winner->setString(player2Name + "\n Won !!!");
    
    if(winner->getPosition().y > 75.0f)
        winner->move(0.0f,-1.0f);
}

void GameState::updateTime()
{
    if(gameOver == -1)  tEnd = std::chrono::steady_clock::now();
    seconds = std::chrono::duration_cast<std::chrono::seconds>(tEnd-tStart).count();
    minutes = seconds/60u;
    seconds %= 60u;
    //std::cout<<minutes<<":"<<seconds<<std::endl;
    std::string strSec = seconds>9 ? std::to_string(seconds) : "0"+std::to_string(seconds);
    std::string strMin = minutes>9 ? std::to_string(minutes) : "0"+std::to_string(minutes);
    strMin+=(":"+strSec);
    gameTime->setString(strMin);
}

//Renderer
void GameState::render(sf::RenderTarget& target)
{
    target.draw(*background);
    back->render(target);
    target.draw(*gameTime);
    for(auto cart : carts) cart->render(target);
    if(gameOver > 0) 
        line->render(target);
    if(gameOver >= 0)
        target.draw(*winner);
    
    player1->render(target);
    player2->render(target);
}

//Initializers
void GameState::initButtons()
{
    back = new Button(100.0f,50.0f,150.0f,50.0f,"Back", *regularFont, 20u, sf::Color::White);
}

void GameState::initPlayers()
{
    player1Name = "You";
    if(*gameID == 1) {
        player2Name = "Player 2";
        player1Name = "Player 1";
    }
    else if(*gameID == 2 || *gameID == 3) player2Name = "Computer";
    else if(*gameID == 4) player2Name = "AI";
    player1 = new Player(30.0f, 180.0f, player1Name, *titleFont);
    player2 = new Player(window->getSize().x-180.0f,180.0f,player2Name,*titleFont);
}

void GameState::initCarts()
{
    float startTop = 0.0f;
    float sideLength = 150.0f;
    float startLeft = window->getSize().x/2.0f - sideLength*1.5 - 20.0f;
    int k = 0,j=0;
    carts.resize(9);
    for(int i=0;i<9;i++){
        if(i%3 == 0) {k=0;j++;}
        carts[i] = new Cart(startLeft + (k++)*(sideLength + 20.0f), startTop + j*(sideLength+20.0f));
    }
}

void GameState::initWinner()
{
    winner = new sf::Text();
    winner->setString("Winner is\n");
    winner->setCharacterSize(60u);
    winner->setFillColor(sf::Color::Red);
    winner->setFont(*titleFont);
    sf::FloatRect winnerRec = winner->getGlobalBounds();
    winner->setOrigin(winnerRec.left + winnerRec.width/2.0f, winnerRec.top + winnerRec.height/2.0f);
    winner->setPosition(window->getSize().x/2.0f, window->getSize().y);
}

void GameState::initTime()
{
    tStart = tEnd = std::chrono::steady_clock::now();
    gameTime = new sf::Text();
    gameTime->setString("00:00");
    gameTime->setFont(*regularFont);
    gameTime->setFillColor(sf::Color::Yellow);
    sf::FloatRect timeRec = gameTime->getGlobalBounds();
    gameTime->setOrigin(timeRec.left + timeRec.width/2.0f, timeRec.top + timeRec.height/2.0f);
    gameTime->setPosition(window->getSize().x-timeRec.width, 50.0f);
}

//Helper Functions
void GameState::checkGame()
{
    float center = window->getSize().x/2.0f;
    float fixAmount = 35.71f;
    //horizontally
    if(gameOver == -1){
        for(int i=0;i<9;i+=3){
            if(carts[i]->getCartID() == 'x' && carts[i+1]->getCartID() == 'x' && carts[i+2]->getCartID() == 'x'){
                std::cout<<player1Name<<" Won!!\n";
                line = new Line(carts[i+1]->getCartPosition(), 90.0f);
                gameOver = 1;
            }
            else if(carts[i]->getCartID() == 'o' && carts[i+1]->getCartID() == 'o' && carts[i+2]->getCartID() == 'o'){
                std::cout<<player2Name<<" Won!!\n";
                line = new Line(carts[i+1]->getCartPosition(), 90.0f);
                gameOver = 2;
            }
        }
    }
    
    //Vertically
    if(gameOver == -1){
        for(int i=0;i<3;i++){
            if(carts[i]->getCartID() == 'x' && carts[i+3]->getCartID() == 'x' && carts[i+6]->getCartID() == 'x'){
                std::cout<<player1Name<<" Won!!\n";
                std::cout<<carts[i+3]->getCartPosition().x<<", "<<carts[i+3]->getCartPosition().y<<std::endl;
                line = new Line(carts[i+3]->getCartPosition(), 0.0f);
                gameOver = 1;
            }
            else if(carts[i]->getCartID() == 'o' && carts[i+3]->getCartID() == 'o' && carts[i+6]->getCartID() == 'o'){
                std::cout<<player2Name<<" Won!!\n";
                line = new Line(carts[i+3]->getCartPosition(), 0.0f);
                gameOver = 2;
            }
        }
    }
    if(gameOver == -1){
        if(carts[0]->getCartID() == 'x' && carts[4]->getCartID() == 'x' && carts[8]->getCartID() == 'x'){
            std::cout<<player1Name<<" Won!!\n";
            line = new Line(carts[4]->getCartPosition(), -45.0f);
            line->setWidth(600.0f, -fixAmount, -fixAmount);
            gameOver = 1;
        }
        else if(carts[0]->getCartID() == 'o' && carts[4]->getCartID() == 'o' && carts[8]->getCartID() == 'o'){
            std::cout<<player2Name<<" Won!!\n";
            line = new Line(carts[4]->getCartPosition(), -45.0f);
            line->setWidth(600.0f, -fixAmount, -fixAmount);
            gameOver = 2;
        }
    }
    //Diagonally
    if(gameOver == -1){
        if(carts[2]->getCartID() == 'x' && carts[4]->getCartID() == 'x' && carts[6]->getCartID() == 'x'){
            std::cout<<player1Name<<" Won!!\n";
            line = new Line(carts[4]->getCartPosition(), 45.0f);
            line->setWidth(600.0f, fixAmount, -fixAmount);
            gameOver = 1;
        }
        else if(carts[2]->getCartID() == 'o' && carts[4]->getCartID() == 'o' && carts[6]->getCartID() == 'o'){
            std::cout<<player2Name<<" Won!!\n";
            line = new Line(carts[4]->getCartPosition(), 45.0f);
            line->setWidth(600.0f, fixAmount, -fixAmount);
            gameOver = 2;
        }
    }
    
    //if draw
    bool result = std::all_of(carts.begin(), carts.end(),[](Cart* c){ return c->getIsOccupied();});
    if(result) {
        std::cout<<"Draw"<<std::endl;
        gameOver = 0;
    }
}

Cart *GameState::easyMode() const
{
    std::vector<int> availableSpots;
    for(int i=0;i< carts.size();i++){
        if(!(carts[i]->getIsOccupied())) 
            availableSpots.push_back(i);
    }
    return carts[availableSpots[random()%availableSpots.size()]];
}

std::pair<int,int> search(const std::vector<std::pair<int,int>>& score, bool x){
    int temp = x ? 0x7fffffff : 0x80000000;
    int index = -1;
    for(int j=0;j<score.size();j++){
        if(x){
            if(score[j].first<temp) {
                temp = score[j].first; 
                index = j;
            }
        }
        else{
            if(score[j].first>temp) {
                temp = score[j].first; 
                index = j;
            }
        }
    }
    return score[index];
}

std::pair<int,int> GameState::miniMax(std::vector<Cart*>& newCarts, bool turn)
{
    int a = checkState(newCarts);
    if(a >= -1) return std::make_pair(a,-2);

    if(turn){
        std::vector<std::pair<int,int>> score;
        for(int i=0;i<newCarts.size();i++){
            if(!newCarts[i]->getIsOccupied()){
                newCarts[i]->setIsOccupied(true, 'x');
                std::pair<int,int> x = miniMax(newCarts, false);
                x.second = i;
                score.push_back(x);
                newCarts[i]->setIsOccupied(false,'n');
            }
        }
        return search(score, true);
    }
    else{
        std::vector<std::pair<int,int>> score;
        for(int i=0;i<newCarts.size();i++){
            if(!newCarts[i]->getIsOccupied()){
                newCarts[i]->setIsOccupied(true, 'o');
                std::pair<int,int> x = miniMax(newCarts, true);
                x.second = i;
                score.push_back(x);
                newCarts[i]->setIsOccupied(false,'n');
            }
        }
        return search(score, false);
    }
}

Cart* GameState::minimax()
{
    std::pair<int,int> result = miniMax(carts,false);
    player1Turn = true;
    return carts[result.second];
}



int GameState::checkState(const std::vector<Cart*>& carts) const
{
    //horizontally
    if(gameOver == -1){
        for(int i=0;i<9;i+=3){
            if(carts[i]->getCartID() == 'x' && carts[i+1]->getCartID() == 'x' && carts[i+2]->getCartID() == 'x') return -1;
            else if(carts[i]->getCartID() == 'o' && carts[i+1]->getCartID() == 'o' && carts[i+2]->getCartID() == 'o') return 1;
        }
    }
    
    //Vertically
    if(gameOver == -1){
        for(int i=0;i<3;i++){
            if(carts[i]->getCartID() == 'x' && carts[i+3]->getCartID() == 'x' && carts[i+6]->getCartID() == 'x') return -1; 
            else if(carts[i]->getCartID() == 'o' && carts[i+3]->getCartID() == 'o' && carts[i+6]->getCartID() == 'o') return 1;
        }
    }
    if(gameOver == -1){
        if(carts[0]->getCartID() == 'x' && carts[4]->getCartID() == 'x' && carts[8]->getCartID() == 'x') return -1;    
        else if(carts[0]->getCartID() == 'o' && carts[4]->getCartID() == 'o' && carts[8]->getCartID() == 'o') return 1;
    }
    //Diagonally
    if(gameOver == -1){
        if(carts[2]->getCartID() == 'x' && carts[4]->getCartID() == 'x' && carts[6]->getCartID() == 'x') return -1;
        else if(carts[2]->getCartID() == 'o' && carts[4]->getCartID() == 'o' && carts[6]->getCartID() == 'o') return 1;
    }
    //if draw
    bool result = std::all_of(carts.begin(), carts.end(),[](Cart* c){ return c->getIsOccupied();});
    if(result) return 0;
    else return -2;
}