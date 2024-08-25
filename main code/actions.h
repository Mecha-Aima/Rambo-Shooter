#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "sound.h"
using namespace std;

/**
 * Handles the movement of Rambo.
 * @param ramboX X-coordinate of Rambo.
 * @param ramboY Y-coordinate of Rambo.
 * @param map The game map.
* @param jumped Has Rambo jumped?
 * @param shot Has Rambo shot?
 * @param bulletX X-coordinate of the bullet.
 * @param bulletY Y-coordinate of the bullet.
 */
void move(int &ramboX, int &ramboY, unsigned char map[][col], bool &jumped, bool &shot, int &bulletX, int &bulletY)
{
    if (_kbhit())
    {

        char ch = _getch();
        if (ch == ' ')
        {
            jumpMusic();
            jump(ramboX, ramboY, map);
            drawMap(map);
            Sleep(150);
            map[ramboY + 1][ramboX] = 219;
            jumped = true;
        }
        switch (ch)
        {
        case 'A':
        case 'a':
            // Rambo has reached far left
            if (ramboX > 1)
            {
                if (ramboX == 21)
                {
                    map[ramboY][ramboX] = 180;
                    map[ramboY + 1][ramboX] = 180;
                    map[ramboY + 2][ramboX] = 180;
                }
                else if (ramboX == 30)
                {
                    map[ramboY][ramboX] = 195;
                    map[ramboY + 1][ramboX] = 195;
                    map[ramboY + 2][ramboX] = 195;
                }
                else
                {
                    map[ramboY][ramboX] = ' ';
                    map[ramboY + 1][ramboX] = ' ';
                    map[ramboY + 2][ramboX] = ' ';
                }
                ramboX--;
            }
            break;

        case 'W':
        case 'w':
            // Rambo has reached the 15th row
            if (ramboY >= rows - 15)
            {
                map[ramboY][ramboX] = ' ';
                map[ramboY + 1][ramboX] = ' ';
                map[ramboY + 2][ramboX] = ' ';
                ramboY--;
            }
            break;

        case 'S':
        case 's':
            // Rambo has reached the bottom row. Y+2 accounts for his legs
            if (ramboY + 2 < rows - 2)
            {
                map[ramboY][ramboX] = ' ';
                map[ramboY + 1][ramboX] = ' ';
                map[ramboY + 2][ramboX] = ' ';
                ramboY++;
            }
            break;

        case 'D':
        case 'd':
            // Rambo has reached the far right
            if (ramboX < col - 2)
            {
                if (ramboX == 21)
                {
                    map[ramboY][ramboX] = 180;
                    map[ramboY + 1][ramboX] = 180;
                    map[ramboY + 2][ramboX] = 180;
                }
                else if (ramboX == 30)
                {
                    map[ramboY][ramboX] = 195;
                    map[ramboY + 1][ramboX] = 195;
                    map[ramboY + 2][ramboX] = 195;
                }
                else
                {
                    map[ramboY][ramboX] = ' ';
                    map[ramboY + 1][ramboX] = ' ';
                    map[ramboY + 2][ramboX] = ' ';
                }
                ramboX++;
            }
            break;
        case 'u':
        case 'U':
            ramboShootMusic();
            if(shot)
            {
                map[bulletY][bulletX] = ' ';
            }
            shoot(map, ramboX, ramboY, shot, bulletX, bulletY);
            break;
        }
    }
    if (map[ramboY + 1][ramboX] != 232)
    {
        map[ramboY][ramboX] = 'o';
        map[ramboY + 1][ramboX] = 219;
        map[ramboY + 2][ramboX] = 186;
    }
}

/**
 * Handles the jumping of Rambo.
 * @param ramboX X-coordinate of Rambo.
 * @param ramboY Y-coordinate of Rambo.
 * @param map The game map.
 */
void jump(int &ramboX, int &ramboY, unsigned char map[][col])
{
    map[ramboY + 2][ramboX] = ' ';
    if (ramboY > rows - 15)
    {
        --ramboY;
    }
    map[ramboY][ramboX] = 'o';
    map[ramboY + 1][ramboX] = 232;
    map[ramboY + 2][ramboX] = 186;
}

/**
 * Speeds up the game based on the level.
 * @param time The time to wait.
 * @param ramboX X-coordinate of Rambo.
 * @param level The current level.
 */
void speedRoad(int time, int &ramboX, const int level)
{
    if (ramboX < 21 || ramboX > 30)
        Sleep(time);
    else if (ramboX >= 21 && ramboX <= 30)
        Sleep(time / 2);
}

/**
 * Shoots a bullet.
 * @param map The game map.
 * @param ramboX X-coordinate of Rambo.
 * @param ramboY Y-coordinate of Rambo.
 * @param shot Has Rambo shot?
 * @param bulletX X-coordinate of the bullet.
 * @param bulletY Y-coordinate of the bullet.
 */
void shoot(unsigned char map[][col], int &ramboX, int &ramboY, bool &shot, int &bulletX, int &bulletY)
{
    if(shot)
    {
        map[bulletY][bulletX] = ' ';
    }
    bulletX = ramboX;
    bulletY = ramboY - 1;
    shot = true;
}

/**
 * Handles the movement of the bullet.
 * @param map The game map.
 * @param bulletX X-coordinate of the bullet.
 * @param bulletY Y-coordinate of the bullet.
 * @param shot Has Rambo shot?
 */
void bulletFlow(unsigned char map[][col], int &bulletX, int &bulletY, bool &shot)
{
    map[bulletY--][bulletX] = ' ';
    map[bulletY][bulletX] = 248;
    if (bulletY == 1)
    {
        shot = false;
        map[bulletY][bulletX] = ' ';
    }
}
