#include "Tile.hpp"

//___________________________________
Tile::Tile() : m_TileLocation(0,0)
{}
//_________________________________________________________
void Tile::setLocation(const Location &location)
{
    m_TileLocation = location;
}
//_______________________________________
Location Tile::getTileLocation()
{
    return m_TileLocation;
}
//________________________
bool Tile::isTileMoveValid()
{
   return true;
}

