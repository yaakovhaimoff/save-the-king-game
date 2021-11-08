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
//____________________________________
int Mage::isMageMoveValid(int nextStep)
{
	switch (nextStep)
	{
	case WARRIOR:
	case KING:
	case THIEF:
	case Gate:
	case Tile:
	case Wall:
	case Throne:
		return DontDoNothing;
	case Space:
	case Fire:
		return ContinueAndDelete;
	case Teleport:
	case GateKey:
		return StepAndSaveKey;
	}
	return 1;
}
