
# Tic-Tac-Toe

In this Small project, I used SFML as a 2D renderer, along with C++ to make Tic Tac Toe Game.  
The game provides:  
-    **2 Players Mode:** where two players can play against each other.  
-    **1 Player Mode:** Where the user chooses the level of difficulty of the computer.  
     - Easy: The computer will select the position randomly.  
     - Medium: The computer will select the position by doing some searching for some specific cases otherwise will pick it randomly.  
     - Hard:  The computer uses the MiniMax Algorithm through which the computer will select the best position to either win or prevent the other player from winning.   

## Author

- [@Reda-AG7](https://www.github.com/Reda-AG7)


## Usage/Examples

```bash
reda@reda-XPS:~/TicTacToe$ g++ -std=c++20 Application.cpp Game.cpp States/*.cpp Components/*.cpp -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio  
reda@reda-XPS:~/TicTacToe$./a.out  
```


## GIF

![tictactoe2](https://github.com/Reda-AG7/CS388/assets/62580207/517ba2f4-d0a7-47f9-83e2-a6a7b4e0990a)
