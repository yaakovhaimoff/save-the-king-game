#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#pragma once
#include <conio.h>
#include <Windows.h>

// include files
#include "Board.hpp"
#include "King.hpp"
#include "Mage.hpp"
#include "Thief.hpp"
#include "Warrior.hpp"
#include "gamesTools.hpp"


class Controller
{
public:
	Controller();
	void findPlayersLocation();
	void playLevel(bool&);
	void runGame(bool);
	int decideActivePlayer(int&);
	bool handleKeyBoardKey(int);
	void handleSpecialKey(int, int&);
	void movePlayerInBoard(int, int&, int, int);
	void restartMembersToNewLevel();

private:
	Board m_board;
	King m_King;
	Mage m_Mage;
	Thief m_Thief;
	Warrior m_Warrior;

};
