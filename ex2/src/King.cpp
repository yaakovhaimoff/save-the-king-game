#include "King.hpp"

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
	case MAGE:
	case WARRIOR:
	case THIEF:
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
//____________________________________________________________________
void King::kingNextStep(Board& board, int index, int decideMove, int player, int &sumOfMoves, int row, int col)
{
	static bool needToSaveKey = false;
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveKingStep(board, index, row, col, player, Space);
		needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		if (needToSaveKey)
		{
			saveKingStep(board, index, row, col, player, GateKey);
			needToSaveKey = false;
			break;
		}
		saveKingStep(board, index, row, col, player, Space);
		break;
	case JumpToNext:
		break;
	case GameOver:
		saveKingStep(board, index, row, col, player, Space);
		std::system("cls");
		board.printBoard(index);
		break;
	}

}
//_______________________________________________________________________
void King::saveKingStep(Board &board, int index, int row, int col, int player, int key)
{
	board.changeBoardItem(index, this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col, player);
	board.changeBoardItem(index, this->getKingLocation().getRow(), this->getKingLocation().getCol(), key);
	this->setLocation(Location(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col));
}

