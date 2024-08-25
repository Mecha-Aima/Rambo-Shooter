#include <iostream>
#include "game.h"


int main() {

    int lives = 1;
    int playerScore = 0;
    int level = 1;

    if(level==1)
    {
        welcome(level);
        play(playerScore, level, lives);
        updateHighscores(playerScore);
    }
  
  

    if (level == 2)
    {
        welcome(level);
        play(playerScore, level, lives);
        updateHighscores(playerScore);
    }

    if (level > 2)
    {
        winner(playerScore);
    }

    system("pause");
    return 0;
}