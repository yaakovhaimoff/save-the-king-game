#include "Controller.hpp"

// the intialization of Controller members
// are done at their classes
//______________________
Controller::Controller()
{}
// runing the game
// the level ends at enter, and the game ends at end of file,
// unless the player will choose to end it when press 'escape'
//________________________
void Controller::runGame()
{
	while (!m_board.checkEndOfFile())
	{
		m_board.getLinesFromFiles();
		findPlayersLocation();
		m_board.createTeleportArr();
		m_board.printMessages(KING, 0, false);
		m_board.printBoard();
		playLevel();
		std::system("cls");
		m_board.clearBoard();
		m_board.printEndOfLevelMessage();
	}
}
// getting the players location on the board
//____________________________________
void Controller::findPlayersLocation()
{
	m_King.setLocation(Location(m_board.getPlayerLoctionInBoard(KING)));
	m_Mage.setLocation(Location(m_board.getPlayerLoctionInBoard(MAGE)));
	m_Warrior.setLocation(Location(m_board.getPlayerLoctionInBoard(WARRIOR)));
	m_Thief.setLocation(Location(m_board.getPlayerLoctionInBoard(THIEF)));
}
// the level will ennd when the King gets to the '@'
// unless the player will press 'escape'
//__________________________
void Controller::playLevel()
{
	int countKeyBoard = 0,
		activePlayer = 0,
		sumOfMoves = 0;;
	for (auto exit = false; !exit;)
	{
		auto c = _getch();
		switch (c)
		{
		case Playerp:
		case PlayerP:
			activePlayer = decideActivePlayer(countKeyBoard);
			break;
		case SpecialKey:
			handleSpecialKey(activePlayer, sumOfMoves);
			break;
		default:
			exit = handleKeyBoardKey(c);
			break;
		}
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
		movePlayerInBoard(activePlayer, sumOfMoves, Up, 0);
		break;

	case KB_Down:
		// Arrow Down pressed
		movePlayerInBoard(activePlayer, sumOfMoves, Down, 0);
		break;

	case KB_Left:
		// Arrow Left pressed
		movePlayerInBoard(activePlayer, sumOfMoves, 0, Left);
		break;

	case KB_Right:
		// Arrow Right pressed
		movePlayerInBoard(activePlayer, sumOfMoves, 0, Right);
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
		std::cout << "Escape pressed. Exiting...\n";
		// exit game message
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
		nextStep = m_board.getBoardItem(m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col);
		m_King.kingNextStep(m_board, nextStep, player, sumOfMoves, row, col);
		break;
	case MAGE:
		nextStep = m_board.getBoardItem(m_Mage.getMageLocation().getRow() + row, m_Mage.getMageLocation().getCol() + col);
		m_Mage.mageNextStep(m_board, nextStep, player, sumOfMoves, row, col);
		break;
	case WARRIOR:
		nextStep = m_board.getBoardItem(m_Warrior.getWarriorLocation().getRow() + row, m_Warrior.getWarriorLocation().getCol() + col);
		m_Warrior.warriorNextStep(m_board, nextStep, player, sumOfMoves, row, col);
		break;
	case THIEF:
		nextStep = m_board.getBoardItem(m_Thief.getThiefLocation().getRow() + row, m_Thief.getThiefLocation().getCol() + col);
		m_Thief.thiefNextStep(m_board, nextStep, player, sumOfMoves, row, col);
		break;
	}
	// at the end of every movement we'll print the board 
	std::system("cls");
	m_board.printMessages(player, sumOfMoves, /*m_Thief.checkIfTheThiefHasAkey()*/ true);
	m_board.printBoard();
}
