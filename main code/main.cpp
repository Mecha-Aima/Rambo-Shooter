/**
 * @file main.cpp
 * @brief The main entry point of the game.
 *
 * This file contains the main function that initializes the game and controls the flow of the game.
 * It includes the necessary functions to welcome the player, play the game, update high scores, and declare the winner.
 *
 */
#include <iostream>
#include "game.h"

int main()
{

    int lives = 1;
    int playerScore = 0;
    int level = 1;

    if (level == 1)
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