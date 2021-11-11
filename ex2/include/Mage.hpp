#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "Board.hpp"
#include "gamesTools.hpp"

class Mage
{
public:
    
    Mage();
    int isMageMoveValid(const int);
    void setLocation(const Location &);
    Location getMageLocation();
    void mageNextStep(Board &, const int, const int, int&, int, int );
    void saveMageStep(Board &, const int, const int, const int, const int);
    void restartMembersToNextLevel();

private:
    Location m_MageLocation;
    bool m_needToSaveKey;
    bool m_teleport;

};
