#include "Controller.hpp"

Controller::Controller()
{
    for (int i=0; i<3; i++)
    {
        m_board.getLinesFromFiles(i);
        m_board.printBoard(i);
        findPlayersLocation(i);
        runGame();
    }
}
void Controller::findPlayersLocation(int index)
{
    char c;
    for (int row=0; row<m_board.getBoard(index).size(); row++)
    {
        for (int col=0; col<m_board.getBoard(index)[row].size(); col++)
        {
            
            c = m_board.getBoard(index)[row][col];
            switch (c)
            {
                case KING:
                    m_King.setLocation(Location(row, col));
                    break;
                    
                default:
                    break;
            }
        }
    }
}
void Controller::runGame()
{
    
    
}
