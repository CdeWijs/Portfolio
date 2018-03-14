#include <time.h>
#include "Grid.h"

Grid::Grid()
{
	createCells();
	totalNeighbours = 0;
}

// Cells are only created once when a new grid is created
void Grid::createCells()
{
	srand(time(NULL));
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLUMNS; y++)
		{
			grid[x][y] = new Cell(x, y, (rand() % 2 ? State::DEAD : State::ALIVE));
		}
	}
}

void Grid::generateNext()
{
	// Display state of every cell
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLUMNS; y++)
		{
			std::cout << std::setw(2) << grid[x][y]->display();
		}
		std::cout << std::endl;
	}

	// Save state for every cell
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLUMNS; y++)
		{
			grid[x][y]->savePrevState();
		}
	}

	// Check neighbours of every cell
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLUMNS; y++)
		{
			checkNeighbours(grid[x][y]);
			updateCell(grid[x][y]);
		}
	}
}

void Grid::checkNeighbours(Cell* cell)
{
	int x = cell->getX();
	int y = cell->getY();
	int rows = ROWS - 1;
	int columns = COLUMNS - 1;
	totalNeighbours = 0;

	if (x > 0 && y > 0) // top left
	{
		if (grid[x - 1][y - 1]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}
	if (y > 0) // top mid
	{
		if (grid[x][y - 1]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}
	if (x < rows && y > 0) // top right
	{
		if (grid[x + 1][y - 1]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}
	if (x > 0) // left
	{
		if (grid[x - 1][y]->getState() == State::ALIVE)
		{+
			totalNeighbours++;
		}
	}
	if (x < rows) // right
	{
		if (grid[x + 1][y]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}	
	if (x > 0 && y < columns) // bottom left
	{
		if (grid[x - 1][y + 1]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}
	if (y < columns) // bottom mid
	{
		if (grid[x][y + 1]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}
	if (x < rows && y < columns) // bottom right
	{
		if (grid[x + 1][y + 1]->getState() == State::ALIVE)
		{
			totalNeighbours++;
		}
	}
}

void Grid::updateCell(Cell * cell)
{
	/*/
	Rules:
	1.	Any live cell with fewer than two live neighbours dies, as if caused by under-population.
	2.	Any live cell with two or three live neighbours lives on to the next generation.
	3.	Any live cell with more than three live neighbours dies, as if by overcrowding.
	4.	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
	/*/

	if (cell->getState() == State::ALIVE && totalNeighbours < 2)
	{
		cell->newState(State::DEAD);
	}
	else if (cell->getState() == State::ALIVE && totalNeighbours == 2 || totalNeighbours == 3)
	{
		cell->newState(State::ALIVE);
	}
	else if (cell->getState() == State::ALIVE && totalNeighbours > 3)
	{
		cell->newState(State::DEAD);
	}
	else if (cell->getState() == State::DEAD && totalNeighbours == 3)
	{
		cell->newState(State::ALIVE);
	}
}



