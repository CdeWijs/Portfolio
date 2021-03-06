/*
This is the console executable, that makes use of the BullCow class.
This acts as the View in a MVC pattern, and is responsible for all
user interaction. For game logic see the BullCowGame class.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "WordGame.h"

void printIntro();
void playGame();
std::string getValidGuess();
void printOutcome(CorrectLetterCount count);
bool askToPlayAgain();

WordGame wordGame;

int main()
{
	// Repeat the game as long as the player wants
	bool playAgain = false;
	do
	{
		printIntro();
		playGame();
		playAgain = askToPlayAgain();
	} while (playAgain == true);

	return 0;
}

void printIntro()
{
	const int WORD_LENGTH = wordGame.getHiddenWordLength();

	std::cout << "--------------------------------------" << std::endl;
	std::cout << "| Welcome to the Word Console Game!  |" << std::endl;
	std::cout << "| I challenge you! Can you guess the |" << std::endl;
	std::cout << "| " << WORD_LENGTH << " letter isogram I'm thinking of?  |" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << std::endl;
}

void playGame()
{
	wordGame.reset();
	int maxTries = wordGame.getMaxTries();

	CorrectLetterCount correctLetterCount;

	// Ask for the player's guess while the game is NOT won...
	// and there are still tries remaining.
	while (wordGame.getGameStatus(correctLetterCount) != GameStatus::Won && wordGame.getCurrentTry() <= maxTries)
	{
		std::string guess = getValidGuess();

		// Submit valid guess to the game, and receive counts
		correctLetterCount = wordGame.submitGuess(guess);

		std::cout << "Correct letters in the right position = " << correctLetterCount.CorrectPlaceCount << std::endl;
		std::cout << "Correct letters in the wrong position = " << correctLetterCount.IncorrectPlaceCount << "\n\n";
	}

	printOutcome(correctLetterCount);
}

// Loop until the user gives a valid guess
std::string getValidGuess()
{
	std::string guess = "";
	GuessStatus status = GuessStatus::Invalid;

	do
	{
		int currentTry = wordGame.getCurrentTry();
		std::cout << "Try " << currentTry << " of " << wordGame.getMaxTries();
		std::cout << " . Enter your guess: ";

		// Get the guess from the player
		std::getline(std::cin, guess);

		status = wordGame.checkInputValidity(guess);
		switch (status)
		{
			case GuessStatus::NotIsogram:
				std::cout << "Your input isn't an isogram! Each letter can only appear once in the word." << std::endl;
				break;
			case GuessStatus::NotCorrectLength:
				std::cout << "Your input isn't the correct word length! ";
				std::cout << "Please enter a word of " << wordGame.getHiddenWordLength() << " letters." << std::endl;
				break;
			case GuessStatus::InvalidCharacters:
				std::cout << "Your input contains invalid characters. Please only use letters of the alphabet." << std::endl;
				break;
			default:
				break; // Assume the guess is valid
		}
	} while (status != GuessStatus::OK);
	return guess;
}

void printOutcome(CorrectLetterCount count)
{
	if (wordGame.getGameStatus(count) == GameStatus::Won)
	{
		std::cout << "Congratulations! You guessed the word! \n" << std::endl;
	}
	else
	{
		std::cout << "Unfortunately you didn't guess the word. Better luck next time.\n" << std::endl;
	}
}

bool askToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)" << std::endl;

	std::string input = "";
	getline(std::cin, input);
	std::cout << std::endl;

	return (input[0] == 'y' || input[0] == 'Y');
}