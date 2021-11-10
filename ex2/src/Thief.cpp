#include "Thief.hpp"

//___________________________________
Thief::Thief() : m_ThiefLocation(0, 0), m_needToSaveKey(false),
m_thiefKey(false), m_amountOfKeys(0)
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
	case Space:
		return ContinueAndDelete;
	case Gate:
		return ThiefHasKey;
	case GateKey:
	case Teleport:
		return StepAndSaveKey;
	}
	return DontDoNothing;
}
//________________________________________________________________________________
void Thief::thiefNextStep(Board& board, int nextStep, int player, int& sumOfMoves, int row, int col)
{
	int decideMove = isThiefMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveThiefStep(board, row, col, player, Space);
		//m_thiefKey = true;
		m_needToSaveKey = true;
		if (nextStep == GateKey)
			m_amountOfKeys++;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		if (m_needToSaveKey && m_amountOfKeys != 1)
		{
			saveThiefStep(board, row, col, player, GateKey);
			m_needToSaveKey = false;
			sumOfMoves++;
			break;
		}
		saveThiefStep(board, row, col, player, Space);
		break;
	case ThiefHasKey:
		if (m_amountOfKeys > 0)
		{
			saveThiefStep(board, row, col, player, Space);
			m_amountOfKeys = 0;
			m_needToSaveKey = false;
		}
	case JumpToNext:
		break;
	}

}
//___________________________________________________________________________________
void Thief::saveThiefStep(Board& board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col, player);
	board.changeBoardItem(this->getThiefLocation().getRow(), this->getThiefLocation().getCol(), key);
	this->setLocation(Location(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col));
}
