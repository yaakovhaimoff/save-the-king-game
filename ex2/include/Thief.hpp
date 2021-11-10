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
    int isThiefMoveValid(int);
    void thiefNextStep(Board&, int, int, int&, int, int);
    void saveThiefStep(Board&, int, int, int, int);

private:
    Location m_ThiefLocation;
    bool m_needToSaveKey;
    bool m_thiefKey;
    int m_amountOfKeys;
};
