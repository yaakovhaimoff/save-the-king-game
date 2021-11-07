#pragma once
#include <stdio.h>
#include "Location.hpp"
#include <iostream>
#include <cstdlib>

class Tile
{
public:
    
    Tile();
    bool isTileMoveValid();
    void setLocation(const Location &);
    Location getTileLocation();

private:
    Location m_TileLocation;

};
