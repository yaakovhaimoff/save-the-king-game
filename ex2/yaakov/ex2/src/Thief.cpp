#include "Thief.hpp"

// initializing the Thief member to default data
//____________
Thief::Thief()
	: m_ThiefLocation(0, 0), m_needToSaveKey(false),
	m_amountOfKeys(0)
{
}
// setting the Thief loaction from the board
//_______________________________________________
void Thief::setLocation(const Location& location)
{
	m_ThiefLocation = location;
}
// sending Thief location
//________________________________
Location Thief::getThiefLocation()
{
	return this->m_ThiefLocation;
}
// returning if thief has a key
//__________________________________
bool Thief::checkIfTheThiefHasAkey()
{
	return this->m_amountOfKeys > 0;
}
// checking what is the next step,
// and returמing its case to thiefNextStep to handle it
//_______________________________________
int Thief::isThiefMoveValid(const int nextStep)
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
		return JumpToTheNextTeleport;
	}
	return DoNothing;
}
// after recieving the case of the next step, the move will be
// handled in this function accordingly,
// the move will go to its case, and in accordance to its case of move the
// the keys will be sent to saveThiefStep.
//_______________________________________________________________
void Thief::thiefNextStep(Board& board, const int nextStep, const int player,
	int& sumOfMoves, int row, int col)
{
	int decideMove = this->isThiefMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// checking if the last move was GateKey or Ork
		// if it was a key will be send to be printed on the board
	case StepAndSaveKey:
		this->saveThiefStep(board, row, col, player, Space);
		this->m_needToSaveKey = true;
		if (nextStep == GateKey)
			this->m_amountOfKeys++;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		// if the thief doesn't have key the function will skip this if
		// and will eat the key, but if elready posses a key,
		// the thief won't eat more keys until he uses his
		if (this->m_needToSaveKey && this->m_amountOfKeys != 1)
		{
			this->saveThiefStep(board, row, col, player, GateKey);
			this->m_needToSaveKey = false;
			sumOfMoves++;
			break;
		}
		this->saveThiefStep(board, row, col, player, Space);
		break;
		//  the thief will use his key to open the Gate and the amount
		// of his keys will restarted to zero
	case ThiefHasKey:
		if (m_amountOfKeys > 0)
		{
			this->saveThiefStep(board, row, col, player, Space);
			this->m_amountOfKeys = 0;
			this->m_needToSaveKey = false;
		}
		break;
		// if the case is Teleport will get the next teleport location and send the king
		// to its coordinates
	case JumpToTheNextTeleport:
		Location nextTel = board.nextTeleportLocation(Location(this->m_ThiefLocation.getRow() + row, this->m_ThiefLocation.getCol() + col));
		row = (nextTel.getRow() - this->m_ThiefLocation.getRow());
		col = (nextTel.getCol() - this->m_ThiefLocation.getCol());
		this->saveThiefStep(board, row, col + 1, player, Space);
		break;
	}
}
// saving the move new data in the board and in the Thief member location 
//___________________________________________________________________________________________________
void Thief::saveThiefStep(Board& board, const int row, const int col, const int player, const int key)
{
	board.changeBoardItem(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col, player);
	board.changeBoardItem(this->getThiefLocation().getRow(), this->getThiefLocation().getCol(), key);
	this->setLocation(Location(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col));
}
// restarting the members to their initialization in order to atart a new level
//____________________________________
void Thief::restartMembersToNextLevel()
{
	this->m_needToSaveKey = false;
	this->m_amountOfKeys = 0;
}
