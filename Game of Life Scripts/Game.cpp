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
	ping_pong = 0;

	srand(time(NULL));
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			grids[ping_pong].cells[x][y] = (rand() % 2 ? 1 : 0);
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
			std::cout << std::setw(2) << display(grids[ping_pong].cells[x][y]);
		}
		std::cout << std::endl;
	}
	
	updateGrid(grids[ping_pong], grids[!ping_pong]);

	ping_pong = ping_pong == 0 ? 1 : 0;

}

void Game::updateGrid(const grid & prevGrid, grid & newGrid)
{
	// Count alive neighbours and change state of every cell
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			int totalNeighbours = checkNeighbours(x, y);
			newGrid.cells[x][y] = (isCellAlive(prevGrid.cells[x][y], totalNeighbours) ? 1 : 0);
		}
	}
}

int Game::checkNeighbours(int x, int y) const
{
	// Count how many neighbours are alive.
<<<<<<< HEAD
	int neighbours = grids[ping_pong].cells[x - 1][y - 1] + grids[ping_pong].cells[x][y - 1] + grids[ping_pong].cells[x + 1][y - 1] +
		grids[ping_pong].cells[x - 1][y] + grids[ping_pong].cells[x + 1][y] +
		grids[ping_pong].cells[x - 1][y + 1] + grids[ping_pong].cells[x][y + 1] + grids[ping_pong].cells[x + 1][y + 1];
=======
	int neighbours = grids[1].cells[x - 1][y - 1] + grids[1].cells[x][y - 1] + grids[1].cells[x + 1][y - 1] +
			 grids[1].cells[x - 1][y] + grids[1].cells[x + 1][y] +
			 grids[1].cells[x - 1][y + 1] + grids[1].cells[x][y + 1] + grids[1].cells[x + 1][y + 1];
>>>>>>> 35b1d9509eb7b6fe4c4ccb3b9c25c5e98f580f21

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
