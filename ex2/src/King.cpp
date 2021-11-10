#include "King.hpp"

//________________________________
King::King() : m_KingLocation(0, 0), m_needToSaveKey(false)
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
	case Space:
		return ContinueAndDelete;
	case GateKey:
		return StepAndSaveKey;
	case Teleport:
		return JumpToNext;
	case Throne:
		return GameOver;
	}
	return DontDoNothing;
}
//____________________________________________________________________
void King::kingNextStep(Board& board, int nextStep, int player, int &sumOfMoves, int row, int col)
{
	int decideMove = isKingMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveKingStep(board, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		if (m_needToSaveKey)
		{
			saveKingStep(board, row, col, player, GateKey);
			m_needToSaveKey = false;
			break;
		}
		saveKingStep(board, row, col, player, Space);
		break;
	case JumpToNext:
		break;
	case GameOver:
		saveKingStep(board, row, col, player, Space);
		std::system("cls");
		board.printBoard();
		break;
	}

}
//_______________________________________________________________________
void King::saveKingStep(Board &board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col, player);
	board.changeBoardItem(this->getKingLocation().getRow(), this->getKingLocation().getCol(), key);
	this->setLocation(Location(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col));
}

