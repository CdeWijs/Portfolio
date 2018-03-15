/*
This class handles the game logic.
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct CorrectLetterCount
{
	int CorrectPlaceCount = 0;
	int IncorrectPlaceCount = 0;
};

enum class GuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	NOT_CORRECT_LENGTH,
	INVALID_CHARACTERS,
};

enum class GameStatus
{
	WON,
	LOST
};

class WordGame
{
public:
	WordGame();

	int getMaxTries() const;
	int getCurrentTry() const;
	int getHiddenWordLength() const;
	GameStatus getGameStatus() const;

	GuessStatus checkInputValidity(std::string);
	CorrectLetterCount submitGuess(std::string);
	void reset();

private:
	const std::string HIDDEN_WORD = "teacup"; // Edit the word here!
	const int MAX_TRIES = 15;

	int maxTries;
	int currentTry;
	std::string hiddenWord;
	bool correctGuess;

	bool isIsogram(std::string) const;
};

