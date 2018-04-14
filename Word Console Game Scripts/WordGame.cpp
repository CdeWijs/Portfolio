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

int WordGame::getHiddenWordLength() const
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

	int wordLength = getHiddenWordLength();

	// Loop over all chars in guess
	for (int i = 0; i < guess.length(); i++)
	{
		// Loop over all chars in the hidden word
		for (int j = 0; j < wordLength; j++)
		{
			// Bounds check in case the hidden word is shorter than guess
			if (i <= wordLength)
			{
				// If chars match
				if (guess[i] == hiddenWord[j])
				{
					// If they're in the same place
					if (i == j)
					{
						count.CorrectPlaceCount++;
					}
					// If they are in the word, but in a different place
					else
					{
						count.IncorrectPlaceCount++;
					}
				}
			}
		}
	}

	return count;
}

bool WordGame::isIsogram(const std::string & guess) const
{
	int wordLength = getHiddenWordLength();
	// Loop over all chars in guess
	for (int i = 0; i < guess.length(); i++)
	{
		for (int j = 0; j < guess.length(); j++)
		{
			// If chars match on a different place in the word
			if (i != j && guess[i] == guess[j])
			{
				return false;
			}
		}
	}

	return true;
}