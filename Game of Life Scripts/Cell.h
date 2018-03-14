#pragma once
#include <iostream>
#include <ctime>
#include <string>

enum class State
{
	DEAD, 
/// OR
	ALIVE
};

class Cell
{
public:
	Cell(int x, int y, State state);

	State getState() const;
	int getX() const;
	int getY() const;

	void savePrevState();
	void newState(State s);
	
	char display() const;

private:
	const char DEAD_DISPLAY = '.';
	const char ALIVE_DISPLAY = 'O';

	int x;
	int y;

	State state;
	State prevState;

};

