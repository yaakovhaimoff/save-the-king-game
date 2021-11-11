#include "Board.hpp"

//---------------using section---------------
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// opening the board files with all the levels.
// intializing board members 
//____________
Board::Board()
	: m_boardSrcFiles("Levels.txt"),
	m_amountTeleport(0), m_teleportLocations(nullptr){}
// reading the level until the text files hits enter,
// the level ends at enter, and the game ends at end of file.
// _____________________________
void Board::getLinesFromFiles()
{
	//     Read a file line-by-line
	for (auto line = std::string(); std::getline(m_boardSrcFiles, line) && line.compare("") != 0;)
	{
		m_textBoard.push_back(line);
	}
}
// printing the board line by line
//______________________
void Board::printBoard()
{
	for (int row = 0; row < this->m_textBoard.size(); row++)
	{
		cout << this->m_textBoard[row] << endl;
	}
}
// printing the messages who will be displayed while playing the games
//_________________________________________________________________
void Board::printMessages(int activePlayer, int moves, bool hasKey)
{
	char c = activePlayer;
	cout << "The control player is: " << c << endl;
	cout << "The sum of steps is: " << moves << endl;
	cout << "Does the thief have a key: ";
	hasKey ? cout << "true\n" : cout << "false\n";
}
// messages which will printed at the end of every level 
//__________________________________
void Board::printEndOfLevelMessage()
{
	cout << "You have finished thw lavel succesfully!\n";
	cout << "Now to the next level->\n";
}
// getting the location of the player at the beginging of each level
//____________________________________________________
Location Board::getPlayerLoctionInBoard(int playerKey)
{
	for (int row = 0; row < m_textBoard.size(); row++)
	{
		for (int col = 0; col < m_textBoard[row].size(); col++)
		{
			if (playerKey == this->m_textBoard[row][col])
				return Location(row, col);
		}
	}
	return Location(0, 0);
}
// changing a board cell when moving a player on the board
//_______________________________________________________
void Board::changeBoardItem(int row, int col, int player)
{
	this->m_textBoard[row][col] = player;
}
// getting a board character to ccompare or check the 
// to check the next step of the player
//________________________________________
int Board::getBoardItem(int row, int col)
{
	return m_textBoard[row][col];
}
// clearing the board vector, after every level
//______________________
void Board::resetBoard()
{
	this->m_textBoard.clear();
	delete[] this->m_teleportLocations;
}
// returning if the file has ended
// the games will run until the end of file
// unless the player will choose to quit
//__________________________
bool Board::checkEndOfFile()
{
	return m_boardSrcFiles.eof();
}
//_____________________________
void Board::createTeleportArr()
{
	int size = findAmountOfTeleports();
	m_teleportLocations = new Location[size];
	locateTeleportsLocation();
}
//________________________________
int Board::findAmountOfTeleports()
{
	int numOfTeleports = 0;
	for (int row = 0; row < m_textBoard.size(); row++)
	{
		for (int col = 0; col < m_textBoard[row].size(); col++)
		{
			if ('X' == m_textBoard[row][col])
			{
				numOfTeleports++;
			}
		}
	}
	return m_amountTeleport = numOfTeleports;
}
//___________________________________
void Board::locateTeleportsLocation()
{
	int indexInLocationArr = 0;
	for (int row = 0; row < m_textBoard.size(); row++)
	{
		for (int col = 0; col < m_textBoard[row].size(); col++)
		{
			if ('X' == m_textBoard[row][col])
			{
				m_teleportLocations[indexInLocationArr] = Location(row, col);
				indexInLocationArr++;
			}
		}
	}
}
//_____________________________________________________
Location Board::nextTeleportLocation(Location boardTel)
{
	int col;
	for (col = 0; col < m_amountTeleport; col++)
	{
		if (teleportLocationEqual(boardTel, m_teleportLocations[col]))
		{
			break;
		}
	}
	return col % 2 == 0 ? m_teleportLocations[col + 1] : m_teleportLocations[col - 1];

}
//__________________________________________________________________
bool Board::teleportLocationEqual(Location boardTel, Location arrTel)
{
	return boardTel.getCol() == arrTel.getCol() && boardTel.getRow() == arrTel.getRow();
}