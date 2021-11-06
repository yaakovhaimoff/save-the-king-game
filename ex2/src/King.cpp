#include "King.hpp"

King::King(): m_KingLocation(0, 0)
{}
//bool King::isKingValid()
//{
//    return true;
//}
//void King::moveKingInBoard(char)
//{
//
//}
void King::setLocation(const Location &location)
{
    m_KingLocation = location;
}
Location King::getKingLocation()
{
    return m_KingLocation;
}
