#pragma onces
#include "FBullCowGame.h"
#include <map>


// to make syntax Unreal Friendly
#define Tmap std::map 
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();

}

void FBullCowGame::Reset()
{	
	constexpr int32 MAX_Tries = 3;
	const FString HIDDEN_WORD = "planet"; //This MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}

// Receives a VALID guess, increments turn, and returns count.


int FBullCowGame::GetMaxTries()const
{
	Tmap <int32, int32> WordLengthToMaxTries{ {3,4},{4,7} ,{5,10}, {6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const
{

	return bGameIsWon;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsgram(Guess)) // if the guess is not an isogram
	{
		
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))// if the guess isnt all lower case return an error. 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length()!= GetHiddenWordLength()) // if the guess length is wrong. 
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK; //otherwise, return Ok.
	}
	
	

}
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	//Loops through all letters in hidden word.
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{	//compare letters againt guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}

			}
			
		}
	}
	if (BullCowCount.Bulls== WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsgram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	//Setup map
	Tmap <char, bool> Letterseen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (Letterseen[Letter])//if the letter is in the map
		{
			return false; //we dont have an isogram
		}
		else
		{
			Letterseen[Letter] = true; //add letter to the map as seen
		}

	}
	return true; // for exampe in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{	
	for (auto Letter : Word) 
	{
		
		if (!islower(Letter))
		{
			return false;
		}
			
	}
	return true;
}
