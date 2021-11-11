#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "Board.hpp"
#include "gamesTools.hpp"

class Thief
{
public:
    
    Thief();
    void setLocation(const Location &);
    Location getThiefLocation();
    int isThiefMoveValid(const int);
    void thiefNextStep(Board&, const int, const int, int&, int, int);
    void saveThiefStep(Board&, const int, const int, const int, const int);
    bool checkIfTheThiefHasAkey();
    void restartMembersToNextLevel();

private:
    Location m_ThiefLocation;
    bool m_needToSaveKey;
    int m_amountOfKeys;
};
