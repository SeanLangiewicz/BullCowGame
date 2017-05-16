/* This is the console excutable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction for gamle logic see the FBullCowGame class.
*/
#pragma once
// Pre-Processor Directive
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = FString;
using int32 = int;

// Function Prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;// Instantiate a new game, which we re-use across plays


// Entry point for the application
int main()
{
	bool bPlayAgain = false;
	do
	{
		
	PrintIntro();
	PlayGame();
	
	bPlayAgain = AskToPlayAgain();
	
	} while (bPlayAgain);

	return 0; // Exit Application

}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game. \n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std:: cout << " letter isogram I'm thinking of ?\n";
	
	return;
}

//Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std:: cout<<"Your Max number of tries is " << MaxTries << std::endl;
	
	// Loop number of guesses while the game is 
	// NOT won and there are stil tries rema
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	 
	{
		FText Guess = GetValidGuess();

		//Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount =  BCGame.SubmitValidGuess(Guess);

		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


//Loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{

	
	//Get a guess from the player
	int32 MyCurrentTry = BCGame.GetCurrentTry();
	std::cout << " \nCurrent Try " << MyCurrentTry << " of " << BCGame.GetMaxTries();
	std::cout << " Enter your guess :";
	
	getline(std::cin, Guess);

	Status = BCGame.CheckGuessValidity(Guess);
	
	switch (Status)
	{
	case EGuessStatus::OK:
		std::cout << "Valid guess !\n\n";
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "Please enter a word without repeating letters.\n\n";
		break;
	case EGuessStatus::Wrong_Length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "Please enter lower case word.\n\n";
		break;
	default:
		//assume the guess is valid
		break;
	}
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors.
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again  with the same hidden word ( Y / N)?";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary ()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE YOU WIN !\n\n";
	}
	else
	{
		std::cout << "Better luck next time\n";
	}
}
