#include "King.hpp"

// initializing the King member to default data
//________________________________
King::King() : m_KingLocation(0, 0),
			   m_needToSaveKey(false),
			   m_kingOnThrone(false) {}
// setting the King loaction from the board
//______________________________________________
void King::setLocation(const Location &location)
{
	this->m_KingLocation = location;
}
// sending King location
//______________________________
Location King::getKingLocation()
{
	return this->m_KingLocation;
}
// checking what is the next step,
// and returמing its case to kingNextStep to handle it
//____________________________________
int King::isKingMoveValid(const int nextStep)
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
void King::kingNextStep(Board &board, const int nextStep, const int player,
						int &sumOfMoves, int row, int col)
{
	int decideMove = this->isKingMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// if the nextStep is on the GateKey will want to alert
		// the function in the nextStep to know to print it
		// in the next step after this one
	case StepAndSaveKey:
		this->saveKingStep(board, row, col, player, Space);
		this->m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		// checking if the last move was GateKey
		// if it was a key will be send to be printed on the board
		if (this->m_needToSaveKey)
		{
			this->saveKingStep(board, row, col, player, GateKey);
			this->m_needToSaveKey = false;
			break;
		}
		this->saveKingStep(board, row, col, player, Space);
		break;
		// if the case is Teleport will get the next teleport location and send the king
		// to its coordinates
	case JumpToTheNextTeleport:
		Location nextTeleport =
			board.nextTeleportLocation(Location(this->m_KingLocation.getRow() + row, this->m_KingLocation.getCol() + col));
		row = (nextTeleport.getRow() - this->m_KingLocation.getRow());
		col = (nextTeleport.getCol() - this->m_KingLocation.getCol());
		saveKingStep(board, row, col + 1, player, Space);
		break;
		// if the player got to '@' the level ends
	case GameOver:
		this->saveKingStep(board, row, col, player, Space);
		this->m_kingOnThrone = true;
		break;
	}
}
// saving the move new data in the board and in the king member location
//_________________________________________________________________________
void King::saveKingStep(Board &board, const int row, const int col, const int player, const int key)
{
	board.changeBoardItem(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col, player);
	board.changeBoardItem(this->getKingLocation().getRow(), this->getKingLocation().getCol(), key);
	this->setLocation(Location(this->getKingLocation().getRow() + row, this->getKingLocation().getCol() + col));
}
// restarting the members to their initialization in order to atart a new level
//____________________________________
void King::restartMembersToNextLevel()
{
	this->m_needToSaveKey = false;
	this->m_kingOnThrone = false;
}
// returning is the king on the throne
//_________________________
bool King::isKingOnThrone()
{
	return this->m_kingOnThrone;
}
