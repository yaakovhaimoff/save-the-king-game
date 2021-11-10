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
    Board();
    void getLinesFromFiles();
    void printBoard();
    void printMessages(int, int, bool);
    Location getPlayerLoctionInBoard(int);
    void changeBoardItem(int, int, int);
    int getBoardItem(int, int);
    void clearBoard();
    bool checkEndOfFile();
    void createTeleportArr();
    int findAmountOfTeleports();
    void locateTeleportsLocation();
    Location nextTeleportLocation(Location);
    bool teleportLocationEqual(Location, Location);

private:
    std::ifstream m_boardSrcFiles;
    std::vector<std::string> m_textBoard;  
    Location *m_teleportLocations;
    int m_amountTeleport;
};
