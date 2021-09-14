// Compulsory 1, Anders P. Åsbø.
#include <iostream>
#include <string>
#include <vector>
#include <random>

void displayTable(std::vector<char>&, int);
void gamePlayLoop(std::vector<char>&, int);
bool checkWin(std::vector<char>&, int);
int aiSelection(std::vector<char>&, int, double);

int main() {
	// TicTacToe console-app.
	const int row_col_length = 3;  // length of each row and column in game board.
	char want_to_play{'y'};  // stores the answer to "play again?".

	while (tolower(want_to_play == 'y'))
	{
		// stores number of and state of each square on game board:
		std::vector<char> table = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

		gamePlayLoop(table, row_col_length);  // runs gameplay loop.
		
		system("pause"); // waits for keypress before closing window.
		system("cls");

		std::cout << " Do you wan't to play again? (y/n): ";
		std::cin >> want_to_play;
	}

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
	char ai_on{};
	char difficulty{'1'};
	double weight{};

	std::cout << " Play against Ai? y/n: ";
	std::cin >> ai_on;
	ai_on = tolower(ai_on);
	
	if (ai_on == 'y') {
		std::cout << std::endl;
		std::cout << " 1. Easy\n 2. Medium\n 3. Hard" << std::endl;
		std::cout << " Select difficulty: ";
		std::cin >> difficulty;

		switch (tolower(difficulty))
		{
		case '1': case 'e': default:
			weight = 0.9;
			break;
		case '2': case 'm':
			weight = 0.5;
			break;
		case '3': case 'h':
			weight = 0.1;
			break;
		}
	}

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

			// checks if ai is on:
			if (player == 1 || ai_on == 'n')
			{
				std::cout << "Player " << player << " (" << mark << ") select a number from the board: ";
				std::cin >> selection;
			}
			else
			{
				selection = aiSelection(table, rcl, weight);  // performs ai selection if ai is enabled.
			}

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

int aiSelection(std::vector<char>& table, int rcl, double weight)
{
	// Function making ai selection. Returns integer corresponding to selected square.
	// Args:
	//	&table - vector of chars passed by refrence,
	//			 containing the squares of the board.
	//	rcl - integer representing the dimension n of the n*n game board.
	//	weight - double between 0 and 1 corresponding to selected difficulty.

	int selection{};  // return variable.

	// creates copy of current game board state:
	std::vector<char> test_table(table.size());
	std::copy(table.begin(), table.end(), test_table.begin());
	
	// variables for storing indices that can be selected:
	std::vector<int> possible_selections{};
	int possible_win{ -1 };  // stores index of winning move.
	int possible_loss{ -1 };  // stores index of losing move.
	bool middle_free{ false };  // stores state of middle square.


	// looping through table:
	for (int i = 0; i < rcl * rcl; i++)
	{
		// finds empty squares:
		if (test_table[i] != 'x' && test_table[i] != 'o') {

			// checks if current square can lead to win if selected:
			test_table[i] = 'o';
			if (checkWin(test_table, rcl)) possible_win = i;  // stores index of winning selection.

			// checks if current square can lead to loss if not selected:
			test_table[i] = 'x';
			if (checkWin(test_table, rcl)) possible_loss = i;  // stores index of possible loss.

			if (i == 4) { middle_free = true; } // checks if middle is free.
			else { possible_selections.push_back(i); }  // stores index of square if free and not middle.
			test_table[i] = table[i];  // resets value of current square to match the current state of the game.
		}
	}

	// creates random number genenrator for ai behaviour:
	std::random_device rd{};
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<double> real_dist(0, 1);  // real distrobution for comparing with weight.
	std::uniform_int_distribution<int> int_dist(0, possible_selections.size() - 1);  // int distrobution for random selection.
	
	double percent = real_dist(gen); // Draws a random real number between 0 and 1 to compare with difficulty weight.
	// A lower weight makes the ai more likely to play correct moves, and thus increases the difficulty.
	
	if (percent > weight && possible_win >= 0) {
		// possible win is selected if random number is bigger than the difficulty weight:
		selection = possible_win;
	}
	else if (percent > weight && possible_loss >= 0) {
		// possible loss is prevented if random number is bigger than the difficulty weight:
		selection = possible_loss;
	}
	else if (middle_free) {
		// middle is selected if it is free:
		selection = 4;
	}
	else {
		// if no other selection has been made, then a random free square is chosen:
		selection = possible_selections[int_dist(gen)];
	}

	return selection + 1;  // returns number of selected square.
}
