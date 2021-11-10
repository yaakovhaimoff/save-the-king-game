#include "Board.hpp"

//---------------using section---------------
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
//_____________
Board::Board() 
: m_boardSrcFiles("Levels.txt"){}
// _____________________________
void Board::getLinesFromFiles()
{
	//     Read a file line-by-line
	for (auto line = std::string(); std::getline(m_boardSrcFiles, line) && line.compare("") !=0 ;)
	{
		m_textBoard.push_back(line);
	}
}
//_______________________________
void Board::printBoard()
{
	for (int row = 0; row < this->m_textBoard.size(); row++)
	{
		cout << this->m_textBoard[row] << endl;
	}
}
//_______________________________________
void Board::printMessages(int activePlayer, int moves, bool hasKey)
{
	char c = activePlayer;
	cout << "The control player is: " << c << endl;
	cout << "The sum of steps is: " << moves << endl;
	cout << "Does the thief have a key: " << hasKey << endl;

}
//_________________________________________________
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
//__________________________________________________________________
void Board::changeBoardItem(int row, int col, int player)
{
	this->m_textBoard[row][col] = player;
}
//__________________________________________________
int Board::getBoardItem(int row, int col)
{
	return m_textBoard[row][col];
}
//______________________
void Board::clearBoard()
{
	this->m_textBoard.clear();
}
//___________________________
bool Board::checkEndOfFile()
{
	return m_boardSrcFiles.eof();
}