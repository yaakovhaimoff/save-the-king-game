#pragma once
#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class Warrior
{
public:
    
    Warrior();
    bool isWarriorMoveValid();
    void setLocation(const Location &);
    Location getWarriorLocation();

private:
    Location m_WarriorLocation;

};
