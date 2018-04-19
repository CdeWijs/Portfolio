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

int WordGame::getHiddenWordLength()
{
	int length = 0;
	for (std::string::iterator it = hiddenWord.begin(); it < hiddenWord.end(); it++)
	{
		length++;
	}
	return length;
}

GameStatus WordGame::getGameStatus(const CorrectLetterCount count) 
{
	return count.CorrectPlaceCount == getHiddenWordLength() ? GameStatus::Won : GameStatus::Lost;
}

void WordGame::reset()
{
	currentTry = 1;
	maxTries = getMaxTries();
	hiddenWord = HIDDEN_WORD;
}

GuessStatus WordGame::checkInputValidity(std::string & guess) const
{
	if (!isIsogram(guess))
	{
		return GuessStatus::NotIsogram;
	}
	else if (guess.length() != hiddenWord.length())
	{
		return GuessStatus::NotCorrectLength;
	}
	else
	{
		return GuessStatus::OK;
	}
}

// Receives a VALID guess, increments turn, and returns count
CorrectLetterCount WordGame::submitGuess(std::string & guess)
{
	currentTry++;
	CorrectLetterCount count;

	int index = 0;
	for (std::string::iterator it = guess.begin(); it < guess.end(); it++)
	{
		if (hiddenWord[index] != '/0')
		{
			// If chars match and they are in the same place
			if (*it == hiddenWord[index])
			{
				count.CorrectPlaceCount++;
			}
			// If they are in the word, but in a different place
			else if (hiddenWord.find(*it) != std::string::npos)
			{
				count.IncorrectPlaceCount++;
			}
		}

		index++;
	}

	return count;
}

bool WordGame::isIsogram(std::string & guess) const
{
	int index = 0;
	for (std::string::iterator it = guess.begin(); it < guess.end(); it++)
	{
		int found = guess.find(*it);
		// Check if this char isn't in another place in the word
		if (found != std::string::npos && found != index)
		{
			return false;
		}

		index++;
	}

	return true;
}