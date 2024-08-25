#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void tankHorizontal(unsigned char map[][col], int &tankX, int &tankY, const int &ramboX, const int &ramboY);

/**
 * @brief Spawns an obstacle on the game map.
 *
 * This function generates a random position for an obstacle on the game map.
 * It ensures that the obstacle does not overlap with any crates or other obstacles.
 *
 * @param obsX The x-coordinate of the obstacle.
 * @param obsY The y-coordinate of the obstacle.
 * @param crateX An array of x-coordinates of crates.
 * @param crateY An array of y-coordinates of crates.
 * @param map A 2D array representing the game map.
 * @return The size of the obstacle.
 */
int obstacleSpawn(int &obsX, int &obsY, int crateX[], int crateY[], unsigned char map[][col])
{
	system("Color 08");
	srand(time(0));
	obsX = rand() % 33 + 5;
	obsY = rand() % 30 + 5;
	for (int i = 0; i < 5; i++)
	{
		if (obsX - crateX[i] < 8 || obsY - crateY[i] < 2)
		{
			obsX = rand() % 33 + 5;
			obsY = rand() % 20 + 5;
		}
	}

	int obsSize = rand() % 5 + 3;
	for (int i = 0; i < obsSize; i++)
	{
		if (i == 0 || i == obsSize - 1)
		{
			map[obsY][obsX + i] = '|';
		}
		else if (i > 0 && i < obsSize - 1)
		{
			map[obsY][obsX + i] = '-';
		}
	}
	return obsSize;
}

/**
 * @brief Updates the obstacle positions at regular intervals.
 *
 * This function checks if an obstacle has reached the bottom of the screen.
 * If so, it resets the obstacle's position and size.
 * It also spawns new obstacles at regular intervals.
 *
 * @param obsX An array of x-coordinates of obstacles.
 * @param obsY An array of y-coordinates of obstacles.
 * @param obsSizes An array of sizes of obstacles.
 * @param crateX An array of x-coordinates of crates.
 * @param crateY An array of y-coordinates of crates.
 * @param map A 2D array representing the game map.
 * @param step The current game step.
 */
void obsInterval(int obsX[], int obsY[], int obsSizes[], int crateX[], int crateY[], unsigned char map[][col], int step)
{
	for (int i = 0; i < 5; i++)
	{
		if (obsY[i] == rows - 2)
		{
			obsY[i] = 0;
			obsX[i] = 0;
			obsSizes[i] = 0;
		}
		if (step % 100 == 0)
		{
			obsSizes[i] = obstacleSpawn(obsX[i], obsY[i], crateX, crateY, map);
		}
	}
}

/**
 * @brief Spawns a crate on the game map.
 *
 * This function generates a random position for a crate on the game map.
 * It ensures that the crate does not overlap with any obstacles or other crates.
 *
 * @param map A 2D array representing the game map.
 * @param crateX An array of x-coordinates of crates.
 * @param crateY An array of y-coordinates of crates.
 */
void crateSpawn(unsigned char map[][col], int crateX[], int crateY[])
{

	for (int i = 0; i < 5; i++)
	{
		// Checks if there is already a crate
		if (crateX[i] == 0)
		{
			crateY[i] = rand() % 20 + 5;
			crateX[i] = rand() % 30 + 10;
			if (crateX[i] == 21 || crateX[i] == 30)
			{
				crateY[i] = rand() % 30 + 5;
				crateX[i] = rand() % 30 + 10;
			}
			map[crateY[i]][crateX[i]] = 177;
			break;
			// To spawn only a single crate
		}
	}
}

/**
 * @brief Updates the crate positions at regular intervals.
 *
 * This function checks if a crate has reached the bottom of the screen.
 * If so, it resets the crate's position.
 * It also spawns new crates at regular intervals.
 *
 * @param map A 2D array representing the game map.
 * @param crateY An array of y-coordinates of crates.
 * @param crateX An array of x-coordinates of crates.
 * @param crateshot An array indicating which crates have been hit.
 * @param step The current game step.
 */
void crateInterval(unsigned char map[][col], int crateY[], int crateX[], bool crateshot[], int step)
{
	for (int i = 0; i < 5; i++)
	{
		if (crateY[i] == rows - 2 || crateshot[i] == true)
		{
			map[crateY[i]][crateX[i]] = ' ';
			crateY[i] = 0;
			crateX[i] = 0;
			crateshot[i] = false;
		}
	}

	if (step % 100 == 0 && step != 0)
	{
		crateSpawn(map, crateX, crateY);
	}
}

/**
 * @brief Updates the obstacle positions.
 *
 * This function moves the obstacles downwards on the game map.
 *
 * @param map A 2D array representing the game map.
 * @param obsSize An array of sizes of obstacles.
 * @param obsX An array of x-coordinates of obstacles.
 * @param obsY An array of y-coordinates of obstacles.
 */
void obsFlow(unsigned char map[][col], int obsSize[], int obsX[], int obsY[])
{
	for (int i = 0; i < 5; i++)
	{
		if (obsY[i] == rows - 2)
			continue;
		for (int j = 0; j < obsSize[i]; j++)
		{

			if (obsX[i] + j != 21 && obsX[i] + j != 30)
				// Clear the obstacle from previous position
				map[obsY[i]][obsX[i] + j] = ' ';
			else if (obsX[i] + j == 21)
			{
				map[obsY[i]][obsX[i] + j] = 180;
			}
			else if (obsX[i] + j == 30)
			{
				map[obsY[i]][obsX[i] + j] = 195;
			}
		}
		obsY[i]++;
		for (int j = 0; j < obsSize[i]; j++)
		{
			if (obsY[i] == rows - 2)
				continue;
			if (j == 0 || j == obsSize[i] - 1)
			{
				map[obsY[i]][obsX[i] + j] = '|';
			}
			else if (j > 0 && j < obsSize[i] - 1)
			{
				map[obsY[i]][obsX[i] + j] = '-';
			}
		}
	}
}

/**
 * @brief Updates the crate positions.
 *
 * This function moves the crates downwards on the game map.
 *
 * @param map A 2D array representing the game map.
 * @param crateX An array of x-coordinates of crates.
 * @param crateY An array of y-coordinates of crates.
 * @param crateshot An array indicating which crates have been hit.
 */
void crateFlow(unsigned char map[][col], int crateX[], int crateY[], bool crateshot[])
{
	for (int i = 0; i < 5; i++)
	{
		if (crateX[i] != 0 && crateshot[i] == false)
		{
			map[crateY[i]++][crateX[i]] = ' ';
			map[crateY[i]][crateX[i]] = 177;
		}
	}
}

/**
 * @brief Spawns a tank on the game map.
 *
 * This function generates a random position for a tank on the game map.
 * It ensures that the tank does not overlap with any obstacles or crates.
 *
 * @param map A 2D array representing the game map.
 * @param tankX The x-coordinate of the tank.
 * @param tankY The y-coordinate of the tank.
 * @param obsX An array of x-coordinates of obstacles.
 * @param obsY An array of y-coordinates of obstacles.
 * @param crateX An array of x-coordinates of crates.
 * @param crateY An array of y-coordinates of crates.
 */
void tankSpawn(unsigned char map[][col], int &tankX, int &tankY, int obsX[], int obsY[], int crateX[], int crateY[])
{
	system("Color 0C");
	tankY = rand() % 20 + 5;
	tankX = rand() % 30 + 10;
	for (int i = 0; i < 5; i++)
	{
		while (tankX - crateX[i] <= 4 && tankY - crateY[i] <= 4 && tankX - obsX[i] <= 7 && tankY - obsY[i] <= 7)
		{
			tankY = rand() % 20 + 5;
			tankX = rand() % 30 + 10;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0)
			{
				map[tankY + i][tankX + j] = 223;
			}
			else if (i == 1)
			{
				if (j == 0)
				{
					map[tankY + i][tankX + j] = 221;
				}
				else if (j == 3)
				{
					map[tankY + i][tankX + j] = 222;
				}
				else
				{
					map[tankY + i][tankX + j] = 219;
				}
			}
			else if (i == 2)
			{
				if (j == 0 || j == 3)
					map[tankY + i][tankX + j] = 220;
				else
					map[tankY + i][tankX + j] = 219;
			}
			else
			{
				if (j == 0 || j == 3)
					map[tankY + i][tankX + j] = ' ';
				else
					map[tankY + i][tankX + j] = 186;
			}
		}
	}
}

/**
 * @brief Updates the tank's position on the game map.
 *
 * This function moves the tank downwards on the game map.
 * It also checks if the tank has reached the bottom of the screen.
 * If so, it resets the tank's position and spawns a new one.
 *
 * tankFlow updates the tank's horizontal position based on Rambo's position.
 * It then updates the tank's vertical position, moving it downwards on the map.
 * If the tank reaches the bottom of the screen, it is removed and a new one is spawned.
 * If the tank has been destroyed, it is removed from the map and a new one is spawned.
 *
 * Parameters:
 * map: A 2D array representing the game map.
 * tankX: The x-coordinate of the tank.
 * tankY: The y-coordinate of the tank.
 * ramboX: Rambo's current x-coordinate.
 * ramboY: Rambo's current y-coordinate.
 * tankdestroy: A boolean indicating whether the tank has been destroyed.
 * tSpawn: A boolean indicating whether the tank has spawned.
 * tShot: A boolean indicating whether the tank has been shot.
 */
void tankFlow(unsigned char map[][col], int &tankX, int &tankY, const int &ramboX, const int &ramboY, bool &tankdestroy, bool &tSpawn, bool &tShot)
{

	if (tankdestroy == false)
	{
		tankHorizontal(map, tankX, tankY, ramboX, ramboY);
		// Vertical flow
		if (tankY + 3 < rows - 2)
		{
			for (int j = 0; j < 4; j++)
			{
				if (tankX + j < col - 2 && tankX + j == 21)
				{
					map[tankY][tankX + j] = 180;
				}
				else if (tankX + j < col - 2 && tankX + j == 30)
				{
					map[tankY][tankX + j] = 195;
				}
				else if (tankX + j < col - 2)
				{
					map[tankY][tankX + j] = ' ';
				}
			}
			tankY++;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i == 0)
					{
						map[tankY + i][tankX + j] = 223;
					}
					else if (i == 1)
					{
						if (j == 0)
						{
							map[tankY + i][tankX + j] = 221;
						}
						else if (j == 3)
						{
							map[tankY + i][tankX + j] = 222;
						}
						else
						{
							map[tankY + i][tankX + j] = 219;
						}
					}
					else if (i == 2)
					{
						if (j == 0 || j == 3)
							map[tankY + i][tankX + j] = 220;
						else
							map[tankY + i][tankX + j] = 219;
					}
					else
					{
						if (j == 0 || j == 3)
							map[tankY + i][tankX + j] = ' ';
						else
							map[tankY + i][tankX + j] = 186;
					}
				}
			}
		}
		else
		{
			tSpawn = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (tankX + j < col - 2 && tankX + j == 21)
					{
						map[tankY + i][tankX + j] = 180;
					}
					else if (tankX + j < col - 2 && tankX + j == 30)
					{
						map[tankY + i][tankX + j] = 195;
					}
					else 
					{
						map[tankY + i][tankX + j] = ' ';
					}
				}
			}
			
		}
	}
	else //if (tankdestroy)
	{
		tShot = false;
		// Once tank shot, clear it
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (tankX + j == 21)
				{
					map[tankY + i][tankX + j] = 180;
				}
				else if (tankX + j == 30)
				{
					map[tankY + i][tankX + j] = 195;
				}
				else
				{
					map[tankY + i][tankX + j] = ' ';
				}
			}
		}
		tSpawn = false;
		tankdestroy = false;
	}
}

void tankHorizontal(unsigned char map[][col], int &tankX, int &tankY, const int &ramboX, const int &ramboY)
{
	if (tankX == 1)
	{ // Reached left border
		for (size_t i = 0; i < 4; i++)
		{
			if (tankY + i <= rows - 2)
			{
				map[tankY + i][tankX] = ' ';
			}
		}
		tankX++;
	}
	else if (tankX + 3 == col - 2)
	{ // Reached right border
		for (size_t i = 0; i < 4; i++)
		{
			if (tankY + i <= rows - 2)
			{
				map[tankY + i][tankX + 3] = ' ';
			}
		}
		tankX--;
	}
	else if (tankX < ramboX && tankX + 3 < col - 2)
	{ // Follow rambo towards right
		for (size_t i = 0; i < 4; i++)
		{
			if (tankY + i <= rows - 2)
			{
				map[tankY + i][tankX] = ' ';
			}
		}
		tankX++;
	}
	else
	{ // Follow rambo towards left
		for (size_t i = 0; i < 4; i++)
		{
			if (tankY + i <= rows - 2)
			{
				map[tankY + i][tankX + 3] = ' ';
			}
		}
		tankX--;
	}
	// Print out tank at new position
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0)
			{
				map[tankY + i][tankX + j] = 223;
			}
			else if (i == 1)
			{
				if (j == 0)
				{
					map[tankY + i][tankX + j] = 221;
				}
				else if (j == 3)
				{
					map[tankY + i][tankX + j] = 222;
				}
				else
				{
					map[tankY + i][tankX + j] = 219;
				}
			}
			else if (i == 2)
			{
				if (j == 0 || j == 3)
					map[tankY + i][tankX + j] = 220;
				else
					map[tankY + i][tankX + j] = 219;
			}
			else
			{
				if (j == 0 || j == 3)
					map[tankY + i][tankX + j] = ' ';
				else
					map[tankY + i][tankX + j] = 186;
			}
		}
	}
}

/**
 * @brief Handles the tank's shooting mechanism.
 *
 * This function is responsible for shooting a bullet from the tank.
 * It first checks if the tank has been destroyed, and if so, it resets the shooting state.
 * If the tank is not destroyed, it sets the shooting state to true and updates the bullet's position on the map.
 *
 * Parameters:
 * map: A 2D array representing the game map.
 * tbulletX: The x-coordinate of the tank's bullet.
 * tbulletY: The y-coordinate of the tank's bullet.
 * tankX: The x-coordinate of the tank.
 * tankY: The y-coordinate of the tank.
 * tshot: A boolean indicating whether the tank has shot.
 * tankDestroy: A boolean indicating whether the tank has been destroyed.
 */
void tankShoot(unsigned char map[][col], int &tbulletX, int &tbulletY, int tankX, int tankY, bool &tshot, bool &tankDestroy)
{
	tankShootMusic();
	if (tankDestroy)
	{
		tshot = false;
	}
	else
	{
		tshot = true;
		tbulletX = tankX + 1;
		tbulletY = tankY + 4;
		map[tbulletY][tbulletX] = 209;
		map[tbulletY][tbulletX + 1] = 209;
	}
}

/**
 * @brief Updates the tank's bullet position on the game map.
 *
 * This function is responsible for moving the tank's bullet downwards on the game map.
 * It checks for collisions with Rambo and updates the lives accordingly.
 * If the bullet reaches the bottom of the screen or has moved a certain distance, it is removed.
 *
 * Parameters:
 * map A 2D array representing the game map.
 * tbulletX The x-coordinate of the tank's bullet.
 * tbulletY The y-coordinate of the tank's bullet.
 * tankY The y-coordinate of the tank.
 * tshot A boolean indicating whether the tank has shot.
 * lives The number of lives Rambo has.
 * ramboX Rambo's current x-coordinate.
 * ramboY Rambo's current y-coordinate.
 */
void tBulletFlow(unsigned char map[][col], int &tbulletX, int &tbulletY, int &tankY, bool &tshot, int &lives, int ramboX, int ramboY)
{
	static int count = 0;
	if (tbulletY - tankY < 14 && tankY < rows - 15)
	{
		if (tbulletX == ramboX && tbulletY == ramboY - 1)
		{
			lives--;
		}
		map[tbulletY][tbulletX] = ' ';
		map[tbulletY++][tbulletX + 1] = ' ';

		map[tbulletY][tbulletX] = 209;
		map[tbulletY][tbulletX + 1] = 209;
		count++;
	}
	else
	{
		map[tbulletY][tbulletX] = ' ';
		map[tbulletY][tbulletX + 1] = ' ';
	}

	if (count >= 10)
	{
		count = 0;
		tshot = false;

		map[tbulletY][tbulletX] = ' ';
		map[tbulletY][tbulletX + 1] = ' ';
	}
}