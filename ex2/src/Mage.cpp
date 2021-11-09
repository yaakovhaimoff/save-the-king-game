#include "Mage.hpp"

//___________________________________
Mage::Mage() : m_MageLocation(0,0), m_needToSaveKey(false)
{}
//_________________________________________________________
void Mage::setLocation(const Location &location)
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
	case WARRIOR:
	case KING:
	case THIEF:
	case Gate:
	case Tile:
	case Wall:
	case Throne:
		return DontDoNothing;
	case Space:
	case Fire:
		return ContinueAndDelete;
	case Teleport:
	case GateKey:
		return StepAndSaveKey;
	}
	return 1;
}
//____________________________________________________________________________________
void Mage::mageNextStep(Board& board, int index, int nextStep, int player, int& sumOfMoves, int row, int col)
{
	int decideMove = isMageMoveValid(nextStep);
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveMageStep(board, index, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		if (m_needToSaveKey)
		{
			saveMageStep(board, index, row, col, player, GateKey);
			m_needToSaveKey = false;
			break;
		}
		saveMageStep(board, index, row, col, player, Space);
		break;
	case JumpToNext:
		break;
	}
}
//_____________________________________________________________________________
void Mage::saveMageStep(Board &board, int index, int row, int col, int player, int key)
{
	board.changeBoardItem(index, this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col, player);
	board.changeBoardItem(index, this->getMageLocation().getRow(), this->getMageLocation().getCol(), key);
	this->setLocation(Location(this->getMageLocation().getRow() + row, this->getMageLocation().getCol() + col));
}