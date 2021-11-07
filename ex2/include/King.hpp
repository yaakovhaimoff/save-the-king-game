#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class King
{
public:
    
    King();
    bool isKingValid();
    void moveKingInBoard(char);
    void setLocation(const Location &);
    Location getKingLocation();

private:
    Location m_KingLocation;

};
