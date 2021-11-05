#pragma once
#include <stdio.h>
#include "Board.hpp"
#include "King.hpp"

class Controller
{
public:
    Controller();
    void run();
    
private:
    Board m_board;
    
};
