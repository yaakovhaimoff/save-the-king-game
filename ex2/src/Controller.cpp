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
int Controller::decideActivePlayer(int &countKeyBoard)
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
		movePlayerInBoard(activePlayer, -1, 0);
		break;

	case KB_Down:
		// Arrow Down pressed
		movePlayerInBoard(activePlayer, 1, 0);
		break;

	case KB_Left:
		// Arrow Left pressed
		movePlayerInBoard(activePlayer, 0, -1);
		break;

	case KB_Right:
		// Arrow Right pressed
		movePlayerInBoard(activePlayer, 0, 1);
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
void Controller::movePlayerInBoard(int player, int row, int col)
{
	switch (player)
	{
	case KING:
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col, player);
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getKingLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getKingLocation().getRow() + row, m_King.getKingLocation().getCol() + col));
		break;
	case MAGE:
		m_board.changeBoardItem(index, m_King.getMageLocation().getRow() + row, m_King.getMageLocation().getCol() + col, player);
		m_board.changeBoardItem(index, m_King.getMageLocation().getRow(), m_King.getMageLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getMageLocation().getRow() + row, m_King.getMageLocation().getCol()));
		break;
	case WARRIOR:
		m_board.changeBoardItem(index, m_King.getWarriorLocation().getRow() + row, m_King.getWarriorLocation().getCol() + col, player);
		m_board.changeBoardItem(index, m_King.getWarriorLocation().getRow(), m_King.getWarriorLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getWarriorLocation().getRow() + row, m_King.getWarriorLocation().getCol() + col));
		break;
	case TILE:
		m_board.changeBoardItem(index, m_King.getTileLocation().getRow() + row, m_King.getTileLocation().getCol() + col, player);
		m_board.changeBoardItem(index, m_King.getKingLocation().getRow(), m_King.getTileLocation().getCol(), Space);
		m_King.setLocation(Location(m_King.getTileLocation().getRow() + row, m_King.getTileLocation().getCol() + col));
		break;
	}
	std::system("cls");
	m_board.printBoard(index);
}