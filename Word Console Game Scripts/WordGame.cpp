#include "stdafx.h"
#include "WordGame.h"

WordGame::WordGame()
{
	reset();
}

int WordGame::getMaxTries() const
{
	return MAX_TRIES;
}

int WordGame::getCurrentTry() const
{
	return currentTry;
}

unsigned int WordGame::getHiddenWordLength() const
{
	return hiddenWord.length();
}

GameStatus WordGame::getGameStatus(CorrectLetterCount count) const
{

	return count.CorrectPlaceCount == getHiddenWordLength() ? GameStatus::Won : GameStatus::Lost;
}

void WordGame::reset()
{
	currentTry = 1;
	maxTries = getMaxTries();
	hiddenWord = HIDDEN_WORD;
}

GuessStatus WordGame::checkInputValidity(const std::string & guess)
{
	if (!isIsogram(guess))
	{
		return GuessStatus::NotIsogram;
	}
	else if (guess.length() != getHiddenWordLength())
	{
		return GuessStatus::NotCorrectLength;
	}
	else
	{
		return GuessStatus::OK;
	}
}

// Receives a VALID guess, increments turn, and returns count
CorrectLetterCount WordGame::submitGuess(const std::string & guess)
{
	currentTry++;
	CorrectLetterCount count;

	for (unsigned int i = 0; guess[i] != 0; i++)
	{
		if (hiddenWord[i] != 0)
		{
			// If chars match and they are in the same place
			if (guess[i] == hiddenWord[i])
			{
				count.CorrectPlaceCount++;
			}
			// If they are in the word, but in a different place
			else if (hiddenWord.find(guess[i]) != std::string::npos)
			{
				count.IncorrectPlaceCount++;
			}
		}
	}

	return count;
}

bool WordGame::isIsogram(const std::string & guess) const
{
	for (unsigned int i = 0; guess[i] != 0; i++)
	{
		unsigned int found = guess.find(guess[i]);
		// Check if this char isn't in another place in the word
		if (found != std::string::npos && found != i)
		{
			return false;
		}
	}

	return true;
}