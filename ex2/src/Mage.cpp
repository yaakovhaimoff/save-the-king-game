#include "Mage.hpp"

// initializing the Mage member to default data
//_________________________________________________________
Mage::Mage() : m_MageLocation(0, 0), m_needToSaveKey(false),
m_teleport(false) {}
// setting the Mage loaction from the board
//______________________________________________
void Mage::setLocation(const Location& location)
{
	this->m_MageLocation = location;
}
// sending Mage location
//_______________________________________
Location Mage::getMageLocation()
{
	return this->m_MageLocation;
}
// checking what is the next step,
// and returמing its case to mageNextStep to handle it
//____________________________________
int Mage::isMageMoveValid(const int nextStep)
{
	switch (nextStep)
	{
	case Space:
	case Fire:
		return ContinueAndDelete;
	case Teleport:
	case GateKey:
		return StepAndSaveKey;
	}
	return DoNothing;
}
// after recieving the case of the next step, the move will be
// handled in this function accordingly,
// the move will go to its case, and in accordance to its case of move the 
// the keys will be sent to saveMageStep.
//_________________________________________________________________________
void Mage::mageNextStep(Board& board, const int nextStep, const int player,
	int& sumOfMoves, int row, int col)
{
	int decideMove = this->isMageMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// checking if the last move was GateKey
		// if it was a key will be send to be printed on the board
	case StepAndSaveKey:
		this->saveMageStep(board, row, col, player, Space);
		nextStep == GateKey ? this->m_needToSaveKey = true : this->m_teleport = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		// checking if the last move was teleport or GateKey
		// if it was one if them their key will be send to be printed on the board
		if (m_needToSaveKey || m_teleport)
		{
			this->saveMageStep(board, row, col, player, this->m_needToSaveKey ? GateKey : Teleport);
			this->m_needToSaveKey = false;
			this->m_teleport = false;
			break;
		}
		this->saveMageStep(board, row, col, player, Space);
		break;
	}
}
// saving the move new data in the board and in the Mage member location 
//_____________________________________________________________________________
void Mage::saveMageStep(Board& board, const int row, const int col, const int player, const int key)
{
	board.changeBoardItem(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col, player);
	board.changeBoardItem(this->getMageLocation().getRow(), this->getMageLocation().getCol(), key);
	this->setLocation(Location(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col));
}
// restarting the members to their initialization in order to atart a new level
//____________________________________
void Mage::restartMembersToNextLevel()
{
	this->m_needToSaveKey = false;
	this->m_teleport = false;
}
