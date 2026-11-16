#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

// Slides and merges every row to the left.
// Returns true if anything on the board moved or merged.
// points gets the score earned by this move (sum of the new merged tiles).
bool move_left(int board[][5], int &points)
{
	bool changed = false;
	points = 0;

	for (int row = 0; row < 5; row++)
	{
		// Step 1: copy the nonzero tiles in order (this closes the gaps)
		int tiles[5];
		int count = 0;
		for (int col = 0; col < 5; col++)
		{
			if (board[row][col] != 0)
			{
				tiles[count] = board[row][col];
				count++;
			}
		}

		// Step 2: build the new row, merging each equal pair once
		int newRow[5] = {0, 0, 0, 0, 0};
		int pos = 0;
		int i = 0;
		while (i < count)
		{
			if (i + 1 < count && tiles[i] == tiles[i + 1])
			{
				newRow[pos] = tiles[i] * 2;
				points += newRow[pos];
				i += 2;   // both tiles are used up, so neither can merge again
			}
			else
			{
				newRow[pos] = tiles[i];
				i++;
			}
			pos++;
		}

		// Step 3: copy back and check if anything changed
		for (int col = 0; col < 5; col++)
		{
			if (board[row][col] != newRow[col])
				changed = true;
			board[row][col] = newRow[col];
		}
	}

	return changed;
}

void move_right(int board[][5], int numrows = 5)
{
	//CODE HERE
}

void move_up(int board[][5], int numrows = 5)
{
	//CODE HERE
}

void move_down(int board[][5], int numrows = 5)
{
	//CODE HERE
}


void print_board(int board[][5], int numrows = 5)
{
	cout << endl << "\t-----------------------------------------" << endl;

	for (int r = 0; r < numrows; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if(board[r][c] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[r][c];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";

			//cout << board[r][c] << "\t|\t";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}

	cout << "\t" << endl << endl;
}


void insert_random(int board[][5], int numrows = 5)
{
	int r, c;
	//count empty
	int empty_count = 0;
	for (int r = 0; r < numrows; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if (board[r][c] == 0)
				empty_count++;
		}
	}

	if (empty_count > 0)
	{
		while (true)
		{
			//generate random location r, c
			r = rand() % numrows;
			c = rand() % numrows;
			//check if empty
			if (board[r][c] == 0)
			{
				//add number randomly {2,4}
				board[r][c] = 2 * (1 + (rand() % 2));
				break;
			}
		}

	}
}

