#include "Board.hpp"

//---------------using section---------------
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// _____________________________________
void Board::getLinesFromFiles(int index)
{
    if(index==0)
        m_boardSrcFiles.open("Levels.txt");
    getline(m_boardSrcFiles, m_levelName[index]);
    m_level[index].open(m_levelName[index]);
    //     Read a file line-by-line
    for (auto line = std::string(); std::getline(m_level[index],line);)
    {
        m_textBoard[index].push_back(line);
    }
}

void Board::printBoard(int index)
{
    for (int row = 0; row < m_textBoard[index].size(); row++)
        cout << m_textBoard[index][row] << endl;
}
std::vector<std::string> Board::getBoard(int index)
{
    return m_textBoard[index];
}
void Board::changeBoardItem(int index, int row, int col, int player)
{
  m_textBoard[index][row][col] = player;
}