#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "gamesTools.hpp"

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
