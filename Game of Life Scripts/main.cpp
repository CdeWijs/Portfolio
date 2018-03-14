// main.cpp : Defines the entry point for the console application.

#include <iostream>
#include <windows.h>

#include "Grid.h"
#include "Cell.h"

void goToConsoleLine(int, int);

int main()
{
	// Create grid
	Grid* grid = new Grid;

	while (true)
	{
		// Update grid
		grid->generateNext();
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
