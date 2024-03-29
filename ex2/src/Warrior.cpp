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
	this->m_WarriorLocation = location;
}
// sending Warrior location
//____________________________________
Location Warrior::getWarriorLocation()
{
	return this->m_WarriorLocation;
}
// checking what is the next step,
// and returמing its case to warriorNextStep to handle it
//__________________________________________
int Warrior::isWarriorMoveValid(const int nextStep)
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
void Warrior::warriorNextStep(Board &board, const int nextStep, const int player,
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
		this->saveWarriorStep(board, row, col, player, Space);
		m_needToSaveKey = true;
		sumOfMoves++;
		break;
	case ContinueAndDelete:
		sumOfMoves++;
		// checking if the last move was GateKey
		// if it was a key will be send to be printed on the board
		if (m_needToSaveKey)
		{
			this->saveWarriorStep(board, row, col, player, GateKey);
			this->m_needToSaveKey = false;
			break;
		}
		this->saveWarriorStep(board, row, col, player, Space);
		break;
		// if the case is Teleport will get the next teleport location and send the king
		// to its coordinates
	case JumpToTheNextTeleport:
		Location nextTel = board.nextTeleportLocation(Location(this->m_WarriorLocation.getRow() + row, this->m_WarriorLocation.getCol() + col));
		row = (nextTel.getRow() - this->m_WarriorLocation.getRow());
		col = (nextTel.getCol() - this->m_WarriorLocation.getCol());
		this->saveWarriorStep(board, row, col + 1, player, Space);
		break;
	}
}
// saving the move new data in the board and in the Warrior member location
//___________________________________________________________________________________
void Warrior::saveWarriorStep(Board &board, const int row, const int col, const int player, const int key)
{
	board.changeBoardItem(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col, player);
	board.changeBoardItem(this->getWarriorLocation().getRow(), this->getWarriorLocation().getCol(), key);
	this->setLocation(Location(this->getWarriorLocation().getRow() + row, this->getWarriorLocation().getCol() + col));
}
// restarting the members to their initialization in order to atart a new level
//____________________________________
void Warrior::restartMembersToNextLevel()
{
	this->m_needToSaveKey = false;
}

