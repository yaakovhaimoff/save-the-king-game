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
//____________________________________
int Warrior::isWarriorMoveValid(int nextStep)
{
	switch (nextStep)
	{
	case MAGE:
	case KING:
	case THIEF:
	case Gate:
	case Wall:
	case Throne:
	case Fire:
		return DontDoNothing;
	case Space:
		return ContinueAndDelete;
	case Tile:
	case Teleport:
	case GateKey:
		return StepAndSaveKey;
	}
	return 1;
}

