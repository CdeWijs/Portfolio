/*/
Rules:
1.	Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2.	Any live cell with two or three live neighbours lives on to the next generation.
3.	Any live cell with more than three live neighbours dies, as if by overcrowding.
4.	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
/*/

#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include "Grid.h"

void goToConsoleLine(int, int);

int main()
{
	// Create grid
	Grid grid;

	while (true)
	{
		// Create new grid
		grid.generateNext();
		goToConsoleLine(0, 0);
	}
	return 0;
}

void goToConsoleLine(int charNr, int lineNr)
{
	COORD coord{ (short)charNr, (short)lineNr };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}