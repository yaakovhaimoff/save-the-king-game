#include "King.hpp"

//___________________________________
King::King() : m_KingLocation(0,0)
{}
//_________________________________________________________
void King::setLocation(const Location &location)
{
    m_KingLocation = location;
}
//_______________________________________
Location King::getKingLocation()
{
    return m_KingLocation;
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
