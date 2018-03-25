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

	void init();
	void generateNext();

private:
	// Create two buffers of grid
	grid grids[2] = {};

	void drawGrid(const grid& newGrid);
	void updateGrid(const grid& prevGrid, grid& newGrid);

	int checkNeighbours(const grid& prevGrid, int x, int y) const;
	bool isCellAlive(char currentState, int neighbours) const;
	char display(char state) const;

	int ping_pong;
};