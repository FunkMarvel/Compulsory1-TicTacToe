// Compulsory 1, Anders P. Åsbø.
#include <iostream>
#include <string>
#include <vector>

void displayTable(std::vector<char>&, int);
void selection(std::vector<char>&, int);
bool checkWin(std::vector<char>&, int);

int main() {
	const int row_col_length = 3;
	std::vector<char> table = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	selection(table, row_col_length);
	return 0;
}

void displayTable(std::vector<char> &table, int rcl) {
	std::cout << std::endl;
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
	std::cout << std::endl << std::endl;
}

void selection(std::vector<char> &table, int rcl) {
	int selection{};
	int turn_number{0};
	int player{};
	char mark{};

	while (turn_number < 9) {
		system("cls");
		displayTable(table, rcl);
	
		while (true) {
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

			std::cout << "Player " << player << " select a number from the board: ";
			std::cin >> selection;
			if (selection > 0 && selection < 10 && table[selection - 1] != 'x' && table[selection - 1] != 'o')
			{
				table[selection - 1] = mark;
				break;
			}
			else
			{
				std::cout << "Invalid selection, try again." << std::endl;
			}
		}
		if (checkWin(table, rcl))
		{
			system("cls");
			displayTable(table, rcl);
			std::cout << "Player " << player << " has won!" << std::endl;
			return;
		}
		turn_number++;
	}
	system("cls");
	displayTable(table, rcl);

	std::cout << "It's a draw!" << std::endl;
}

bool checkWin(std::vector<char> &table, int rcl)
{
	bool win{ false };
	for (int i = 0; i < rcl; i++)
	{
		win = (table[i * rcl] == table[i * rcl + 1] && table[i * rcl] == table[i * rcl + 2]);
		if (win) return win;

		win = (table[i] == table[i + rcl] && table[i] == table[i + 2 * rcl]);
		if (win) return win;
	}
	win = (table[0] == table[rcl + 1] && table[0] == table[2 * rcl + 2]);
	if (win) return win;

	win = (table[2] == table[rcl + 1] && table[2] == table[2 * rcl]);
	if (win) return win;

	return false;
}
