#include "2048_helper.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <climits>

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
	     << "  s  save the game to savegame.txt (replaces the last save)" << endl
	     << "  o  open (load) the game from savegame.txt" << endl
	     << "  n  new game (asks first)" << endl
	     << "  h  show this help" << endl
	     << "  e  exit" << endl
	     << "Tiles slide as far as they can and equal tiles merge once per move." << endl
	     << "A new 2 appears only after a move that changes the board." << endl
	     << "Reach 2048 to win (you can keep playing). The game is over when" << endl
	     << "the board is full and no two neighbors match." << endl;
}

// ---------- save and load ----------

bool save_game(const string &filename, const int board[][SIZE], int score, int moves, string &error)
{
	ofstream out(filename);
	if (!out)
	{
		error = "Could not open " + filename + " for writing.";
		return false;
	}

	out << SAVE_MARKER << "\n";
	out << score << " " << moves << "\n";
	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			out << board[r][c];
			if (c < SIZE - 1)
				out << " ";
		}
		out << "\n";
	}

	out.close();
	if (out.fail())
	{
		error = "Something went wrong while writing " + filename + ".";
		return false;
	}
	return true;
}

// Turns a token into an int. Fails on anything that is not a whole
// number or is outside the range of int.
bool parse_int(const string &token, int &value)
{
	if (token.empty())
		return false;

	size_t start = 0;
	if (token[0] == '-' || token[0] == '+')
		start = 1;
	if (start == token.size())
		return false;

	long long total = 0;
	for (size_t i = start; i < token.size(); i++)
	{
		if (token[i] < '0' || token[i] > '9')
			return false;
		total = total * 10 + (token[i] - '0');
		if (total > (long long)INT_MAX + 1)
			return false;
	}

	if (token[0] == '-')
		total = -total;
	if (total < INT_MIN || total > INT_MAX)
		return false;

	value = (int)total;
	return true;
}

bool is_valid_tile(int value)
{
	if (value == 0)
		return true;
	if (value < 2)
		return false;
	// power of two: only one bit set
	return (value & (value - 1)) == 0;
}

// Reads everything into temporary variables first. The real board,
// score, and moves are only replaced if the whole file is valid.
bool load_game(const string &filename, int board[][SIZE], int &score, int &moves, string &error)
{
	ifstream in(filename);
	if (!in)
	{
		error = "Could not open " + filename + ". Has a game been saved yet?";
		return false;
	}

	string token;
	if (!(in >> token) || token != SAVE_MARKER)
	{
		error = "Not a valid save file (missing " + SAVE_MARKER + " on the first line).";
		return false;
	}

	int tempScore, tempMoves;
	if (!(in >> token) || !parse_int(token, tempScore) || tempScore < 0)
	{
		error = "Score is missing, not a whole number, or negative.";
		return false;
	}
	if (!(in >> token) || !parse_int(token, tempMoves) || tempMoves < 0)
	{
		error = "Move count is missing, not a whole number, or negative.";
		return false;
	}

	int temp[SIZE][SIZE];
	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			if (!(in >> token))
			{
				error = "Save file is incomplete (fewer than 25 tiles).";
				return false;
			}
			int value;
			if (!parse_int(token, value))
			{
				error = "Tile \"" + token + "\" is not a whole number in range.";
				return false;
			}
			if (!is_valid_tile(value))
			{
				error = "Tile " + token + " is not 0 or a power of two (2, 4, 8, ...).";
				return false;
			}
			temp[r][c] = value;
		}
	}

	if (in >> token)
	{
		error = "Save file has extra data after the 25 tiles.";
		return false;
	}

	// Everything checked out, so now copy into the real game
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			board[r][c] = temp[r][c];
	score = tempScore;
	moves = tempMoves;
	return true;
}
