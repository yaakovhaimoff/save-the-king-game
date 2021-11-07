#pragma once
#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class King
{
public:
    
    King();
    int isKingMoveValid(int);
    void setLocation(const Location &);
    Location getKingLocation();

private:
    Location m_KingLocation;

};
