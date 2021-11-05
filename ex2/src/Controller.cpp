#include "Controller.hpp"

Controller::Controller()
{
    for (int i=0; i<2; i++)
    {
        m_board.getLinesFromFiles(i);
        m_board.printBoard(i);
        run();
    }
}
void Controller::run()
{
    
    
}
