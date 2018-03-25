#include "stdafx.h"
#include <time.h>
#include "Game.h"

Game::Game()
{
	init();
}

// Cells are only created once when a new grid is created
void Game::init()
{
	srand(time(NULL));
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			grids[0].cells[x][y] = (rand() % 2 ? 1 : 0);
		}
	}
}

void Game::generateNext()
{
	// Note: the outer edge of the grid is being skipped, so the state of the neighbours
	// can be checked without having to do bound checks for each one of them.

	// Display state of every cell
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			std::cout << std::setw(2) << display(grids[0].cells[x][y]);
		}
		std::cout << std::endl;
	}

	// Save state for every cell
	bool ping_pong = true;
	if (ping_pong)
	{
		updateGrid(grids[0], grids[1]);
	}
	else
	{
		updateGrid(grids[1], grids[0]);
	}
	ping_pong = !ping_pong;

	// Count alive neighbours and change state of every cell
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			int totalNeighbours = checkNeighbours(x, y);
			grids[0].cells[x][y] = (isCellAlive(grids[1].cells[x][y], totalNeighbours) ? 1 : 0);
		}
	}
}

void Game::updateGrid(const grid & inPrevGrid, grid & inNewGrid)
{
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			inNewGrid.cells[x][y] = inPrevGrid.cells[x][y];
		}
	}

	//inNewGrid.cells[0][0] = inPrevGrid.cells[0][0];
}

int Game::checkNeighbours(int x, int y) const
{
	// Count how many neighbours are alive.
	int neighbours = grids[1].cells[x - 1][y - 1] + grids[1].cells[x][y - 1] + grids[1].cells[x + 1][y - 1] +
			 grids[1].cells[x - 1][y] + grids[1].cells[x + 1][y] +
			 grids[1].cells[x - 1][y + 1] + grids[1].cells[x][y + 1] + grids[1].cells[x + 1][y + 1];

	return neighbours;
}

bool Game::isCellAlive(char state, int neighbours) const
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

char Game::display(char state) const
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
