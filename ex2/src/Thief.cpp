#include "Thief.hpp"

//___________________________________
Thief::Thief() : m_ThiefLocation(0, 0), m_needToSaveKey(false),
m_thiefKey(false)
{}
//_______________________________________________
void Thief::setLocation(const Location& location)
{
	m_ThiefLocation = location;
}
//_______________________________________
Location Thief::getThiefLocation()
{
	return m_ThiefLocation;
}
//____________________________________
int Thief::isThiefMoveValid(int nextStep)
{
	switch (nextStep)
	{
	case MAGE:
	case KING:
	case WARRIOR:
	case Wall:
	case Throne:
	case Fire:
	case Tile:
		return DontDoNothing;
	case Space:
		return ContinueAndDelete;
	case Gate:
		return ThiefHasKey;
	case GateKey:
	case Teleport:
		return StepAndSaveKey;
	}
	return 1;
}
//________________________________________________________________________________
void Thief::thiefNextStep(Board& board, int index, int nextStep, int player, int& sumOfMoves, int row, int col)
{
	int decideMove = isThiefMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveThiefStep(board, index, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		if (nextStep == GateKey)
			m_thiefKey = true;
		if (m_needToSaveKey && m_thiefKey)
		{
			saveThiefStep(board, index, row, col, player, GateKey);
			m_needToSaveKey = false;
			sumOfMoves++;
			break;
		}
		saveThiefStep(board, index, row, col, player, Space);
		break;
	case ThiefHasKey:
		if (nextStep == Gate && m_thiefKey)
		{
			saveThiefStep(board, index, row, col, player, Space); saveThiefStep(board, index, row, col, player, Space);
			m_thiefKey = false;
		}
	case JumpToNext:
		break;
	}

}
//___________________________________________________________________________________
void Thief::saveThiefStep(Board& board, int index, int row, int col, int player, int key)
{
	board.changeBoardItem(index, this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col, player);
	board.changeBoardItem(index, this->getThiefLocation().getRow(), this->getThiefLocation().getCol(), key);
	this->setLocation(Location(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col));
}
