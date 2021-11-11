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
void Thief::setLocation(const Location &location)
{
	m_ThiefLocation = location;
}
// sending Thief location
//________________________________
Location Thief::getThiefLocation()
{
	return m_ThiefLocation;
}
//
//__________________________
bool Thief::checkIfTheThiefHasAkey()
{
	return m_amountOfKeys > 0 ? true : false;
}
// checking what is the next step,
// and returמing its case to thiefNextStep to handle it
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
		return JumpToTheNextTeleport;
	}
	return DoNothing;
}
// after recieving the case of the next step, the move will be
// handled in this function accordingly,
// the move will go to its case, and in accordance to its case of move the
// the keys will be sent to saveThiefStep.
//_______________________________________________________________
void Thief::thiefNextStep(Board &board, int nextStep, int player,
						  int &sumOfMoves, int row, int col)
{
	int decideMove = isThiefMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// checking if the last move was GateKey or Ork
		// if it was a key will be send to be printed on the board
	case StepAndSaveKey:
		saveThiefStep(board, row, col, player, Space);
		m_needToSaveKey = true;
		if (nextStep == GateKey)
			m_amountOfKeys++;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		// if the thief doesn't have key the function will skip this if
		// and will eat the key, but if elready posses a key,
		// the thief won't eat more keys until he uses his
		if (m_needToSaveKey && m_amountOfKeys != 1)
		{
			saveThiefStep(board, row, col, player, GateKey);
			m_needToSaveKey = false;
			sumOfMoves++;
			break;
		}
		saveThiefStep(board, row, col, player, Space);
		break;
		//  the thief will use his key to open the Gate and the amount
		// of his keys will restarted to zero
	case ThiefHasKey:
		if (m_amountOfKeys > 0)
		{
			saveThiefStep(board, row, col, player, Space);
			m_amountOfKeys = 0;
			m_needToSaveKey = false;
		}
		break;
		// if the case is Teleport will get the next teleport location and send the king
		// to its coordinates
	case JumpToTheNextTeleport:
		Location nextTel = board.nextTeleportLocation(Location(m_ThiefLocation.getRow() + row, m_ThiefLocation.getCol() + col));
		row = (nextTel.getRow() - m_ThiefLocation.getRow());
		col = (nextTel.getCol() - m_ThiefLocation.getCol());
		saveThiefStep(board, row, col + 1, player, Space);
		break;
	}
}
// saving the move new data in the board and in the Thief member location 
//____________________________________________________________________________
void Thief::saveThiefStep(Board &board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col, player);
	board.changeBoardItem(this->getThiefLocation().getRow(), this->getThiefLocation().getCol(), key);
	this->setLocation(Location(this->getThiefLocation().getRow() + row, this->getThiefLocation().getCol() + col));
}
