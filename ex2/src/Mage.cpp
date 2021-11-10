#include "Mage.hpp"

//___________________________________
Mage::Mage() : m_MageLocation(0, 0), m_needToSaveKey(false),
m_teleport(false) {}
//_________________________________________________________
void Mage::setLocation(const Location& location)
{
	m_MageLocation = location;
}
//_______________________________________
Location Mage::getMageLocation()
{
	return m_MageLocation;
}
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
	return DontDoNothing;
}
//____________________________________________________________________________________
void Mage::mageNextStep(Board& board, int nextStep, int player, int& sumOfMoves, int row, int col)
{
	int decideMove = isMageMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveMageStep(board, row, col, player, Space);
		nextStep == GateKey ? m_needToSaveKey = true : m_teleport = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
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
//_____________________________________________________________________________
void Mage::saveMageStep(Board& board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col, player);
	board.changeBoardItem(this->getMageLocation().getRow(), this->getMageLocation().getCol(), key);
	this->setLocation(Location(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col));
}