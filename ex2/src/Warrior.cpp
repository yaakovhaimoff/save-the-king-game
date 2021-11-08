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
//________________________________________________________________________________
void Warrior::warriorNextStep(Board& board, int index, int decideMove, int player, int& sumOfMoves, int row, int col)
{
	static bool needToSaveKey = false;
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveWarriorStep(board, index, row, col, player, Space);
		needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		if (needToSaveKey)
		{
			saveWarriorStep(board, index, row, col, player, GateKey);
			needToSaveKey = false;
			break;
		}
		saveWarriorStep(board, index, row, col, player, Space);
		break;
	case JumpToNext:
		break;
	}

}
//___________________________________________________________________________________
void Warrior::saveWarriorStep(Board &board, int index, int row, int col, int player, int key)
{
	board.changeBoardItem(index, this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col, player);
	board.changeBoardItem(index, this->getWarriorLocation().getRow(), this->getWarriorLocation().getCol(), key);
	this->setLocation(Location(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col));
}
