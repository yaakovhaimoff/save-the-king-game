#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "Location.hpp"
#include "gamesTools.hpp"

class Mage
{
public:
    
    Mage();
    int isMageMoveValid(int nextStep);
    void setLocation(const Location &);
    Location getMageLocation();

private:
    Location m_MageLocation;
};
