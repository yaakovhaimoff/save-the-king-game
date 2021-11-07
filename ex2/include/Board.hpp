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

class Board
{
    
public:
    void printBoard(int);
    void getLinesFromFiles(int);
    std::vector<std::string> getBoard(int);
    void changeBoardItem(int, int, int, int);
    int getBoardItem(int, int, int);
    //    void clear();
private:
    std::ifstream m_boardSrcFiles;
    std::ifstream m_level[3];
    std::string m_levelName[3];
    std::vector<std::string> m_textBoard[3];
    
};
