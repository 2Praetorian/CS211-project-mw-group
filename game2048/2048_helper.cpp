#include "2048_helper.h"

#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

// ---------- board setup ----------

void clear_board(int board[][SIZE])
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			board[r][c] = 0;
}

// Picks one empty cell at random and puts a 2 there.
// Returns false if the board has no empty cell.
bool insert_random(int board[][SIZE])
{
	static mt19937 rng(random_device{}());

	int emptyRows[SIZE * SIZE];
	int emptyCols[SIZE * SIZE];
	int count = 0;

	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			if (board[r][c] == 0)
			{
				emptyRows[count] = r;
				emptyCols[count] = c;
				count++;
			}
		}
	}

	if (count == 0)
		return false;

	uniform_int_distribution<int> pick(0, count - 1);
	int i = pick(rng);
	board[emptyRows[i]][emptyCols[i]] = 2;
	return true;
}

void new_game(int board[][SIZE], int &score, int &moves)
{
	clear_board(board);
	score = 0;
	moves = 0;
	insert_random(board);   // two 2s in different empty cells
	insert_random(board);
}

// ---------- movement ----------

// Slides one line of 5 values toward index 0 and merges equal pairs once.
// Returns the points earned. The caller decides which direction the line runs.
int slide_line(int line[SIZE])
{
	// Step 1: copy the nonzero tiles in order (closes the gaps)
	int tiles[SIZE];
	int count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (line[i] != 0)
		{
			tiles[count] = line[i];
			count++;
		}
	}

	// Step 2: build the new line, merging each equal pair only once
	int result[SIZE] = {0, 0, 0, 0, 0};
	int pos = 0;
	int points = 0;
	int i = 0;
	while (i < count)
	{
		if (i + 1 < count && tiles[i] == tiles[i + 1])
		{
			result[pos] = tiles[i] * 2;
			points += result[pos];
			i += 2;   // both tiles are used up, so neither can merge again
		}
		else
		{
			result[pos] = tiles[i];
			i++;
		}
		pos++;
	}

	// Step 3: copy back
	for (int k = 0; k < SIZE; k++)
		line[k] = result[k];

	return points;
}

// Left: each row read left to right
bool move_left(int board[][SIZE], int &points)
{
	bool changed = false;
	points = 0;
	for (int r = 0; r < SIZE; r++)
	{
		int line[SIZE];
		for (int c = 0; c < SIZE; c++)
			line[c] = board[r][c];

		points += slide_line(line);

		for (int c = 0; c < SIZE; c++)
		{
			if (board[r][c] != line[c])
				changed = true;
			board[r][c] = line[c];
		}
	}
	return changed;
}

// Right: each row read right to left
bool move_right(int board[][SIZE], int &points)
{
	bool changed = false;
	points = 0;
	for (int r = 0; r < SIZE; r++)
	{
		int line[SIZE];
		for (int k = 0; k < SIZE; k++)
			line[k] = board[r][SIZE - 1 - k];

		points += slide_line(line);

		for (int k = 0; k < SIZE; k++)
		{
			int c = SIZE - 1 - k;
			if (board[r][c] != line[k])
				changed = true;
			board[r][c] = line[k];
		}
	}
	return changed;
}

// Up: each column read top to bottom
bool move_up(int board[][SIZE], int &points)
{
	bool changed = false;
	points = 0;
	for (int c = 0; c < SIZE; c++)
	{
		int line[SIZE];
		for (int r = 0; r < SIZE; r++)
			line[r] = board[r][c];

		points += slide_line(line);

		for (int r = 0; r < SIZE; r++)
		{
			if (board[r][c] != line[r])
				changed = true;
			board[r][c] = line[r];
		}
	}
	return changed;
}

// Down: each column read bottom to top
bool move_down(int board[][SIZE], int &points)
{
	bool changed = false;
	points = 0;
	for (int c = 0; c < SIZE; c++)
	{
		int line[SIZE];
		for (int k = 0; k < SIZE; k++)
			line[k] = board[SIZE - 1 - k][c];

		points += slide_line(line);

		for (int k = 0; k < SIZE; k++)
		{
			int r = SIZE - 1 - k;
			if (board[r][c] != line[k])
				changed = true;
			board[r][c] = line[k];
		}
	}
	return changed;
}

// ---------- board checks ----------

int highest_tile(const int board[][SIZE])
{
	int best = 0;
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			if (board[r][c] > best)
				best = board[r][c];
	return best;
}

bool has_empty_cell(const int board[][SIZE])
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			if (board[r][c] == 0)
				return true;
	return false;
}

// A move is possible if there is an empty cell or two equal neighbors
// side by side or one above the other.
bool can_move(const int board[][SIZE])
{
	if (has_empty_cell(board))
		return true;

	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			if (c + 1 < SIZE && board[r][c] == board[r][c + 1])
				return true;
			if (r + 1 < SIZE && board[r][c] == board[r + 1][c])
				return true;
		}
	}
	return false;
}

// ---------- display ----------

void print_board(const int board[][SIZE])
{
	cout << endl << "\t-----------------------------------------" << endl;
	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			if (board[r][c] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[r][c];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}
	cout << endl;
}

void print_status(const int board[][SIZE], int score, int moves)
{
	print_board(board);
	cout << "Score: " << score
	     << "   Moves: " << moves
	     << "   Highest tile: " << highest_tile(board) << endl;
}

void print_help()
{
	cout << endl
	     << "Commands:" << endl
	     << "  u  move up" << endl
	     << "  d  move down" << endl
	     << "  l  move left" << endl
	     << "  r  move right" << endl
	     << "  s  save (coming in the next update)" << endl
	     << "  o  open/load (coming in the next update)" << endl
	     << "  n  new game (asks first)" << endl
	     << "  h  show this help" << endl
	     << "  e  exit" << endl
	     << "Tiles slide as far as they can and equal tiles merge once per move." << endl
	     << "A new 2 appears only after a move that changes the board." << endl
	     << "Reach 2048 to win (you can keep playing). The game is over when" << endl
	     << "the board is full and no two neighbors match." << endl;
}
