#include "Mage.hpp"

// initializing the Mage member to default data
//_________________________________________________________
Mage::Mage() : m_MageLocation(0, 0), m_needToSaveKey(false),
m_teleport(false) {}
// setting the Mage loaction from the board
//______________________________________________
void Mage::setLocation(const Location& location)
{
	m_MageLocation = location;
}
// sending Mage location
//_______________________________________
Location Mage::getMageLocation()
{
	return m_MageLocation;
}
// checking what is the next step,
// and returמing its case to mageNextStep to handle it
//____________________________________
int Mage::isMageMoveValid(int nextStep)
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
//____________________________________________________________________________________
void Mage::mageNextStep(Board& board, int nextStep, int player, int& sumOfMoves, int row, int col)
{
	int decideMove = isMageMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// checking if the last move was GateKey
		// if it was a key will be send to be printed on the board
	case StepAndSaveKey:
		saveMageStep(board, row, col, player, Space);
		nextStep == GateKey ? m_needToSaveKey = true : m_teleport = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		// checking if the last move was teleport or GateKey
		// if it was one if them their key will be send to be printed on the board
		if (m_needToSaveKey || m_teleport)
		{
			saveMageStep(board, row, col, player, m_needToSaveKey ? GateKey : Teleport);
			m_needToSaveKey = false;
			m_teleport = false;
			break;
		}
		saveMageStep(board, row, col, player, Space);
		break;
	}
}
// saving the move new data in the board and in the Mage member location 
//_____________________________________________________________________________
void Mage::saveMageStep(Board& board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col, player);
	board.changeBoardItem(this->getMageLocation().getRow(), this->getMageLocation().getCol(), key);
	this->setLocation(Location(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col));
}