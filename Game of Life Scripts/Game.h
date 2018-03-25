#pragma once
#include <iostream>
#include <iomanip>

static const int ROWS = 32;
static const int COLUMNS = 32;

struct grid
{
	char cells[ROWS][COLUMNS];
};

class Game
{
public:
	Game();

	// Create grid
	grid grids[2] = {};
	void init();

	// Create new generation
	void generateNext();
	void updateGrid(const grid& inPrevGrid, grid& inNewGrid);
	int checkNeighbours(int x, int y) const;
	bool isCellAlive(char state, int neighbours) const;

	char display(char state) const;
};