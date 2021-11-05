#include "Board.hpp"

//---------------using section---------------
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// _____________________________________
void Board::getLinesFromFiles(int count)
{
    if(count==0)
        m_boardSrcFiles.open("rcs/Levels");
    getline(m_boardSrcFiles, m_levelName[count]);
    m_level[count].open(m_levelName[count]);
    //     Read a file line-by-line
    for (auto line = std::string(); std::getline(m_level[count],line);)
    {
        m_textBoard[count].push_back(line);
    }
}

void Board::printBoard(int count)
{
    for (int row = 0; row < m_textBoard[count].size(); row++)
        cout << m_textBoard[count][row] << endl;
}
