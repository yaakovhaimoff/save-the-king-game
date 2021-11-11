#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Location.hpp"
#include "Board.hpp"
#include "gamesTools.hpp"

class King
{
public:
    
    King();
    void setLocation(const Location &);
    Location getKingLocation();
    int isKingMoveValid(const int);
    void kingNextStep(Board &, const int, const int, int&, int, int);
    void saveKingStep(Board &, const int, const int, const int, const int);
    void restartMembersToNextLevel();

private:
    Location m_KingLocation;
    bool m_needToSaveKey;
};
