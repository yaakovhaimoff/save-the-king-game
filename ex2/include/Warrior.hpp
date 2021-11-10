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
    int isWarriorMoveValid(int);
    void warriorNextStep(Board&, int, int, int&, int, int);
    void saveWarriorStep(Board&, int, int, int, int);

private:
    Location m_WarriorLocation;
    bool m_needToSaveKey;

};
