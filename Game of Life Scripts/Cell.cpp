#include "Cell.h"

Cell::Cell(int x, int y, State state)
{
	this->x = x;
	this->y = y;
	this->state = state;
}

State Cell::getState() const
{
	return prevState;
}

int Cell::getX() const
{
	return x;
}

int Cell::getY() const
{
	return y;
}

void Cell::savePrevState()
{
	prevState = state;
}

void Cell::newState(State s)
{
	state = s;
}

char Cell::display() const
{
	if (state == State::DEAD){
		return DEAD_DISPLAY;
	}
	else {
		return ALIVE_DISPLAY;
	}
}
