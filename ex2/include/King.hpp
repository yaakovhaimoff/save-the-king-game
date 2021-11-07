#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class King
{
public:
    
    King(Location);
    bool isKingValid();
    void moveKingInBoard(char);
    void setLocation(const Location &, int);
    Location getKingLocation(int);

private:
    Location m_KingLocation[3];

};
