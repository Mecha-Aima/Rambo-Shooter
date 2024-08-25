
#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

/**
 * @brief Checks if Rambo has collided with an obstacle.
 *
 * This function checks if Rambo's current position is the same as an obstacle's position.
 * If a collision is detected, Rambo's lives are decremented.
 *
 * @param map A 2D array representing the game map.
 * @param obssize An array containing the sizes of the obstacles.
 * @param obsX An array containing the x-coordinates of the obstacles.
 * @param obsY An array containing the y-coordinates of the obstacles.
 * @param ramboX Rambo's current x-coordinate.
 * @param ramboY Rambo's current y-coordinate.
 * @param lives Rambo's current number of lives.
 * @param jumped A boolean indicating whether Rambo is currently jumping.
 */
void checkObs(unsigned char map[][50], int obssize[], int obsX[], int obsY[], const int &ramboX, const int &ramboY, int &lives, bool &jumped)
{
	static bool hit = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < obssize[i]; j++)
		{
			if (obsX[i] + j == ramboX && obsY[i] == ramboY && !jumped)
			{
				if (!hit)
				{
					lives--;
					hit = true;
				}
				else
				{
					hit = false;
				}
			}
		}
	}
	jumped = false;
}

/**
 * @brief Checks if Rambo has collided with a crate.
 *
 * This function checks if Rambo's current position is the same as a crate's position.
 * If a collision is detected, Rambo's lives are decremented.
 *
 * @param map A 2D array representing the game map.
 * @param crateX An array containing the x-coordinates of the crates.
 * @param crateY An array containing the y-coordinates of the crates.
 * @param ramboX Rambo's current x-coordinate.
 * @param ramboY Rambo's current y-coordinate.
 * @param lives Rambo's current number of lives.
 */
void checkCrates(unsigned char map[][50], int crateX[], int crateY[], const int &ramboX, const int &ramboY, int &lives)
{
	for (int i = 0; i < 5; i++)
	{
		if (crateX[i] == ramboX && crateY[i] == ramboY)
		{
			lives--;
			break;
		}
	}
}


/**
 * @brief Checks if a bullet has hit a crate.
 *
 * This function checks if a bullet's current position is the same as a crate's position.
 * If a hit is detected, the crate is removed, and the player's score is incremented.
 *
 * @param map A 2D array representing the game map.
 * @param bulletX The bullet's current x-coordinate.
 * @param bulletY The bullet's current y-coordinate.
 * @param crateX An array containing the x-coordinates of the crates.
 * @param crateY An array containing the y-coordinates of the crates.
 * @param playerscore The player's current score.
 * @param crateCount The number of crates hit.
 * @param crateshot An array indicating which crates have been hit.
 */
void crateHit(unsigned char map[][50], int &bulletX, int &bulletY, int crateX[], int crateY[], int &playerscore, int &crateCount, bool crateshot[])
{
	for (int i = 0; i < 5; i++)
	{
		if (bulletY - 1 == crateY[i] && bulletX == crateX[i])
		{
			crateMusic();
			crateCount++;
			crateshot[i] = true;
			playerscore += 20;
			map[bulletY][bulletX] = ' ';
			map[crateY[i]][crateX[i]] = ' ';
			system("Color 06");
		}
	}
}

/**
 * @brief Checks if the number of crates hit has reached a certain threshold.
 *
 * This function increments Rambo's lives if the number of crates hit has reached a certain threshold.
 *
 * @param crateCount The number of crates hit.
 * @param lives Rambo's current number of lives.
 */
void checkCrateCount(int &crateCount, int &lives)
{
	static bool inc = false;
	if (crateCount % 6 == 0 && crateCount != 0)
	{
		inc = false;
	}
	else if (crateCount % 5 == 0 && crateCount != 0 && inc == false)
	{
		lives++;
		inc = true;
	}
}

/**
 * @brief Checks if a bullet has hit the tank.
 *
 * This function checks if a bullet's current position is the same as the tank's position.
 * If a hit is detected, the tank is removed, and the player's score is incremented.
 *
 * @param map A 2D array representing the game map.
 * @param bulletX The bullet's current x-coordinate.
 * @param bulletY The bullet's current y-coordinate.
 * @param tankX The tank's current x-coordinate.
 * @param tankY The tank's current y-coordinate.
 * @param playerscore The player's current score.
 * @param tankCount The number of tanks hit.
 * @param tankshot A boolean indicating whether the tank has been hit.
 */
void tankHit(unsigned char map[][50], int &bulletX, int &bulletY, int &tankX, int &tankY, int &playerscore, int &tankCount, bool &tankshot)
{
	static int tShot = 0;
	for (int i = 0; i < 4; i++)
	{
		if (bulletY - 1 == tankY + 3 && bulletX == tankX + i)
		{
			tShot++;
			map[bulletY][bulletX] = ' ';
		}
	}

	if (tShot >= 2)
	{
		tShot = 0;
		tankCount++;
		playerscore += 50;
		tankshot = true;
	}
}

/**
 * @brief Checks if the tank has hit Rambo.
 *
 * This function checks if the tank's current position is the same as Rambo's position.
 * If a hit is detected, Rambo's lives are decremented.
 *
 * @param map A 2D array representing the game map.
 * @param ramboX Rambo's current x-coordinate.
 * @param ramboY Rambo's current y-coordinate.
 * @param tankX The tank's current x-coordinate.
 * @param tankY The tank's current y-coordinate.
 * @param lives Rambo's current number of lives.
 * @param tankShot A boolean indicating whether the tank has been hit.
 * @param tSpawn A boolean indicating whether the tank has spawned.
 */
void tankCheck(unsigned char map[][col], int &ramboX, int &ramboY, int &tankX, int &tankY, int &lives, bool tankShot, bool tSpawn)
{
	if (!tankShot && tSpawn)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((ramboX == tankX + i && tankY + i == ramboY) || (ramboX == tankX + i && tankY + i == ramboY + 1) || (ramboX == tankX + i && tankY + i == ramboY + 2))
			{
				lives--;
			}
		}
	}
}

