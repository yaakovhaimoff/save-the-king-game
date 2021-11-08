#include "King.hpp"
#include "gamesTools.hpp"

//________________________________
King::King() : m_KingLocation(0, 0)
{}
//______________________________________________
void King::setLocation(const Location& location)
{
	m_KingLocation = location;
}
//______________________________
Location King::getKingLocation()
{
	return m_KingLocation;
}
//____________________________________
int King::isKingMoveValid(int nextStep)
{
	switch (nextStep)
	{
	case Fire:
	case Gate:
	case Tile:
	case Wall:
		return DontDoNothing;
	case Space:
		return ContinueAndDelete;
	case GateKey:
		return StepAndSaveKey;
	case Teleport:
		return JumpToNext;
	case Throne:
		return GameOver;
	}
	return 1;
}

