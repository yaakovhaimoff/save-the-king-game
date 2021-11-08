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
	char c;
	for (int row = 0; row < m_board.getBoard(index).size(); row++)
	{
		for (int col = 0; col < m_board.getBoard(index)[row].size(); col++)
		{

			c = m_board.getBoard(index)[row][col];
			switch (c)
			{
			case KING:
				m_King.setLocation(Location(row, col));
				break;
			case MAGE:
				m_Mage.setLocation(Location(row, col));
				break;
			case WARRIOR:
				m_Warrior.setLocation(Location(row, col));
				break;
			case THIEF:
				m_Thief.setLocation(Location(row, col));
				break;
			default:
				break;
			}
		}
	}
}
//________________________________________
void Controller::playLevel(int indexLevel)
{
	int countKeyBoard = 0,
		activePlayer = 0;
	for (auto exit = false; !exit;)
	{
		auto c = _getch();
		switch (c)
		{
		case PlayersKey:
			activePlayer = decideActivePlayer(countKeyBoard);
			break;
		case SpecialKey:
			handleSpecialKey(activePlayer, indexLevel);
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
void Controller::handleSpecialKey(int activePlayer, int index)
{
	static int sumOfMoves = 0;
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
void Controller::movePlayerInBoard(int index, int player, int sumOfMoves, int row, int col, bool thiefHasKey)
{
	int nextStep;
	switch (player)
	{
	case KING:
		nextStep = m_board.getBoardItem(index, m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col);
		kingNextStep(index, m_King.isKingMoveValid(nextStep), row, col, player);
		break;
	case MAGE:
		nextStep = m_board.getBoardItem(index, m_Mage.getMageLocation().getRow() + row, m_Mage.getMageLocation().getCol() + col);
		mageNextStep(index, m_Mage.isMageMoveValid(nextStep), row, col, player);
		break;
	case WARRIOR:
		nextStep = m_board.getBoardItem(index, m_Warrior.getWarriorLocation().getRow() + row, m_Warrior.getWarriorLocation().getCol() + col);
		warriorNextStep(index, m_Warrior.isWarriorMoveValid(nextStep), row, col, player);
		break;
	case THIEF:
		m_board.changeBoardItem(index, m_Thief.getThiefLocation().getRow() + row, m_Thief.getThiefLocation().getCol() + col, player);
		m_board.changeBoardItem(index, m_Thief.getThiefLocation().getRow(), m_Thief.getThiefLocation().getCol(), Space);
		m_Thief.setLocation(Location(m_Thief.getThiefLocation().getRow() + row, m_Thief.getThiefLocation().getCol() + col));
		break;
	}
	std::system("cls");
	m_board.printMessages(player, sumOfMoves, thiefHasKey);
	m_board.printBoard(index);
}
//_________________________________
void Controller::kingNextStep(int index, int decideMove, int row, int col, int player)
{
	static bool needToSaveKey = false;
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveKingStep(index, row, col, player, Space);
			needToSaveKey = true;
		break;
	case ContinueAndDelete:
		if (needToSaveKey)
		{
			saveKingStep(index, row, col, player, GateKey);
			needToSaveKey = false;
			break;
		}
		saveKingStep(index, row, col, player, Space);
			break;
	case JumpToNext:
		break;
	case GameOver:
		saveKingStep(index, row, col, player, Space);
		std::system("cls");
		m_board.printBoard(index);
		break;
	}
}
//_____________________________________________________________________________
void Controller::saveKingStep(int index, int row, int col, int player, int key)
{
	m_board.changeBoardItem(index, m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col, player);
	m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol(), key);
	m_King.setLocation(Location(m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col));
}
//____________________________________________________________________________________
void Controller::mageNextStep(int index, int decideMove, int row, int col, int player)
{
	static bool needToSaveKey = false;
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveMageStep(index, row, col, player, Space);
		needToSaveKey = true;
		break;
	case ContinueAndDelete:
		if (needToSaveKey)
		{
			saveMageStep(index, row, col, player, GateKey);
			needToSaveKey = false;
			break;
		}
		saveMageStep(index, row, col, player, Space);
		break;
	case JumpToNext:
		break;
	}
}
//_____________________________________________________________________________
void Controller::saveMageStep(int index, int row, int col, int player, int key)
{
	m_board.changeBoardItem(index, m_Mage.getMageLocation().getRow() + row, m_Mage.getMageLocation().getCol() + col, player);
	m_board.changeBoardItem(index, m_Mage.getMageLocation().getRow(), m_Mage.getMageLocation().getCol(), key);
	m_Mage.setLocation(Location(m_Mage.getMageLocation().getRow() + row, m_Mage.getMageLocation().getCol() + col));

}
//________________________________________________________________________________
void Controller::warriorNextStep(int index, int decideMove, int row, int col, int player)
{
	static bool needToSaveKey = false;
	switch (decideMove)
	{
	case DontDoNothing:
		break;
	case StepAndSaveKey:
		saveWarriorStep(index, row, col, player, Space);
		needToSaveKey = true;
		break;
	case ContinueAndDelete:
		if (needToSaveKey)
		{
			saveWarriorStep(index, row, col, player, GateKey);
			needToSaveKey = false;
			break;
		}
		saveWarriorStep(index, row, col, player, Space);
		break;
	case JumpToNext:
		break;
	}

}
//___________________________________________________________________________________
void Controller::saveWarriorStep(int index, int row, int col, int player, int key)
{
	m_board.changeBoardItem(index, m_Warrior.getWarriorLocation().getRow() + row, m_Warrior.getWarriorLocation().getCol() + col, player);
	m_board.changeBoardItem(index, m_Warrior.getWarriorLocation().getRow(), m_Warrior.getWarriorLocation().getCol(), key);
	m_Warrior.setLocation(Location(m_Warrior.getWarriorLocation().getRow() + row, m_Warrior.getWarriorLocation().getCol() + col));

}