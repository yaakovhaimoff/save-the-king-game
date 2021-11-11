#include "Warrior.hpp"

// initializing the Warrior member to default data
//___________________________________
Warrior::Warrior() : m_WarriorLocation(0, 0), m_needToSaveKey(false)
{
}
// setting the Warrior loaction from the board
//__________________________________________________
void Warrior::setLocation(const Location &location)
{
	m_WarriorLocation = location;
}
// sending Warrior location
//____________________________________
Location Warrior::getWarriorLocation()
{
	return m_WarriorLocation;
}
// checking what is the next step,
// and returמing its case to warriorNextStep to handle it
//__________________________________________
int Warrior::isWarriorMoveValid(int nextStep)
{
	switch (nextStep)
	{
	case Space:
		return ContinueAndDelete;
	case Tile:
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
// the keys will be sent to saveWarriorStep.
//____________________________________________________________________
void Warrior::warriorNextStep(Board &board, int nextStep, int player,
							  int &sumOfMoves, int row, int col)
{
	int decideMove = isWarriorMoveValid(nextStep);
	switch (decideMove)
	{
	case DoNothing:
		break;
		// if the nextStep is on the GateKey will want to alert 
		// the function in the nextStep to know to print it 
		// in the next step after this one
	case StepAndSaveKey:
		saveWarriorStep(board, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		// checking if the last move was GateKey
		// if it was a key will be send to be printed on the board
		if (m_needToSaveKey)
		{
			saveWarriorStep(board, row, col, player, GateKey);
			m_needToSaveKey = false;
			break;
		}
		saveWarriorStep(board, row, col, player, Space);
		break;
		// if the case is Teleport will get the next teleport location and send the king
		// to its coordinates
	case JumpToTheNextTeleport:
		Location nextTel = board.nextTeleportLocation(Location(m_WarriorLocation.getRow() + row, m_WarriorLocation.getCol() + col));
		row = (nextTel.getRow() - m_WarriorLocation.getRow());
		col = (nextTel.getCol() - m_WarriorLocation.getCol());
		saveWarriorStep(board, row, col + 1, player, Space);
		break;
	}
}
// saving the move new data in the board and in the Warrior member location
//___________________________________________________________________________________
void Warrior::saveWarriorStep(Board &board, int row, int col, int player, int key)
{
	board.changeBoardItem(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col, player);
	board.changeBoardItem(this->getWarriorLocation().getRow(), this->getWarriorLocation().getCol(), key);
	this->setLocation(Location(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col));
}
