#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "gamesTools.hpp"

class Warrior
{
public:
    
    Warrior();
    bool isWarriorMoveValid();
    void setLocation(const Location &);
    Location getWarriorLocation();
    int isWarriorMoveValid(int nextStep);

private:
    Location m_WarriorLocation;

};
