#include "Controller.hpp"

//______________________
Controller::Controller()
{
	for (int level = 0; level < amountOfLevels; level++)
	{
		m_board.getLinesFromFiles(level);
	}
}
//________________________
void Controller::runGame()
{
	for (int level = 0; level < amountOfLevels; level++)
	{
		findPlayersLocation(level);
		m_board.printMessages('K', 0, false);
		m_board.printBoard(level);
		playLevel(level);
		std::system("cls");
	}
}
//_____________________________________________
void Controller::findPlayersLocation(int index)
{
	m_King.setLocation(Location(m_board.getPlayerLoctionInBoard(index, KING)));
	m_Mage.setLocation(Location(m_board.getPlayerLoctionInBoard(index, MAGE)));
	m_Warrior.setLocation(Location(m_board.getPlayerLoctionInBoard(index, WARRIOR)));
	m_Thief.setLocation(Location(m_board.getPlayerLoctionInBoard(index, THIEF)));
}
//________________________________________
void Controller::playLevel(int indexLevel)
{
	int countKeyBoard = 0,
		activePlayer = 0,
		sumOfMoves = 0;;
	for (auto exit = false; !exit;)
	{
		auto c = _getch();
		switch (c)
		{
		case PlayersKey:
			activePlayer = decideActivePlayer(countKeyBoard);
			break;
		case SpecialKey:
			handleSpecialKey(activePlayer, indexLevel, sumOfMoves);
			break;
		default:
			exit = handleKeyBoardKey(c);
			break;
		}
	}
}
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
//________________________________
void Controller::handleSpecialKey(int activePlayer, int index, int& sumOfMoves)
{
	static bool thiefHasKey = false;
	auto c = _getch();
	switch (c)
	{
	case KB_Up:
		// Arrow Up pressed
		movePlayerInBoard(index, activePlayer, sumOfMoves, Up, 0, thiefHasKey);
		break;

	case KB_Down:
		// Arrow Down pressed
		movePlayerInBoard(index, activePlayer, sumOfMoves, Down, 0, thiefHasKey);
		break;

	case KB_Left:
		// Arrow Left pressed
		movePlayerInBoard(index, activePlayer, sumOfMoves, 0, Left, thiefHasKey);
		break;

	case KB_Right:
		// Arrow Right pressed
		movePlayerInBoard(index, activePlayer, sumOfMoves, 0, Right, thiefHasKey);
		break;
	}
}
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
//_________________________________________________________________________
void Controller::movePlayerInBoard(int index, int player, int& sumOfMoves, int row, int col, bool thiefHasKey)
{
	int nextStep;
	switch (player)
	{
	case KING:
		nextStep = m_board.getBoardItem(index, m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col);
		m_King.kingNextStep(m_board, index, nextStep, player, sumOfMoves, row, col);
		break;
	case MAGE:
		nextStep = m_board.getBoardItem(index, m_Mage.getMageLocation().getRow() + row, m_Mage.getMageLocation().getCol() + col);
		m_Mage.mageNextStep(m_board, index, nextStep, player, sumOfMoves, row, col);
		break;
	case WARRIOR:
		nextStep = m_board.getBoardItem(index, m_Warrior.getWarriorLocation().getRow() + row, m_Warrior.getWarriorLocation().getCol() + col);
		m_Warrior.warriorNextStep(m_board, index, nextStep, player, sumOfMoves, row, col);
		break;
	case THIEF:
		nextStep = m_board.getBoardItem(index, m_Thief.getThiefLocation().getRow() + row, m_Thief.getThiefLocation().getCol() + col);
		m_Thief.thiefNextStep(m_board, index, nextStep, player, sumOfMoves, row, col);
		break;
	}
	std::system("cls");
	m_board.printMessages(player, sumOfMoves, thiefHasKey);
	m_board.printBoard(index);
}
