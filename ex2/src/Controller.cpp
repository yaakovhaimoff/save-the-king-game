#include "Controller.hpp"

// the intialization of Controller members
// are done at their own classes
//______________________
Controller::Controller()
{}
// runing the game
// the level ends at enter, and the game ends at end of file,
// unless the player will choose to end it when press 'escape'
//________________________
void Controller::runGame(bool exitEscape)
{
	while (!this->m_board.checkEndOfFile() && !exitEscape)
	{
		this->m_board.getLinesFromFiles();
		this->findPlayersLocation();
		this->m_board.createTeleportArr();
		this->m_board.printMessages(KING, 0, false);
		this->m_board.printBoard();
		this->playLevel(exitEscape);
		this->restartMembersToNewLevel();
		this->m_board.printEndOfLevelMessage();
	}
	if (!exitEscape)
	{
		std::system("cls");
		std::cout << "Game Over! \n" << std::endl;
	}
}
// getting the players location on the board
//____________________________________
void Controller::findPlayersLocation()
{
	this->m_King.setLocation(Location(m_board.getPlayerLoctionInBoard(KING)));
	this->m_Mage.setLocation(Location(m_board.getPlayerLoctionInBoard(MAGE)));
	this->m_Warrior.setLocation(Location(m_board.getPlayerLoctionInBoard(WARRIOR)));
	this->m_Thief.setLocation(Location(m_board.getPlayerLoctionInBoard(THIEF)));
}
// the level will ennd when the King gets to the '@'
// unless the player will press 'escape'
//__________________________
void Controller::playLevel(bool& exitEscape)
{
	int countKeyBoard = 0,
		activePlayer = 0,
		sumOfMoves = 0;;
	while (!this->m_King.isKingOnThrone())
	{
		auto c = _getch();
		switch (c)
		{
		case Playerp:
		case PlayerP:
			activePlayer = this->decideActivePlayer(countKeyBoard);
			break;
		case SpecialKey:
			this->handleSpecialKey(activePlayer, sumOfMoves);
			break;
		default:
			if (this->handleKeyBoardKey(c))
				exitEscape = true;
			break;
		}
		if (exitEscape)
			break;
	}
}
// every time the player presses 'p' / 'P' he can switch a 
// keyPlayer to move on the board. this switching will go in a circle.
// the method is deviding the amount of keyPlayers into Equilibrium classes.
// every class repesent the remaining division by the amount of keyBoards we have in the game
//__________________________________________________
int Controller::decideActivePlayer(int& countKeyBoard)
{
	countKeyBoard++;
	if ((countKeyBoard - 1) % numOfPlayers == 0)
	{
		return KING;
	}
	else if ((countKeyBoard - 1) % numOfPlayers == 1)
	{
		return WARRIOR;
	}
	else if ((countKeyBoard - 1) % numOfPlayers == 2)
	{
		return MAGE;
	}
	else if ((countKeyBoard - 1) % numOfPlayers == 3)
	{
		return THIEF;
	}
	return 1;
}
// sending the player to move his keyBoard by the arrow he pressed
//_________________________________________________________________
void Controller::handleSpecialKey(int activePlayer, int& sumOfMoves)
{
	auto c = _getch();
	switch (c)
	{
	case KB_Up:
		// Arrow Up pressed
		this->movePlayerInBoard(activePlayer, sumOfMoves, Up, 0);
		break;

	case KB_Down:
		// Arrow Down pressed
		this->movePlayerInBoard(activePlayer, sumOfMoves, Down, 0);
		break;

	case KB_Left:
		// Arrow Left pressed
		this->movePlayerInBoard(activePlayer, sumOfMoves, 0, Left);
		break;

	case KB_Right:
		// Arrow Right pressed
		this->movePlayerInBoard(activePlayer, sumOfMoves, 0, Right);
		break;
	}
}
// if the player chooses to end the game by pressing escape
//_______________________________________
bool Controller::handleKeyBoardKey(int c)
{
	switch (c)
	{
	case KB_Escape:
		return true;
	default:
		std::cout << "Unknown regular key pressed (code = " << c << ")\n";
		break;
	}
	return false;
}
// getting the next step, and sending every playerKey to her class
//  to handle the move and check if this move is valid, 
// and to decide what to do with it.
//______________________________________________________________________
void Controller::movePlayerInBoard(int player, int& sumOfMoves, int row,
	int col)
{
	int nextStep;
	switch (player)
	{
	case KING:
		nextStep = this->m_board.getBoardItem(this->m_King.getKingLocation().getRow() + row, this->m_King.getKingLocation().getCol() + col);
		this->m_King.kingNextStep(this->m_board, nextStep, player, sumOfMoves, row, col);
		break;
	case MAGE:
		nextStep = this->m_board.getBoardItem(this->m_Mage.getMageLocation().getRow() + row, this->m_Mage.getMageLocation().getCol() + col);
		this->m_Mage.mageNextStep(this->m_board, nextStep, player, sumOfMoves, row, col);
		break;
	case WARRIOR:
		nextStep = this->m_board.getBoardItem(this->m_Warrior.getWarriorLocation().getRow() + row, this->m_Warrior.getWarriorLocation().getCol() + col);
		this->m_Warrior.warriorNextStep(this->m_board, nextStep, player, sumOfMoves, row, col);
		break;
	case THIEF:
		nextStep = this->m_board.getBoardItem(this->m_Thief.getThiefLocation().getRow() + row, this->m_Thief.getThiefLocation().getCol() + col);
		this->m_Thief.thiefNextStep(this->m_board, nextStep, player, sumOfMoves, row, col);
		break;
	}
	// at the end of every movement we'll print the board 
	std::system("cls");
	this->m_board.printMessages(player, sumOfMoves, this->m_Thief.checkIfTheThiefHasAkey());
	this->m_board.printBoard();
}
// restarting the members to their intialzation in order to start a new level
//_________________________________________
void Controller::restartMembersToNewLevel()
{
	this->m_board.resetBoard();
	this->m_King.restartMembersToNextLevel();
	this->m_Mage.restartMembersToNextLevel();
	this->m_Thief.restartMembersToNextLevel();
	this->m_Warrior.restartMembersToNextLevel();
}
