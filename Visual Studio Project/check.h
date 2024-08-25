	#pragma once
	#include <iostream>
	#include <windows.h>
	using namespace std;

	void checkObs(unsigned char map[][50], int obssize[], int obsX[], int obsY[], const int& ramboX, const int& ramboY, int& lives, bool& jumped)
	{
		static bool hit = false;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < obssize[i]; j++) {
				if (obsX[i] + j == ramboX && obsY[i] == ramboY && !jumped)
				{
					if (!hit) {
						lives--;
						hit = true;
					}
					else {
						hit = false;
					}
				}
			}
		}
		jumped = false;
	}

	void checkCrates(unsigned char map[][50], int crateX[], int crateY[], const int& ramboX, const int& ramboY, int& lives)
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


	void crateHit(unsigned char map[][50], int& bulletX, int& bulletY, int crateX[], int crateY[], int& playerscore, int &crateCount, bool crateshot[])
	{
		for(int i=0;i < 5;i++)
		{
			if (bulletY - 1 == crateY[i] && bulletX == crateX[i])
			{
				crateMusic();
				crateCount++;
				crateshot[i] = true;
				playerscore += 20;
				map[bulletY][bulletX]= ' ';
				map[crateY[i]][crateX[i]] = ' ';
				system("Color 06");
			
			}
		}
	}

	void checkCrateCount(int& crateCount, int& lives)
	{
		static bool inc = false;
		if (crateCount % 6 == 0 && crateCount != 0) {
			inc = false;
		}
		else if (crateCount % 5 == 0 && crateCount != 0 && inc == false) {
			lives++;
			inc = true;
		}
  
	}


	//To see if rambo's bullet hit the tank
	void tankHit(unsigned char map[][50], int& bulletX, int& bulletY, int& tankX, int& tankY, int& playerscore, int& tankCount, bool &tankshot)
	{
		static int tShot = 0;
		for (int i = 0; i < 4; i++) {
			if (bulletY-1 == tankY+3 && bulletX == tankX + i)
			{
				tShot++;
				map[bulletY][bulletX] = ' ';
			
			}
		}

		if (tShot >= 2) {
			tShot = 0;
			tankCount++;
			playerscore += 50;
			tankshot = true;
		}
	}

	// If Tank Hits Rambo
	void tankCheck(unsigned char map[][col],int& ramboX, int& ramboY, int& tankX,int& tankY,int& lives)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((ramboX == tankX + i && tankY + i == ramboY) || (ramboX == tankX + i && tankY + i == ramboY+1) || (ramboX == tankX + i && tankY + i == ramboY+2))
			{
				lives--;
			}
		}
	}