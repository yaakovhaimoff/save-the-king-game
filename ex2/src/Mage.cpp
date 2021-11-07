#include "Mage.hpp"

//___________________________________
Mage::Mage() : m_MageLocation(0,0)
{}
//_________________________________________________________
void Mage::setLocation(const Location &location)
{
    m_MageLocation = location;
}
//_______________________________________
Location Mage::getMageLocation()
{
    return m_MageLocation;
}
//________________________
bool Mage::isMageMoveValid()
{
   return true;
}

