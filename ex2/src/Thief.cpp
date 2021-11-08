#include "Thief.hpp"

//___________________________________
Thief::Thief() : m_ThiefLocation(0,0)
{}
//_________________________________________________________
void Thief::setLocation(const Location &location)
{
    m_ThiefLocation = location;
}
//_______________________________________
Location Thief::getThiefLocation()
{
    return m_ThiefLocation;
}
//________________________
bool Thief::isThiefMoveValid()
{
   return true;
}

//________________________________________________________________________________
void Warrior::warriorNextStep(Board& board, int index, int decideMove, int player, int& sumOfMoves, int row, int col)
