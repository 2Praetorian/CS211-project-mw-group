// Runs the left-move examples from Part A of the handout.
// Build from the top project folder:
//   g++ -std=c++17 -Wall -Wextra -pedantic tests/test_move_left.cpp -o test_move_left
#include <iostream>
#include "../game2048/2048_helper.h"
using namespace std;

void print_row(int row[5])
{
	for (int c = 0; c < 5; c++)
		cout << row[c] << " ";
}

int main()
{
	const int NUM_TESTS = 7;
	int start[NUM_TESTS][5] = {
		{0, 2, 0, 2, 0},
		{2, 2, 2, 0, 0},
		{2, 2, 2, 2, 2},
		{2, 2, 4, 0, 0},
		{4, 4, 8, 8, 0},
		{2, 4, 8, 0, 0},
		{0, 0, 0, 0, 2}
	};
	int expected[NUM_TESTS][5] = {
		{4, 0, 0, 0, 0},
		{4, 2, 0, 0, 0},
		{4, 4, 2, 0, 0},
		{4, 4, 0, 0, 0},
		{8, 16, 0, 0, 0},
		{2, 4, 8, 0, 0},
		{2, 0, 0, 0, 0}
	};
	int expectedPoints[NUM_TESTS] = {4, 4, 8, 4, 24, 0, 0};
	bool expectedChanged[NUM_TESTS] = {true, true, true, true, true, false, true};

	int failed = 0;
	for (int t = 0; t < NUM_TESTS; t++)
	{
		// put the test row in the top row of an empty board
		int board[5][5] = {};
		for (int c = 0; c < 5; c++)
			board[0][c] = start[t][c];

		int points = 0;
		bool changed = move_left(board, points);

		bool pass = (points == expectedPoints[t]) && (changed == expectedChanged[t]);
		for (int c = 0; c < 5; c++)
		{
			if (board[0][c] != expected[t][c])
				pass = false;
		}

		print_row(start[t]);
		cout << "-> ";
		print_row(board[0]);
		cout << " score +" << points << (changed ? " (changed)" : " (no change)");
		cout << (pass ? "  PASS" : "  FAIL") << endl;

		if (!pass)
			failed++;
	}

	cout << endl << (NUM_TESTS - failed) << " of " << NUM_TESTS << " tests passed." << endl;
	return failed;
}
