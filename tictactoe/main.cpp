// Compulsory 1, Anders P. Åsbø.
#include <iostream>
#include <string>
#include <vector>

void displayTable(std::vector<char>&, int);
void gamePlayLoop(std::vector<char>&, int);
bool checkWin(std::vector<char>&, int);

int main() {
	// TicTacToe console-app.
	const int row_col_length = 3;  // length of each row and column in game board.

	// stores number of and state of each square on game board:
	std::vector<char> table = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

	gamePlayLoop(table, row_col_length);  // runs gameplay loop.
	system("pause"); // waits for keypress before closing window.

	return 0;
}

void displayTable(std::vector<char> &table, int rcl) {
	// Function displaying game board to terminal.
	// Args:
	//	&table - vector of chars passed by refrence,
	//			 containing the squares of the board.
	//	rcl - integer representing the dimension n of the n*n game board.

	std::cout << std::endl;  // padding.

	// loops through table vector and prints the game board as 3 by 3 table:
	for (int i = 0; i < rcl; i++)
	{
		for (int j = 0; j < rcl; j++)
		{
			std::cout << " " << table[rcl*i + j] << " ";
			if (j != rcl-1)
			{
				std::cout << "|";
			}
		}
		if (i != rcl-1)
		{
			std::cout << "\n-----------" << std::endl;
		}
	}
	std::cout << std::endl << std::endl; // padding.
}

void gamePlayLoop(std::vector<char> &table, int rcl) {
	// Function running the gameplay loop.
	// Args:
	//	&table - vector of chars passed by refrence,
	//			 containing the squares of the board.
	//	rcl - integer representing the dimension n of the n*n game board.

	int selection{};  // stores the number corresponding to selected square.
	int turn_number{};  // stores the number of turns that have passed.
	int player{};  // stores the player number.
	char mark{};  // stores the mark to use when updating the board ('x' or 'o').

	// the primary gameplay loop:
	while (turn_number < 9) {  // loop stops when maximum number of turns have been met.
		// displaying game board:
		system("cls");
		displayTable(table, rcl);
	
		// loop asking for player input and setting corresponding mark in selected box:
		while (true) {
			// alternates player number and mark to use:
			if (turn_number % 2 == 0)
			{
				player = 1;
				mark = 'x';
			}
			else
			{
				player = 2;
				mark = 'o';
			}

			// asks for input:
			std::cout << "Player " << player << " select a number from the board: ";
			std::cin >> selection;

			// marks selected square if it's not already marked:
			if (selection > 0 && selection < 10 && table[selection - 1] != 'x' && table[selection - 1] != 'o')
			{
				table[selection - 1] = mark;
				break;
			}
			else  // asks for new selection if square is already marked:
			{
				std::cout << "Invalid selection, try again." << std::endl;
			}
		}

		// checks if win condition has been met, and prints win-message if true: 
		if (checkWin(table, rcl))
		{
			system("cls");
			displayTable(table, rcl);
			std::cout << "Player " << player << " has won!" << std::endl;
			return;  // jumps out of function if a player has won.
		}
		turn_number++;  // counts up by one turn.
	}
	// displays the final table if its a draw:
	system("cls");
	displayTable(table, rcl);

	std::cout << "It's a draw!" << std::endl;
}

bool checkWin(std::vector<char> &table, int rcl)
{
	// Function that checks entire board and returns a bool of value true
	// if a win has been reached and value false if no win has been reached.
	// Args:
	//	&table - vector of chars passed by refrence,
	//			 containing the squares of the board.
	//	rcl - integer representing the dimension n of the n*n game board.

	bool win{ false };  // return value.

	// looping through table:
	for (int i = 0; i < rcl; i++)
	{
		// checking row number i for win and returns true if true:
		win = (table[i * rcl] == table[i * rcl + 1] && table[i * rcl] == table[i * rcl + 2]);
		if (win) return win;

		// checking column number i for win and returns true if true:
		win = (table[i] == table[i + rcl] && table[i] == table[i + 2 * rcl]);
		if (win) return win;
	}

	// checks upper-left to lower-right diagonal for win and returns true if true:
	win = (table[0] == table[rcl + 1] && table[0] == table[2 * rcl + 2]);
	if (win) return win;

	// checks lower-left to upper-right diagonal for win and returns true if true:
	win = (table[2] == table[rcl + 1] && table[2] == table[2 * rcl]);
	if (win) return win;

	return false;  // returns false if end of function is reached. 
}
