#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "Board.hpp"
#include "gamesTools.hpp"

class King
{
public:
    
    King();
    void setLocation(const Location &);
    Location getKingLocation();
    int isKingMoveValid(int);
    void kingNextStep(Board &, int, int, int&, int, int);
    void saveKingStep(Board &, int, int, int, int);

private:
    Location m_KingLocation;
    bool m_needToSaveKey;

};
