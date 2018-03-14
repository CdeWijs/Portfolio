#pragma once
#include <iostream>
#include <iomanip>
#include "Cell.h"

class Grid
{
public:
	Grid();

	static const int ROWS = 30;
	static const int COLUMNS = 30;

	// Create grid
	Cell* grid[ROWS][COLUMNS];

	// Create cells
	void createCells();
	void generateNext();

	// Create a new generation
	void checkNeighbours(Cell* cell);
	void updateCell(Cell * cell);

private:
	int totalNeighbours;
};

