#pragma once

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
	ContinueAndSaveKey = 2,
	JumpToNext = 3,
	GameOver = 4
};

enum steps
{
	Up = -1,
	Down = 1,
	Left = -1,
	Right = 1
};