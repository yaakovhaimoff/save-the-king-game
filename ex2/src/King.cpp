#include "King.hpp"

// initializing the King member to default data
//________________________________
King::King() : m_KingLocation(0, 0),
			   m_needToSaveKey(false) {}
// setting the King loaction from the board
//______________________________________________
void King::setLocation(const Location &location)
{
	m_KingLocation = location;
}
// sending King location
//______________________________
Location King::getKingLocation()
{
	return m_KingLocation;
}
// checking what is the next step,
// and returמing its case to kingNextStep to handle it
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
		return JumpToTheNextTeleport;
	case Throne:
		return GameOver;
	}
	return DoNothing;
}
// after recieving the case of the next step, the move will be
// handled in this function accordingly,
// the move will go to its case, and in accordance to its case of move the
// the keys will be sent to saveKingStep.
//______________________________________________________________
void King::kingNextStep(Board &board, int nextStep, int player,
						int &sumOfMoves, int row, int col)
{
	int decideMove = isKingMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// if the nextStep is on the GateKey will want to alert
		// the function in the nextStep to know to print it
		// in the next step after this one
	case StepAndSaveKey:
		saveKingStep(board, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		// checking if the last move was GateKey
		// if it was a key will be send to be printed on the board
		if (m_needToSaveKey)
		{
			saveKingStep(board, row, col, player, GateKey);
			m_needToSaveKey = false;
			break;
		}
		saveKingStep(board, row, col, player, Space);
		break;
		// if the case is Teleport will get the next teleport location and send the king
		// to its coordinates
	case JumpToTheNextTeleport:
		Location nextTeleport =
			board.nextTeleportLocation(Location(m_KingLocation.getRow() + row, m_KingLocation.getCol() + col));
		row = (nextTeleport.getRow() - m_KingLocation.getRow());
		col = (nextTeleport.getCol() - m_KingLocation.getCol());
		saveKingStep(board, row, col + 1, player, Space);
		break;
		// if the player got to '@' the level ends
	case GameOver:
		saveKingStep(board, row, col, player, Space);
		std::system("cls");
		board.printBoard();
		break;
	}
}
// saving the move new data in the board and in the king member location
//_________________________________________________________________________
void King::saveKingStep(Board &board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col, player);
	board.changeBoardItem(this->getKingLocation().getRow(), this->getKingLocation().getCol(), key);
	this->setLocation(Location(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col));
}
