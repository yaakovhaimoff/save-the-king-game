#include "Warrior.hpp"

//___________________________________
Warrior::Warrior() : m_WarriorLocation(0,0), m_needToSaveKey(false)
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
	case Space:
		return ContinueAndDelete;
	case Tile:
	case GateKey:
		return StepAndSaveKey;
	case Teleport:
		return JumpToNext;
	}
	return DontDoNothing;
}
//________________________________________________________________________________
void Warrior::warriorNextStep(Board& board, int nextStep, int player, int& sumOfMoves, int row, int col)
{
	int decideMove = isWarriorMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveWarriorStep(board, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		if (m_needToSaveKey)
		{
			saveWarriorStep(board,  row, col, player, GateKey);
			m_needToSaveKey = false;
			break;
		}
		saveWarriorStep(board, row, col, player, Space);
		break;
	case JumpToNext:
		Location nextTel = board.nextTeleportLocation(Location(m_WarriorLocation.getRow() + row, m_WarriorLocation.getCol() + col));
		row = (nextTel.getRow() - m_WarriorLocation.getRow());
		col = (nextTel.getCol() - m_WarriorLocation.getCol());
		saveWarriorStep(board, row, col + 1, player, Space);
		break;
	}
}
//___________________________________________________________________________________
void Warrior::saveWarriorStep(Board &board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col, player);
	board.changeBoardItem(this->getWarriorLocation().getRow(), this->getWarriorLocation().getCol(), key);
	this->setLocation(Location(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col));
}
