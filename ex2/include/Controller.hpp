#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>

#include "Board.hpp"
#include "King.hpp"
#include "Player.hpp"

const char KING = 'K';
const char MAZE = 'M';
const char WARRIOR = 'W';
const char TILE = 'T';

enum Keys
{
    KB_Escape = 27,
    SpecialKey = 224,
};

enum SpecialKeys
{
    KB_Up = 72,
    KB_Down = 80,
    KB_Left = 75,
    KB_Right = 77,
};

class Controller
{
public:
    Controller();
    void findPlayersLocation(int);
    void runGame();
    
private:
    Board m_board;
    King m_King;
    Player m_Player;
    
};
