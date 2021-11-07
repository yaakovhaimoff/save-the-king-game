#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class King
{
public:
    
    King();
    bool isKingMoveValid();
    void setLocation(const Location &);
    Location getKingLocation();

private:
    Location m_KingLocation;

};
