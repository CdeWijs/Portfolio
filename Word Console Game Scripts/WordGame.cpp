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

GameStatus WordGame::getGameStatus() const
{
	if (correctGuess == true) { return GameStatus::WON; }
	else { return GameStatus::LOST; }
}

void WordGame::reset()
{
	currentTry = 1;
	maxTries = getMaxTries();
	hiddenWord = HIDDEN_WORD;
	correctGuess = false;
}

GuessStatus WordGame::checkInputValidity(std::string guess)
{
	if (!isIsogram(guess))
	{
		return GuessStatus::NOT_ISOGRAM;
	}
	else if (guess.length() != getHiddenWordLength())
	{
		return GuessStatus::NOT_CORRECT_LENGTH;
	}
	else
	{
		return GuessStatus::OK;
	}
}

// Receives a VALID guess, increments turn, and returns count
CorrectLetterCount WordGame::submitGuess(std::string guess)
{
	currentTry++;
	CorrectLetterCount count;

	// loop through all letters in the hidden word
	int wordLength = getHiddenWordLength();
	for (int i = 0; i < wordLength; i++)
	{
		// loop through all letters in the guess
		for (int j = 0; j < wordLength; j++)
		{
			// If letters match
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

	if (count.CorrectPlaceCount == wordLength)
	{
		correctGuess = true;
	}
	else
	{
		correctGuess = false;
	}

	return count;
}

bool WordGame::isIsogram(std::string guess) const
{
	// Create a map with all letters in the word
	std::map<char, bool> lettersInWord;
	for (char letter : guess)
	{
		// Make sure everything is lowercase
		letter = tolower(letter);

		// If a letter is already present in the map, the guess is not an isogram!
		if (lettersInWord[letter])
		{
			return false;
		}
		else
		{
			// Add the letter to the map
			lettersInWord[letter] = true;
		}
	}

	// If all letters are added to the map without problem, the word is an isogram
	return true;
}
