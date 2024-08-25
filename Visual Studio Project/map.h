
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

void drawRambo(unsigned char map[][col], int& ramboX, int& ramboY);
void drawroad(unsigned char map[][col], int tankX, int tankY);

void initialize_map(unsigned char map[][col], int& ramboX, int& ramboY) {
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < col; j++)
        {

            if (i == 0 && j == 0)
            {
                map[i][j] = 201; //top-left
            }
            else if (i == 0 && j == col - 1)
            {
                map[i][j] = 187; //top-right
            }
            else if (i == rows - 1 && j == 0)
            {
                map[i][j] = 200;    //bottom-left
            }
            else if (i == rows - 1 && j == col - 1)
            {
                map[i][j] = 188; //bottom-right
            }
            else if (i == 0 || i == rows - 1)
            {
                map[i][j] = 205;    //horizontal
            }
            else if (j == 0 || j == col - 1)
            {
                map[i][j] = 186;  //vertical
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

void drawRambo(unsigned char map[][col], int& ramboX, int& ramboY) {
    ramboY = rows - 10;
    ramboX = col - (col / 2);
    map[ramboY][ramboX] = 'o';
    map[ramboY + 1][ramboX] = 219;
    map[ramboY + 2][ramboX] = 186;
}

void drawMap(unsigned char map[][col], int tankX = 0, int tankY = 0)
{
    string line;
    stringstream ss;
    for (size_t i = 0; i < rows; i++)
    {
        drawroad(map, tankX, tankY);
        for (size_t j = 0; j < col; j++)
        {
            if (i == rows - 1 && j !=0 && j != col-1) {
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
            else {
                map[i][21] = 180;
                map[r][30] = 195;
            }
        }
         
    }
}