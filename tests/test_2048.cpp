// Automated checks for the 2048 helper functions (handout Part A movement tests).
// Build from the top project folder:
//   g++ -std=c++17 -Wall -Wextra -pedantic tests/test_2048.cpp game2048/2048_helper.cpp -o test_2048
#include <iostream>
#include <string>
#include "../game2048/2048_helper.h"
using namespace std;

int passed = 0;
int failed = 0;

void check(const string &name, bool ok)
{
	cout << (ok ? "PASS  " : "FAIL  ") << name << endl;
	if (ok)
		passed++;
	else
		failed++;
}

bool same_board(const int a[][SIZE], const int b[][SIZE])
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			if (a[r][c] != b[r][c])
				return false;
	return true;
}

void copy_board(const int from[][SIZE], int to[][SIZE])
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			to[r][c] = from[r][c];
}

int count_tiles(const int b[][SIZE])
{
	int n = 0;
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			if (b[r][c] != 0)
				n++;
	return n;
}

// Puts one row in row 0 of an empty board, moves left, compares row 0.
void left_row_test(int start[SIZE], int expected[SIZE], int expectedPoints, bool expectedChanged)
{
	int b[SIZE][SIZE] = {};
	for (int c = 0; c < SIZE; c++)
		b[0][c] = start[c];
	int points = 0;
	bool changed = move_left(b, points);
	bool ok = (points == expectedPoints) && (changed == expectedChanged);
	for (int c = 0; c < SIZE; c++)
		if (b[0][c] != expected[c])
			ok = false;

	string name = "left ";
	for (int c = 0; c < SIZE; c++)
		name += to_string(start[c]) + " ";
	name += "-> ";
	for (int c = 0; c < SIZE; c++)
		name += to_string(b[0][c]) + " ";
	name += "(+" + to_string(points) + ")";
	check(name, ok);
}

int main()
{
	// ---- 1 & 2: handout row examples (left), merge-once ----
	int s1[] = {0, 2, 0, 2, 0}, e1[] = {4, 0, 0, 0, 0};
	int s2[] = {2, 2, 2, 0, 0}, e2[] = {4, 2, 0, 0, 0};
	int s3[] = {2, 2, 2, 2, 2}, e3[] = {4, 4, 2, 0, 0};
	int s4[] = {2, 2, 4, 0, 0}, e4[] = {4, 4, 0, 0, 0};
	int s5[] = {4, 4, 8, 8, 0}, e5[] = {8, 16, 0, 0, 0};
	int s6[] = {2, 4, 8, 0, 0}, e6[] = {2, 4, 8, 0, 0};
	int s7[] = {2, 2, 2, 2, 0}, e7[] = {4, 4, 0, 0, 0};
	left_row_test(s1, e1, 4, true);
	left_row_test(s2, e2, 4, true);
	left_row_test(s3, e3, 8, true);
	left_row_test(s4, e4, 4, true);
	left_row_test(s5, e5, 24, true);
	left_row_test(s6, e6, 0, false);
	left_row_test(s7, e7, 8, true);   // four equal tiles

	// ---- right: handout example 2 2 2 0 0 -> 0 0 0 2 4 ----
	{
		int b[SIZE][SIZE] = {{2, 2, 2, 0, 0}};
		int exp[SIZE][SIZE] = {{0, 0, 0, 2, 4}};
		int p = 0;
		bool ch = move_right(b, p);
		check("right 2 2 2 0 0 -> 0 0 0 2 4 (+4)", ch && p == 4 && same_board(b, exp));
	}
	{
		int b[SIZE][SIZE] = {{0, 2, 0, 2, 0}};
		int exp[SIZE][SIZE] = {{0, 0, 0, 0, 4}};
		int p = 0;
		bool ch = move_right(b, p);
		check("right through gaps 0 2 0 2 0 -> 0 0 0 0 4 (+4)", ch && p == 4 && same_board(b, exp));
	}

	// ---- up / down on a column (column 0 = 2,2,2,0,0 top to bottom) ----
	{
		int b[SIZE][SIZE] = {{2}, {2}, {2}, {0}, {0}};
		int exp[SIZE][SIZE] = {{4}, {2}, {0}, {0}, {0}};
		int p = 0;
		bool ch = move_up(b, p);
		check("up column 2 2 2 0 0 -> 4 2 0 0 0 (+4)", ch && p == 4 && same_board(b, exp));
	}
	{
		int b[SIZE][SIZE] = {{2}, {2}, {2}, {0}, {0}};
		int exp[SIZE][SIZE] = {{0}, {0}, {0}, {2}, {4}};
		int p = 0;
		bool ch = move_down(b, p);
		check("down column 2 2 2 0 0 -> 0 0 0 2 4 (+4)", ch && p == 4 && same_board(b, exp));
	}
	{
		int b[SIZE][SIZE] = {{0}, {4}, {0}, {4}, {8}};
		int exp[SIZE][SIZE] = {{0}, {0}, {0}, {8}, {8}};
		int p = 0;
		bool ch = move_down(b, p);
		check("down through gaps 0 4 0 4 8 -> 0 0 0 8 8 (+8, new 8 does not merge again)", ch && p == 8 && same_board(b, exp));
	}
	{
		int b[SIZE][SIZE] = {{2}, {2}, {2}, {2}, {0}};
		int exp[SIZE][SIZE] = {{4}, {4}, {0}, {0}, {0}};
		int p = 0;
		bool ch = move_up(b, p);
		check("up four equal 2 2 2 2 0 -> 4 4 0 0 0 (+8)", ch && p == 8 && same_board(b, exp));
	}

	// ---- 3: slide with no merge -> changed, no points ----
	{
		int b[SIZE][SIZE] = {{0, 0, 0, 0, 2}};
		int p = 0;
		bool ch = move_left(b, p);
		check("slide with no merge: changed, +0", ch && p == 0 && b[0][0] == 2);
	}

	// ---- 4: unchanged move ----
	{
		int b[SIZE][SIZE] = {{2, 4, 8, 16, 32}};
		int before[SIZE][SIZE];
		copy_board(b, before);
		int p = 0;
		bool ch = move_left(b, p);
		check("unchanged move: not changed, +0, board same", !ch && p == 0 && same_board(b, before));
	}

	// ---- 5: full boards ----
	{
		int b[SIZE][SIZE] = {
			{2, 4, 2, 4, 2},
			{4, 2, 4, 2, 4},
			{2, 4, 2, 4, 2},
			{4, 2, 4, 2, 4},
			{2, 4, 2, 4, 4}};   // last two match
		check("full board with a possible merge: can_move = true", can_move(b) && !has_empty_cell(b));
	}
	{
		int b[SIZE][SIZE] = {
			{2, 4, 2, 4, 2},
			{4, 2, 4, 2, 4},
			{2, 4, 2, 4, 2},
			{4, 2, 4, 2, 4},
			{2, 4, 2, 4, 2}};
		check("full board with no moves: can_move = false (game over)", !can_move(b));
		int before[SIZE][SIZE];
		copy_board(b, before);
		int p = 0;
		bool any = move_left(b, p) || move_right(b, p) || move_up(b, p) || move_down(b, p);
		check("full board with no moves: no direction changes it", !any && same_board(b, before));
	}

	// ---- 6: several merges in one move, score, reaching 2048 ----
	{
		int b[SIZE][SIZE] = {
			{4, 4, 8, 8, 0},
			{2, 2, 0, 0, 0},
			{1024, 1024, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}};
		int p = 0;
		bool ch = move_left(b, p);
		bool ok = ch && p == 8 + 16 + 4 + 2048 && b[2][0] == 2048 && highest_tile(b) == 2048;
		check("several merges in one move: +2076, 1024+1024 makes 2048", ok);
	}

	// ---- random insertion: exactly one 2 in an empty cell ----
	{
		int b[SIZE][SIZE] = {{2, 0, 0, 0, 0}};
		insert_random(b);
		int twos = 0;
		for (int r = 0; r < SIZE; r++)
			for (int c = 0; c < SIZE; c++)
				if (b[r][c] == 2)
					twos++;
		check("insert_random adds exactly one 2", count_tiles(b) == 2 && twos == 2);
	}
	{
		int b[SIZE][SIZE];
		int score = 99, moves = 99;
		new_game(b, score, moves);
		check("new_game: two 2s, score 0, moves 0", count_tiles(b) == 2 && highest_tile(b) == 2 && score == 0 && moves == 0);
	}

	cout << endl << passed << " passed, " << failed << " failed." << endl;
	return failed;
}
