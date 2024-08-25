/**
 * @file game.h
 *
 * This file contains the implementation of the Rambo Shooter game.
 *
 * It includes functions for displaying game results, playing the game, writing high scores, updating high scores, welcoming the player, and declaring the winner.
 *
 * The game is a 2D shooter where the player controls Rambo and must avoid obstacles, destroy crates and tanks, and survive for a certain amount of time.
 */
#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include "map.h"
#include "actions.h"
#include "elements.h"
#include "check.h"
#include "sound.h"
using namespace std;

/**
 * @brief Displays the results of the current level.
 *
 * This function clears the screen, sets the text color, and displays the level results.
 * It includes the player's score, lives, crates destroyed, and tanks destroyed.
 * If the player has died, it plays death music and displays a "YOU DIED!" message.
 * Otherwise, it plays victory music.
 *
 * Parameters
 * playerscore The player's current score.
 * lives The number of lives the player has.
 * level The current level.
 * crateCount The number of crates destroyed.
 * tankCount The number of tanks destroyed.
 */
void displayResults(int &playerscore, int &lives, int &level, int &crateCount, int &tankCount)
{
	system("cls");
	system("Color 0D");
	cout << setw(15) << "\nLEVEL " << level << " RESULTS" << endl;
	cout << setw(50) << setfill('_') << "" << endl;
	if (lives < 1)
	{
		deathMusic();
		cout << setw(25) << setfill('X') << "   YOU DIED!   "
			 << setw(10) << setfill('X') << "" << endl;
	}
	else
	{
		victoryMusic();
	}
	cout << left << setw(20) << setfill(' ') << "\n\nPlayer Score : " << setw(15) << playerscore << endl;
	cout << setw(20) << "Lives : " << setw(15) << lives << endl;
	cout << setw(20) << "Crates Destroyed : " << setw(15) << crateCount << endl;
	cout << setw(20) << "Tanks Destroyed : " << setw(15) << tankCount << endl;
	system("pause");
}

/**
 * @brief Plays the Rambo Shooter game.
 *
 * This function implements the game logic for the Rambo Shooter game.
 * It initializes the game map, sets up the player and obstacles, and starts the game loop.
 * The game loop updates the game state, checks for collisions, and updates the score.
 * The function ends when the player completes the level or runs out of lives.
 *
 * Parameters
 * playerscore: The player's current score.
 * level: The current level.
 * lives: The number of lives the player has.
 */
void play(int &playerscore, int &level, int &lives)
{
	int ramboX, ramboY, tankX = 0, tankY = 0, bulletX, bulletY, tBulletX, tBulletY;
	bool jumped = false, shot = false, tankDestroy = false, tShot = false;
	int crateCount = 0, tankCount = 0, time = 50;
	const int maxelems = 5;
	int obsSizes[maxelems] = {0}, obsX[maxelems] = {0}, obsY[maxelems] = {0}, crateX[maxelems] = {0}, crateY[maxelems] = {0};
	bool crateShot[maxelems] = {false}, tSpawn = false;
	openingMusic();

	system("Color 09");
	unsigned char map[rows][col];
	initialize_map(map, ramboX, ramboY);

	if (level == 2)
	{
		time = time / 1.5;
	}

	for (int step = 1; step <= 2500 && lives > 0; step++)
	{
		drawMap(map, tankX, tankY);
		cout << endl
			 << "Lives: " << lives << "\tPlayerscore: " << playerscore;
		speedRoad(time, ramboX, level);
		move(ramboX, ramboY, map, jumped, shot, bulletX, bulletY);

		if (shot)
		{
			bulletFlow(map, bulletX, bulletY, shot);
		}

		obsInterval(obsX, obsY, obsSizes, crateX, crateY, map, step);
		crateInterval(map, crateY, crateX, crateShot, step);

		if (step % 2 == 0)
		{
			obsFlow(map, obsSizes, obsX, obsY);
			crateFlow(map, crateX, crateY, crateShot);
		}

		if (level == 2)
		{
			if (step % 150 == 0)
			{
				tankSpawn(map, tankX, tankY, obsX, obsY, crateX, crateY);
				tSpawn = true;
			}
			if (tSpawn)
			{
				tankFlow(map, tankX, tankY, ramboX, ramboY, tankDestroy, tSpawn, tShot);
			}
		}
		else
		{
			if (step % 200 == 0)
			{
				tankSpawn(map, tankX, tankY, obsX, obsY, crateX, crateY);
				tSpawn = true;
			}
			if (step % 2 == 0 && tSpawn)
			{
				tankFlow(map, tankX, tankY, ramboX, ramboY, tankDestroy, tSpawn, tShot);
			}
		}

		if (tSpawn == true)
		{
			if (step % 11 == 0)
			{
				tankShoot(map, tBulletX, tBulletY, tankX, tankY, tShot, tankDestroy);
			}
			if (tShot)
			{
				tBulletFlow(map, tBulletX, tBulletY, tankY, tShot, lives, ramboX, ramboY);
			}
		}

		checkObs(map, obsSizes, obsX, obsY, ramboX, ramboY, lives, jumped);
		checkCrates(map, crateX, crateY, ramboX, ramboY, lives);
		crateHit(map, bulletX, bulletY, crateX, crateY, playerscore, crateCount, crateShot);

		checkCrateCount(crateCount, lives);

		tankHit(map, bulletX, bulletY, tankX, tankY, playerscore, tankCount, tankDestroy);
		tankCheck(map, ramboX, ramboY, tankX, tankY, lives, tankDestroy);

		system("cls");

		if (tankCount >= 10 || step == 2500)
		{
			level++;
			break;
		}
	}
	displayResults(playerscore, lives, level, crateCount, tankCount);
}
/*
Function Name: writeScores
Description:
This function writes the top 10 scores to a file named "Highscores.txt". The scores are stored in an integer array, scores, which is passed as a parameter to the function.

Parameters:
scores: An integer array containing the top 10 scores
Return: None
Notes:
This function opens a file named "Highscores.txt" in write mode and writes the top 10 scores to the file, one score per line. The scores are written in ascending order.
*/

void writeScores(int scores[])
{
	ofstream fout;
	fout.open("Highscores.txt", ios::out);

	for (int i = 0; i < 10; i++)
	{
		fout << scores[i] << endl;
	}

	fout.close();
}

/**

@brief Updates the high scores list.
This function reads the current high scores from a file, compares the player's score to the existing scores,
and updates the list if the player's score is higher. The updated list is then written back to the file.
Parameters
playerscore: The player's current score to be compared with the existing high scores. */
void updateHighscores(int playerscore)
{
	ifstream fin;
	ofstream fapp;
	int savedScore;
	fin.open("Highscores.txt");
	fapp.open("Highscores.txt", ios::app);
	int countContents = 0;

	int scores[10];

	if (fin.is_open())
	{
		while (fin.eof() == false)
		{
			// Count scores stored in file
			fin >> savedScore;
			countContents++;
		}

		fin.close();
		fin.open("Highscores.txt");

		if (countContents < 10)
		{
			// If scores < 10, no need for comparison
			fapp << endl
				 << playerscore;
		}
		else
		{
			// Move to start of file
			for (int i = 0; i < 10; i++)
			{
				// Read all the scores into an array & perform comparison
				fin >> scores[i];
				if (playerscore > scores[i])
				{
					scores[i] = playerscore;
				}
			}

			// Once array is updated, write it in the file
			writeScores(scores);
		}
	}

	fin.close();
	fapp.close();
}

void welcome(int &level)
{
	openingMusic();
	system("cls");
	system("Color 03");

	if (level == 1)
	{
		cout << setw(40) << setfill(' ') << "WELCOME TO RAMBO SHOOTER! " << endl
			 << endl;
	}
	else if (level == 2)
	{
		cout << setw(40) << setfill(' ') << "YOU MADE IT TO LEVEL 2! " << endl
			 << endl;
	}

	cout << setw(50) << setfill('*') << "" << endl
		 << endl;
	cout << setw(20) << setfill(' ') << ""
		 << "START LEVEL " << level << " ?" << endl;
	system("pause");
}

/*
Function: winner
Description: This function is used to display a victory message to the user when they have won the game "Rambo Shooter". It also displays the user's final score.
Parameters: playerscore: a reference to an integer that holds the player's final score.
Return Value: None*/
void winner(int &playerscore)
{
	victoryMusic();
	system("cls");
	system("Color 03");

	cout << setw(40) << setfill(' ') << "YOU HAVE WON RAMBO SHOOTER! YOU'RE AN ALIEN " << endl
		 << endl;
	cout << setw(50) << setfill('*') << "" << endl
		 << endl;
	cout << setw(20) << setfill(' ') << ""
		 << "YOUR FINAL SCORE : " << playerscore << endl;
	system("pause");
}