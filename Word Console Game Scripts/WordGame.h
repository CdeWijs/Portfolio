/*
This class handles the game logic.
*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

struct CorrectLetterCount
{
	int CorrectPlaceCount = 0;
	int IncorrectPlaceCount = 0;
};

enum class GuessStatus
{
	Invalid,
	OK,
	NotIsogram,
	NotCorrectLength,
	InvalidCharacters,
};

enum class GameStatus
{
	Won,
	Lost
};

class WordGame
{
public:
	WordGame();

	int getMaxTries() const;
	int getCurrentTry() const;
	int getHiddenWordLength();
	GameStatus getGameStatus(const CorrectLetterCount count);

	GuessStatus checkInputValidity(std::string&) const;
	CorrectLetterCount submitGuess(std::string&);
	void reset();

private:
	const std::string HIDDEN_WORD = "teacup"; // Edit the word here!
	const int MAX_TRIES = 15;

	int maxTries;
	int currentTry;
	std::string hiddenWord;

	bool isIsogram(std::string&) const;
};