#pragma once
#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class Thief
{
public:
    
    Thief();
    bool isThiefMoveValid();
    void setLocation(const Location &);
    Location getThiefLocation();

private:
    Location m_ThiefLocation;

};
