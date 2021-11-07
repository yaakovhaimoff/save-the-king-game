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
		m_board.printBoard(level);
		playLevel(level);
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
			case TILE:
				m_Tile.setLocation(Location(row, col));
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
	for (auto exit = false; !exit; )
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
		return TILE;
	}
	return 1;
}
//________________________________
void Controller::handleSpecialKey(int activePlayer, int index)
{
	auto c = _getch();
	switch (c)
	{
	case KB_Up:
		// Arrow Up pressed
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow() - 1, m_King.getKingLocation().getCol(), activePlayer);
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getKingLocation().getRow() - 1, m_King.getKingLocation().getCol()));
		std::system("cls");
		m_board.printBoard(index);
		break;

	case KB_Down:
		//Arrow Down pressed
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow() + 1, m_King.getKingLocation().getCol(), activePlayer);
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getKingLocation().getRow() + 1, m_King.getKingLocation().getCol()));
		std::system("cls");
		m_board.printBoard(index);
		break;

	case KB_Left:
		//Arrow Left pressed
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol() - 1, activePlayer);
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol() - 1));
		std::system("cls");
		m_board.printBoard(index);
		break;

	case KB_Right:
		//Arrow Right pressed
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol() + 1, activePlayer);
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol() + 1));
		std::system("cls");
		m_board.printBoard(index);
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