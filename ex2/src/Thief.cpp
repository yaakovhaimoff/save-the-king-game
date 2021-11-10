#include "Thief.hpp"

//____________
Thief::Thief()
	: m_ThiefLocation(0, 0), m_needToSaveKey(false),
	m_amountOfKeys(0)
{}
//_______________________________________________
void Thief::setLocation(const Location& location)
{
	m_ThiefLocation = location;
}
//________________________________
Location Thief::getThiefLocation()
{
	return m_ThiefLocation;
}
//__________________________
bool Thief::getThiegHasKey()
{
	return m_amountOfKeys > 0;

}
//_______________________________________
int Thief::isThiefMoveValid(int nextStep)
{
	switch (nextStep)
	{
	case Space:
		return ContinueAndDelete;
	case Gate:
		return ThiefHasKey;
	case GateKey:
		return StepAndSaveKey;
	case Teleport:
		return JumpToNext;
	}
	return DontDoNothing;
}
//_______________________________________________________________
void Thief::thiefNextStep(Board& board, int nextStep, int player,
	int& sumOfMoves, int row, int col)
{
	int decideMove = isThiefMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveThiefStep(board, row, col, player, Space);
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
		Location nextTel = board.nextTeleportLocation(Location(m_ThiefLocation.getRow() + row, m_ThiefLocation.getCol() + col));
		row = (nextTel.getRow() - m_ThiefLocation.getRow());
		col = (nextTel.getCol() - m_ThiefLocation.getCol());
		saveThiefStep(board, row, col + 1, player, Space);

		break;
	}
}
//____________________________________________________________________________
void Thief::saveThiefStep(Board& board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col, player);
	board.changeBoardItem(this->getThiefLocation().getRow(), this->getThiefLocation().getCol(), key);
	this->setLocation(Location(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col));
}
