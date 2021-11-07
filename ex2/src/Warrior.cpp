#include "Warrior.hpp"

//___________________________________
Warrior::Warrior() : m_WarriorLocation(0,0)
{}
//_________________________________________________________
void Warrior::setLocation(const Location &location)
{
    m_WarriorLocation = location;
}
//_______________________________________
Location Warrior::getWarriorLocation()
{
    return m_WarriorLocation;
}
//________________________
bool Warrior::isWarriorMoveValid()
{
   return true;
}

