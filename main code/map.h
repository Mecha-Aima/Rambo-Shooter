/**
 * @file map.h
 * @brief The game logic and rendering functions.
 *
 * This file contains the functions responsible for initializing the game map, drawing the game elements (Rambo, roads, and tanks), and rendering the game map.
 *
 */
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

extern const int rows = 50;
extern const int col = 50;

void drawRambo(unsigned char map[][col], int &ramboX, int &ramboY);
void drawroad(unsigned char map[][col], int tankX, int tankY);

/**
 * @brief Initializes the game map with borders and roads.
 *
 * This function initializes the game map by setting up the borders and roads.
 * It also calls the drawRambo function to place Rambo on the map.
 *
 * @param map The 2D array representing the game map.
 * @param ramboX The x-coordinate of Rambo's position.
 * @param ramboY The y-coordinate of Rambo's position.
 */
void initialize_map(unsigned char map[][col], int &ramboX, int &ramboY)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < col; j++)
        {

            if (i == 0 && j == 0)
            {
                map[i][j] = 201; // top-left
            }
            else if (i == 0 && j == col - 1)
            {
                map[i][j] = 187; // top-right
            }
            else if (i == rows - 1 && j == 0)
            {
                map[i][j] = 200; // bottom-left
            }
            else if (i == rows - 1 && j == col - 1)
            {
                map[i][j] = 188; // bottom-right
            }
            else if (i == 0 || i == rows - 1)
            {
                map[i][j] = 205; // horizontal
            }
            else if (j == 0 || j == col - 1)
            {
                map[i][j] = 186; // vertical
            }
            else if (j == 21)
            {
                map[i][j] = 180;
            }
            else if (j == 30)
            {
                map[i][j] = 195;
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
    drawRambo(map, ramboX, ramboY);
}

/**
 * @brief Draws Rambo on the game map.
 *
 * This function draws Rambo on the game map by setting the corresponding characters in the map array.
 *
 * @param map The 2D array representing the game map.
 * @param ramboX The x-coordinate of Rambo's position.
 * @param ramboY The y-coordinate of Rambo's position.
 */
void drawRambo(unsigned char map[][col], int &ramboX, int &ramboY)
{
    ramboY = rows - 10;
    ramboX = col - (col / 2);
    map[ramboY][ramboX] = 'o';
    map[ramboY + 1][ramboX] = 219;
    map[ramboY + 2][ramboX] = 186;
}

/**
 * @brief Draws the game map, including roads and tanks.
 *
 * This function draws the game map by iterating over the map array and printing the characters.
 * It also calls the drawroad function to draw the roads.
 *
 * @param map The 2D array representing the game map.
 * @param tankX The x-coordinate of the tank's position.
 * @param tankY The y-coordinate of the tank's position.
 */
void drawMap(unsigned char map[][col], int tankX = 0, int tankY = 0)
{
    string line;
    stringstream ss;
    for (size_t i = 0; i < rows; i++)
    {
        drawroad(map, tankX, tankY);
        for (size_t j = 0; j < col; j++)
        {
            if (i == rows - 1 && j != 0 && j != col - 1)
            {
                ss << static_cast<char>(205);
                continue;
            }
            ss << map[i][j];
        }
        ss << "\n";
    }
    line = ss.str();
    cout << line;
}

/**
 * @brief Draws the roads on the game map.
 *
 * This function draws the roads on the game map by setting the corresponding characters in the map array.
 * It iterates over the map array and sets the characters for the roads.
 *
 * @param map The 2D array representing the game map.
 * @param tankX The x-coordinate of the tank's position.
 * @param tankY The y-coordinate of the tank's position.
 */
void drawroad(unsigned char map[][col], int tankX, int tankY)
{
    for (int i = 1, r = 1; i < rows - 1 && r < rows - 1; i++, r++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tankX + j == 21)
            {
                i = i + 3;
                map[i][21] = 180;
                map[r][30] = 195;
            }
            else if (tankX >= 21 && tankX <= 30 && tankX + j == 30)
            {
                r += 3;
                map[i][21] = 180;
                map[r][30] = 195;
            }
            else
            {
                map[i][21] = 180;
                map[r][30] = 195;
            }
        }
    }
}