/*
This class handles the game logic.
*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct CorrectLetterCount
{
	unsigned int CorrectPlaceCount = 0;
	unsigned int IncorrectPlaceCount = 0;
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
	unsigned int getHiddenWordLength() const;
	GameStatus getGameStatus(CorrectLetterCount count) const;

	GuessStatus checkInputValidity(const std::string&);
	CorrectLetterCount submitGuess(const std::string&);
	void reset();

private:
	const std::string HIDDEN_WORD = "teacup"; // Edit the word here!
	const int MAX_TRIES = 15;

	int maxTries;
	int currentTry;
	std::string hiddenWord;

	bool isIsogram(const std::string&) const;
};