#pragma once
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
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
	void findPlayersLocation(int);
	void playLevel(int);

	void runGame();
	int decideActivePlayer(int&);
	bool handleKeyBoardKey(int);
	void handleSpecialKey(int, int, int&);
	void movePlayerInBoard(int, int, int&, int, int, bool);

private:
	Board m_board;
	King m_King;
	Mage m_Mage;
	Thief m_Thief;
	Warrior m_Warrior;

};
