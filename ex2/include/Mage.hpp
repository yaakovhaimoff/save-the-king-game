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
    int isMageMoveValid(int);
    void setLocation(const Location &);
    Location getMageLocation();
    void mageNextStep(Board &, int, int, int&, int, int );
    void saveMageStep(Board &, int, int, int, int);

private:
    Location m_MageLocation;
    bool m_needToSaveKey;

};
