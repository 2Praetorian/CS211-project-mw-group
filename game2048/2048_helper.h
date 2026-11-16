#ifndef GAME_2048_HELPER_H
#define GAME_2048_HELPER_H

#include <string>

const int SIZE = 5;
const std::string SAVE_FILE = "savegame.txt";
const std::string SAVE_MARKER = "CS211_2048_V1";

// Board setup
void clear_board(int board[][SIZE]);
void new_game(int board[][SIZE], int &score, int &moves);
bool insert_random(int board[][SIZE]);

// Movement: each returns true if the board changed.
// points gets the score earned by the move (sum of the new merged tiles).
// No random tile is added here, so moves can be tested on their own.
bool move_left(int board[][SIZE], int &points);
bool move_right(int board[][SIZE], int &points);
bool move_up(int board[][SIZE], int &points);
bool move_down(int board[][SIZE], int &points);

// Board checks
int highest_tile(const int board[][SIZE]);
bool has_empty_cell(const int board[][SIZE]);
bool can_move(const int board[][SIZE]);

// Display
void print_board(const int board[][SIZE]);
void print_status(const int board[][SIZE], int score, int moves);
void print_help();

// Save and load (one slot: savegame.txt)
bool save_game(const std::string &filename, const int board[][SIZE], int score, int moves, std::string &error);
bool load_game(const std::string &filename, int board[][SIZE], int &score, int &moves, std::string &error);

#endif
