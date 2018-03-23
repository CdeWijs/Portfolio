#include "stdafx.h"
#include <time.h>
#include "Grid.h"

Grid::Grid()
{
	init();
}

// Cells are only created once when a new grid is created
void Grid::init()
{
	srand(time(NULL));
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			grid[x][y] = (rand() % 2 ? 1 : 0);
		}
	}
}

void Grid::generateNext()
{
	// Display state of every cell
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			std::cout << std::setw(2) << display(grid[x][y]);
		}
		std::cout << std::endl;
	}

	// Save state for every cell
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			prevGrid[x][y] = grid[x][y];
		}
	}

	// Count alive neighbours and change state of every cell
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			int n = checkNeighbours(prevGrid[x][y], x, y);
			grid[x][y] = (isCellAlive(prevGrid[x][y], n) ? 1 : 0);
		}
	}
}

int Grid::checkNeighbours(char state, int x, int y) const
{
	// Count how many neighbours are alive.
	int neighbours = prevGrid[x - 1][y - 1] + prevGrid[x][y - 1] + prevGrid[x + 1][y - 1] + prevGrid[x - 1][y] + 
					 prevGrid[x + 1][y] + prevGrid[x - 1][y + 1] + prevGrid[x][y + 1] + prevGrid[x + 1][y + 1];

	return neighbours;
}

bool Grid::isCellAlive(char state, int neighbours) const
{
	if (state == 1)
	{
		return (neighbours == 2 || neighbours == 3);
	}
	else
	{
		return (neighbours == 3);
	}
}

char Grid::display(char state) const
{
	if (state == 1)
	{
		return 'O';
	}
	else
	{
		return '.';
	}
}
