#pragma once
#include <iostream>
#include <iomanip>

class Grid
{
public:
	Grid();

	static const int ROWS = 32;
	static const int COLUMNS = 32;

	// Create grid
	char grid[ROWS][COLUMNS];
	char prevGrid[ROWS][COLUMNS];
	void init();

	// Create new generation
	void generateNext();
	int checkNeighbours(char state, int x, int y) const;
	bool isCellAlive(char state, int neighbours) const;

	char display(char state) const;
};

