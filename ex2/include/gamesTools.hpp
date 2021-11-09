#pragma once

const int amountOfLevels = 3;
const int numOfPlayers = 4;

enum gameTools
{
	GateKey = 70,
	Fire = 42,
	Teleport = 88,
	Throne = 64,
	Tile = 33,
	Gate = 35,
	Space = 32,
	Wall = 61
};

enum gameMoves
{
	DontDoNothing = 0,
	ContinueAndDelete = 1,
	StepAndSaveKey = 2,
	JumpToNext = 3,
	ThiefHasKey = 4,
	GameOver = 5
};

enum steps
{
	Up = -1,
	Down = 1,
	Left = -1,
	Right = 1
};

enum playersKeys
{
	KING = 75,      // 'K'
	MAGE = 77,     // 'M'
	WARRIOR = 87, // 'W'
	THIEF = 84    // 'T'
};

enum Keys
{
	PlayersKey = 112,
	KB_Escape = 27,
	SpecialKey = 224,
};

enum SpecialKeys
{
	KB_Up = 72,
	KB_Down = 80,
	KB_Left = 75,
	KB_Right = 77,
};