#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string.h>
#include <string>

#include "Location.hpp"

class Board
{
    
public:
    void printBoard(int);
    void printMessages(int, int, bool);
    void getLinesFromFiles(int);
    Location getPlayerLoctionInBoard(int, int);
    void changeBoardItem(int, int, int, int);
    int getBoardItem(int, int, int);
    //    void clear();
private:
    std::ifstream m_boardSrcFiles;
    std::ifstream m_level[3];
    std::string m_levelName[3];
    std::vector<std::string> m_textBoard[3];
    
};
