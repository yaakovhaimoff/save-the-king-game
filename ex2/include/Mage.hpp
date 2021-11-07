#pragma once
#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class Mage
{
public:
    
    Mage();
    bool isMageMoveValid();
    void setLocation(const Location &);
    Location getMageLocation();

private:
    Location m_MageLocation;
};
