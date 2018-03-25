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

// Create new generation
void Game::generateNext()
{
	// Note: the outer edge of the grid is not being drawn or updated, so the state of the 
	// neighbours can be checked without having to do bound checks for each one of them.

	drawGrid(grids[ping_pong]);

	const int prev_idx = ping_pong;
	ping_pong = (ping_pong == 0) ? 1 : 0; // Flip buffer
	const int current_idx = ping_pong;

	updateGrid(grids[prev_idx], grids[current_idx]);
}

// Display state of every cell.
void Game::drawGrid(const grid& newGrid)
{
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			std::cout << std::setw(2) << display(newGrid.cells[x][y]);
		}
		std::cout << std::endl;
	}
}

// Count alive neighbours and change state of every cell.
void Game::updateGrid(const grid & prevGrid, grid & newGrid)
{
	for (int x = 1; x < ROWS - 1; x++)
	{
		for (int y = 1; y < COLUMNS - 1; y++)
		{
			int totalNeighbours = checkNeighbours(prevGrid, x, y);
			newGrid.cells[x][y] = (isCellAlive(prevGrid.cells[x][y], totalNeighbours) ? 1 : 0);
		}
	}
}

// Count how many neighbours are alive.
int Game::checkNeighbours(const grid & prevGrid, int x, int y) const
{
	int neighbours = prevGrid.cells[x - 1][y - 1] + prevGrid.cells[x][y - 1] + prevGrid.cells[x + 1][y - 1] +
			 prevGrid.cells[x - 1][y] + prevGrid.cells[x + 1][y] +
			 prevGrid.cells[x - 1][y + 1] + prevGrid.cells[x][y + 1] + prevGrid.cells[x + 1][y + 1];

	return neighbours;
}

// Check if cell should be alive or dead, according to their neighbours.
bool Game::isCellAlive(char currentState, int neighbours) const
{
	if (currentState == 1) // alive
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
	if (state == 1) // alive
	{
		return 'O';
	}
	else
	{
		return '.';
	}
}