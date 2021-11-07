#include "King.hpp"

//___________________________________
King::King(Location location) 
    : m_KingLocation[0](0,0),
m_KingLocation[1](0, 0), m_KingLocation[2](0, 0)
{}
//_________________________________________________________
void King::setLocation(const Location &location, int index)
{
    m_KingLocation[index] = location;
}
//_______________________________________
Location King::getKingLocation(int index)
{
    return m_KingLocation[index];
}
//________________________
//bool King::isKingValid()
//{
//    return true;
//}
//________________________________
//void King::moveKingInBoard(char)
//{
//
//}
