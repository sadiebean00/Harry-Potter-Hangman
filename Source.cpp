/*This is my hangman coursework. The theme for this game is Harry Potter. There are five different levels the player can pick from which include Hogwarts Lessons,
Creatures, Location, Ultimate Nerd, and Equipment.

The inputs include the choice input for the menu, so whether the player wants to play the game, select the level,, view the instructions, or exit. Another input is 
the letter that the player is guessing during the game. 

The processes is the method that the computer takes when the game is running. The computer asks for a letter
and the player inputs a letter. The system then reads what letter has been inputted and scans the word to see whether the letter is present. If the letter is 
present in the word, the system places it back in the underscore. If the letter is not present, the system draws the first gallow process by calling the drawGallow
function and seeing how many guesses have been taken. The system also increments the guessesTaken variable by one. Once the player has reached 6 guesses, the game
will end.

The outputs for this game include seeing the different states of execution, as well as the final word being outputted to the user.*/
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <cmath>
#include <iomanip>
#include <time.h>
#include <cctype>
#include <cstring>

int menu();
int guessesTaken = 0;
bool level_select();
bool play_Creatures_Level();
bool play_Hogwars_Lesson_Level();
bool play_Location_Level();
bool play_Ultimate_Nerd_Level();
bool play_Equipment_Level();
void instructions();
void exit_game();
void displayUnderscore(char[], char[]);
bool guessed = false;
int lettersGuessed(char, char[], char[]);
void drawGallows();
const int MAX_TRIES = 6;

int main()
{
	system("CLS");
	bool exit_flag = false;
	int option = 0;

	while (exit_flag == false)
	{
		option = menu();
		std::cout << "\nChoice " << option << " Selected\n";
		switch (option)
		{
			case 1:
			{
				system("CLS");
				std::cout << "Harry Potter Hangman Game selected!\n";
				bool result = level_select();
				option = 0;
				if (result == true)
				{
					std::cout << "Congratulations you won and beat the death eaters!\n";
				}
				else
				{
					std::cout << "Hard luck, the death eaters defeated you!\n";
				}
				exit_flag = false;
				break;
			}
			case 2:
			{
				instructions();
				exit_flag = false;
				option = 0;
				break;
			}
			case 3:
			{
				exit_game();
				exit_flag = true;
				option = 0;
				break;
			}
			default:
			{
				std::cout << "There has been an error with the Muggle technology... Exiting now\n";
				exit_flag = true;
				break;
			}
		}
	}
	std::cin.get();
	return 0;
}

int menu()
{
	system("CLS");
	int choice = 0;
	bool test = false;

	do {
		system("CLS");
		std::cout << "HARRY POTTER AND THE MYSTERIOUS HANGMAN GAME!\n";
		std::cout << "Please Select Our Option from the Menu\n";
		std::cout << "--------------------------------------\n";
		std::cout << "Play Harry Potter and the Mysterious Hangman Game - Press 1 \n";
		std::cout << "See the Instructions for the game - Press 2 \n";
		std::cout << "Exit the game - Press 3 \n";
		std::cout << "Choice -> ";
		std::cin >> choice;

		if ((choice > 3) || (choice < 0))
		{
			system("CLS");
			test = false;
			std::cout << "Please select a valid number of 1, 2, or 3!\n";
			Sleep(2000);
		}
		else
		{
			test = true;
		}
	} while (test == false);
	return (choice);
}

bool level_select()
{
	system("CLS");
	
	bool exit_flag = false;
	int choice = 0;

	while (exit_flag == false)
	{
		std::cout << "Select a Level to Play! " << std::endl;
		std::cout << "1. Hogwarts Lessons Level - Guess the Hogwarts lessons!" << std::endl;
		std::cout << "2. Creatures Level - Guess the Harry Potter creatures!" << std::endl;
		std::cout << "3. Equipment Level - Guess the Harry Potter equipment like wands and broomsticks!" << std::endl;
		std::cout << "4. Locations Level - Guess the Harry Potter locations!" << std::endl;
		std::cout << "5. Ultimate Nerd Level - The hardest level of them all!" << std::endl;
		std::cout << "Enter a choice: " << std::endl;
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				system("CLS");
				std::cout << "Hogwarts Lessons Level Selected!" << std::endl;
				bool result = play_Hogwars_Lesson_Level();
				exit_flag = false;
				choice = 0;
				break;
			}
			case 2:
			{
				system("CLS");
				std::cout << "Creatures Level Selected!" << std::endl;
				bool result = play_Creatures_Level();
				exit_flag = false;
				choice = 0;
				break;
			}
			case 3:
			{
				system("CLS");
				std::cout << "Equipment Level Selected!" << std::endl;
				bool result = play_Equipment_Level();
				exit_flag = false;
				choice = 0;
				break;
			}
			case 4:
			{
				system("CLS");
				std::cout << "Locations Level Selected!" << std::endl;
				bool result = play_Location_Level();
				exit_flag = false;
				choice = 0;
				break;
			}
			case 5:
			{
				system("CLS");
				std::cout << "The Ultimate Nerd Level has been picked, are you ready?" << std::endl;
				bool result = play_Ultimate_Nerd_Level();
				exit_flag = false;
				choice = 0;
				break;
			}
			default:
			{
				std::cout << "There has been an error with the Muggle technology... Exiting now\n";
				exit_flag = true;
				break;
			}
		}
	}
	std::cin.get();
	return 0;
}

bool play_Hogwars_Lesson_Level()
{
	system("CLS");

	char _words[6][30] = {"potions", "charms", "transfiguration", "herbology", "flying", "divination" };
	char hidden_word[30]{ 0 };
	char unknown_word[30];
	int wordLength;
	char guess;

	std::cout << "Guesses Taken: " << guessesTaken << std::endl;

	srand(time(NULL));

	int i = rand() % 6;
	strcpy_s(hidden_word, _words[i]);
	
	displayUnderscore(hidden_word, unknown_word);

	bool Gameover = false;

	while (guessesTaken < MAX_TRIES)
	{
		std::cout << "\n\n" << unknown_word << std::endl;
		std::cout << "\nGuess a letter: " << std::endl;
		std::cin >> guess;

		if (lettersGuessed(guess, hidden_word, unknown_word) == 0)
		{
			drawGallows();
			guessesTaken++;
		}
		else
		{
			std::cout << "\nYay, you've found a letter!" << std::endl;
		}
		
		std::cout << "\nGuesses Taken: " << guessesTaken << std::endl;
		std::cout << "\nYou have: " << MAX_TRIES - guessesTaken << " guesses left\n" << std::endl;

		if (strcmp(hidden_word, unknown_word) == 0)
		{
			std::cout << "\nWell done! The word was: " << hidden_word << std::endl;
			std::cout << "\nYou have defeated the Death Eaters!\n" << std::endl;
			guessesTaken = 0;
			break;
		}
	}

	if (guessesTaken == MAX_TRIES)
	{
		std::cout << "\nSorry, the Death Eaters have gotten you!" << std::endl;
		std::cout << "\nThe word was: \n" << hidden_word << std::endl;
		guessesTaken = 0;
	}
	
	system("PAUSE");
	return menu();
}

bool play_Creatures_Level()
{
	system("CLS");

	char _words[6][30] = { "owl", "goblin", "phoenix", "basiisk", "niffler", "troll" };
	char hidden_word[30]{ 0 };
	char unknown_word[30];
	int wordLength;
	char guess;

	std::cout << "Guesses Taken: " << guessesTaken << std::endl;

	srand(time(NULL));

	int i = rand() % 6;
	strcpy_s(hidden_word, _words[i]);

	displayUnderscore(hidden_word, unknown_word);

	bool Gameover = false;

	while (guessesTaken < MAX_TRIES)
	{
		std::cout << "\n\n" << unknown_word << std::endl;
		std::cout << "\nGuess a letter: " << std::endl;
		std::cin >> guess;

		if (lettersGuessed(guess, hidden_word, unknown_word) == 0)
		{
			drawGallows();
			guessesTaken++;
		}
		else
		{
			std::cout << "\nYay, you've found a letter!" << std::endl;
		}

		std::cout << "\nGuesses Taken: " << guessesTaken << std::endl;
		std::cout << "\nYou have: " << MAX_TRIES - guessesTaken << " guesses left\n" << std::endl;

		if (strcmp(hidden_word, unknown_word) == 0)
		{
			std::cout << "\nWell done! The word was: " << hidden_word << std::endl;
			std::cout << "\nYou have defeated the Death Eaters!\n" << std::endl;
			guessesTaken = 0;
			break;
		}
	}

	if (guessesTaken == MAX_TRIES)
	{
		std::cout << "\nSorry, the Death Eaters have gotten you!" << std::endl;
		std::cout << "\nThe word was: \n" << hidden_word << std::endl;
		guessesTaken = 0;
	}

	system("PAUSE");
	return menu();
}

bool play_Equipment_Level()
{
	system("CLS");

	char _words[6][30] = { "wand", "broomstick", "snitch", "rememberall", "cauldron", "horcrux" };
	char hidden_word[30]{ 0 };
	char unknown_word[30];
	int wordLength;
	char guess;

	std::cout << "Guesses Taken: " << guessesTaken << std::endl;

	srand(time(NULL));

	int i = rand() % 6;
	strcpy_s(hidden_word, _words[i]);

	displayUnderscore(hidden_word, unknown_word);

	bool Gameover = false;

	while (guessesTaken < MAX_TRIES)
	{
		std::cout << "\n\n" << unknown_word << std::endl;
		std::cout << "\nGuess a letter: " << std::endl;
		std::cin >> guess;

		if (lettersGuessed(guess, hidden_word, unknown_word) == 0)
		{
			drawGallows();
			guessesTaken++;
		}
		else
		{
			std::cout << "\nYay, you've found a letter!" << std::endl;
		}

		std::cout << "\nGuesses Taken: " << guessesTaken << std::endl;
		std::cout << "\nYou have: " << MAX_TRIES - guessesTaken << " guesses left\n" << std::endl;

		if (strcmp(hidden_word, unknown_word) == 0)
		{
			std::cout << "\nWell done! The word was: " << hidden_word << std::endl;
			std::cout << "You have defeated the Death Eaters!\n" << std::endl;
			guessesTaken = 0;
			break;
		}
	}

	if (guessesTaken == MAX_TRIES)
	{
		std::cout << "\nSorry, the Death Eaters have gotten you!" << std::endl;
		std::cout << "\nThe word was: \n" << hidden_word << std::endl;
		guessesTaken = 0;
	}

	system("PAUSE");
	return menu();
}

bool play_Location_Level()
{
	system("CLS");

	char _words[6][30] = { "hogwarts", "diagon", "burrow", "knockturn", "hogsmeade", "ministry" };
	char hidden_word[30]{ 0 };
	char unknown_word[30];
	int wordLength;
	char guess;

	std::cout << "Guesses Taken: " << guessesTaken << std::endl;

	srand(time(NULL));

	int i = rand() % 6;
	strcpy_s(hidden_word, _words[i]);

	displayUnderscore(hidden_word, unknown_word);

	bool Gameover = false;

	while (guessesTaken < MAX_TRIES)
	{
		std::cout << "\n\n" << unknown_word << std::endl;
		std::cout << "\nGuess a letter: " << std::endl;
		std::cin >> guess;

		if (lettersGuessed(guess, hidden_word, unknown_word) == 0)
		{
			drawGallows();
			guessesTaken++;
		}
		else
		{
			std::cout << "\nYay, you've found a letter!" << std::endl;
		}

		std::cout << "\nGuesses Taken: " << guessesTaken << std::endl;
		std::cout << "\nYou have: " << MAX_TRIES - guessesTaken << " guesses left\n" << std::endl;

		if (strcmp(hidden_word, unknown_word) == 0)
		{
			std::cout << "\nWell done! The word was: " << hidden_word << std::endl;
			std::cout << "\nYou have defeated the Death Eaters!\n" << std::endl;
			guessesTaken = 0;
			break;
		}
	}

	if (guessesTaken == MAX_TRIES)
	{
		std::cout << "\nSorry, the Death Eaters have gotten you!" << std::endl;
		std::cout << "\nThe word was: \n" << hidden_word << std::endl;
		guessesTaken = 0;
	}

	system("PAUSE");
	return menu();
}

bool play_Ultimate_Nerd_Level()
{
	system("CLS");

	char _words[6][30] = { "winky", "peeves", "expelliarmus", "bagman", "firewhisky", "gobstones" };
	char hidden_word[30]{ 0 };
	char unknown_word[30];
	int wordLength;
	char guess;

	std::cout << "Guesses Taken: " << guessesTaken << std::endl;

	srand(time(NULL));

	int i = rand() % 6;
	strcpy_s(hidden_word, _words[i]);

	displayUnderscore(hidden_word, unknown_word);

	bool Gameover = false;

	while (guessesTaken < MAX_TRIES)
	{
		std::cout << "\n\n" << unknown_word << std::endl;
		std::cout << "\nGuess a letter: " << std::endl;
		std::cin >> guess;

		if (lettersGuessed(guess, hidden_word, unknown_word) == 0)
		{
			drawGallows();
			guessesTaken++;
		}
		else
		{
			std::cout << "\nYay, you've found a letter!" << std::endl;
		}

		std::cout << "\nGuesses Taken: " << guessesTaken << std::endl;
		std::cout << "\nYou have: " << MAX_TRIES - guessesTaken << " guesses left\n" << std::endl;

		if (strcmp(hidden_word, unknown_word) == 0)
		{
			std::cout << "\nWell done! The word was: " << hidden_word << std::endl;
			std::cout << "\nYou have defeated the Death Eaters!\n" << std::endl;
			guessesTaken = 0;
			break;
		}
	}

	if (guessesTaken == MAX_TRIES)
	{
		std::cout << "\nSorry, the Death Eaters have gotten you!" << std::endl;
		std::cout << "\nThe word was: \n" << hidden_word << std::endl;
		guessesTaken = 0;
	}

	system("PAUSE");
	return menu();
}

void drawGallows()
{
	switch (guessesTaken)
	{
	case 1:
	{
		std::cout << "----------" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "----------" << std::endl;
		break;
	}
	case 2:
	{
		std::cout << "----------" << std::endl;
		std::cout << "|		   |" << std::endl;
		std::cout << "|		  ()" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "----------" << std::endl;
		break;
	}
	case 3:
	{
		std::cout << "----------" << std::endl;
		std::cout << "|		   |" << std::endl;
		std::cout << "|		  ()" << std::endl;
		std::cout << "|		   |-" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "----------" << std::endl;
		break;
	}
	case 4:
	{
		std::cout << "----------" << std::endl;
		std::cout << "|		   |" << std::endl;
		std::cout << "|		  ()" << std::endl;
		std::cout << "|		  -|-" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "----------" << std::endl;
		break;
	}
	case 5:
	{
		std::cout << "----------" << std::endl;
		std::cout << "|		   |" << std::endl;
		std::cout << "|		  ()" << std::endl;
		std::cout << "|		  -|-" << std::endl;
		std::cout << "|		   '\'" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "----------" << std::endl;
		break;
	}
	case 6:
	{
		std::cout << "-------------" << std::endl;
		std::cout << "|		      |" << std::endl;
		std::cout << "|		     ()" << std::endl;
		std::cout << "|		     -|-" << std::endl;
		std::cout << "|		    '/\'" << std::endl;
		std::cout << "|" << std::endl;
		std::cout << "------------" << std::endl;
		break;
	}
	return;
	}
}

int lettersGuessed(char guess, char secret_word[], char word_guessed[])
{
	int i;
	int matches = 0;

	for (i = 0; secret_word[i] != '\0'; i++)
	{
		if (guess == word_guessed[i])
			return 0;
		if (guess == secret_word[i])
		{
			word_guessed[i] = guess;
			matches++;
		}
	}
	return matches;
}

void displayUnderscore(char hidden_word[], char unknown_word[])
{
	int i;
	int length = strlen(hidden_word);
	for (i = 0; i < length; i++)
	unknown_word[i] = '_';
	unknown_word[i] = '\0';
}

void instructions()
{
	system("CLS");
	std::cout << "To play, just guess the Harry Potter related word!\n";
	std::cout << "You have a choice of 5 levels, each with Harry Potter related words!\n";
	std::cout << "The First Level is Hogwarts Lessons and the words are potions, herbology, charms, transfiguration, flying, and divination\n";
	std::cout << "The Second Level is Creatures and the words are owl, goblin, basilisk, troll, niffler, and phoenix\n";
	std::cout << "The Third Level is Equipment and the words are broomstick, wand, snitch, rememberall, cauldron, and horcrux\n";
	std::cout << "The Fourth Level is Locations and the words are ministry, diagon, knocturn, burrow, and hogwarts\n";
	std::cout << "The Fifth Level is the Ultimate Nerd Level and the words are firewhisky, gobstones, winky, peeves, bagman, and expelliarmus\n";
	std::cout << "You have 6 tries to try and get all of the words before the Death Eaters win!\n";
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::cin.get();
	return;
}

void exit_game()
{
	system("CLS");
	std::cout << "You have chosen the exit. Preparing to disaparate back into the Muggle world!\n";
	Sleep(2000);
}

