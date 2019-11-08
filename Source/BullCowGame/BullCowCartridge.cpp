// Fill out your copyright notice in the Description page of Project Settings.
#include "./BullCowCartridge.h"
#include "HiddenWordList.h"

void	UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	SetupGame(); // Setting up game

	GetValidWords(HiddenWordList);
	PrintLine(FString::Printf(TEXT("The hidden word is: %s and it is %i characters long\n"), *HiddenWord, HiddenWord.Len())); // Debug Line
};

void	UBullCowCartridge::OnInput(const FString& Input) // When player hits "Enter"
{
	if (bGameOver) // Game loop
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input);
	}
};

void	UBullCowCartridge::SetupGame()
{
	// Initializing game state
	HiddenWord = TEXT("star");
	Lives = HiddenWord.Len();
	bGameOver = false;

	// Welcoming the player and prompt player for PlayerGuess
	PrintLine(TEXT("Welcome to the Bull Cow Game!"));
	PrintLine(FString::Printf(TEXT("Guess the %i letter isogram"), HiddenWord.Len()));
	PrintLine(FString::Printf(TEXT("You have %i Lives\nEnter your guess and press \"Enter\""), HiddenWord.Len()));
}

void	UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Please press enter to play again"));
}

void	UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord) // Checking PlayerGuess
	{
		PrintLine(TEXT("You won!"));
		EndGame();
		return;
	}
	if (!IsIsogram(Guess)) // Checking if PlayerGuess is an isogram
	{
		PrintLine(TEXT("No repeating letters"));
		return;
	}
	if (Guess.Len() != HiddenWord.Len()) // Check if PlayerGuess has the right number of characters
	{
		PrintLine(FString::Printf(TEXT("It is a %i letter word, try again"), HiddenWord.Len()));
		PrintLine(FString::Printf(TEXT("You have %i lives remaining"), Lives));
		return;
	}

	PrintLine(FString::Printf(TEXT("You lost a life... You now have %i lives"), --Lives));

	if (Lives <= 0)
	{
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	PrintLine(TEXT("Trying guessing again, you have %i lives left"), Lives);
}

bool	UBullCowCartridge::IsIsogram(FString Guess) const
{
	for (int32 Index = 0; Index < Guess.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Guess.Len(); Comparison++)
		{
			if (Guess[Index] == Guess[Comparison])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString>	UBullCowCartridge::GetValidWords(TArray<FString> Words) const
{
	TArray<FString> ValidWords;
	
	for (int32 Index = 0; Index < Words.Num(); Index++)
	{
		if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8 && IsIsogram(Words[Index]))
		{
			ValidWords.Emplace(Words[Index]);
		}
	}
	PrintLine(FString::Printf(TEXT("%i words selected"), ValidWords.Num()));
	return ValidWords;
}
