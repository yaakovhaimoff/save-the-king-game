#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "Board.hpp"
#include "gamesTools.hpp"

class Warrior
{
public:
    
    Warrior();
    void setLocation(const Location &);
    Location getWarriorLocation();
    int isWarriorMoveValid(const int);
    void warriorNextStep(Board&, const int, const int, int&, int, int);
    void saveWarriorStep(Board&, const int, const int, const int, const int);
    void restartMembersToNextLevel();

private:
    Location m_WarriorLocation;
    bool m_needToSaveKey;

};
