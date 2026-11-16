#include <iostream>
#include <string>
#include "2048_helper.h"
using namespace std;

// Reads one line and returns its first non-space character.
// Returns false at end of input. Sets valid to false if the line
// has more than one character (like "lr" or "left").
bool read_command(char &cmd, bool &valid)
{
	string line;
	if (!getline(cin, line))
		return false;

	string trimmed;
	for (char ch : line)
		if (ch != ' ' && ch != '\t' && ch != '\r')
			trimmed += ch;

	valid = (trimmed.size() == 1);
	cmd = valid ? trimmed[0] : ' ';
	return true;
}

int main()
{
	int board[SIZE][SIZE];
	int score = 0;
	int moves = 0;
	bool wonAnnounced = false;

	new_game(board, score, moves);

	cout << "2048 (5x5). Type h for help." << endl;
	print_status(board, score, moves);

	while (true)
	{
		bool gameOver = !can_move(board);
		if (gameOver)
			cout << "GAME OVER - no moves left. You can still use s, o, n, h, or e." << endl;

		cout << "Command (u/d/l/r, s=save, o=open, n=new, h=help, e=exit): ";
		char cmd;
		bool valid;
		if (!read_command(cmd, valid))
		{
			cout << endl << "End of input. Goodbye!" << endl;
			break;
		}
		if (!valid)
		{
			cout << "Invalid command. Type one letter, or h for help." << endl;
			continue;
		}

		if (cmd == 'u' || cmd == 'd' || cmd == 'l' || cmd == 'r')
		{
			if (gameOver)
			{
				cout << "No moves are possible. Try n, o, s, h, or e." << endl;
				continue;
			}

			int points = 0;
			bool changed = false;
			if (cmd == 'u')
				changed = move_up(board, points);
			else if (cmd == 'd')
				changed = move_down(board, points);
			else if (cmd == 'l')
				changed = move_left(board, points);
			else
				changed = move_right(board, points);

			if (!changed)
			{
				cout << "Nothing moved in that direction. Try another one." << endl;
				continue;
			}

			score += points;
			moves++;
			insert_random(board);
			print_status(board, score, moves);

			if (!wonAnnounced && highest_tile(board) >= 2048)
			{
				cout << "*** You reached 2048! You win! Keep playing if you want. ***" << endl;
				wonAnnounced = true;
			}
		}
		else if (cmd == 's' || cmd == 'o')
		{
			cout << "Save and load are not added yet. Your game was not changed." << endl;
		}
		else if (cmd == 'n')
		{
			cout << "Start a new game? Your current game will be lost unless you saved it. (y/n): ";
			char answer;
			bool answerValid;
			if (!read_command(answer, answerValid))
			{
				cout << endl << "End of input. Goodbye!" << endl;
				break;
			}
			if (answerValid && (answer == 'y' || answer == 'Y'))
			{
				new_game(board, score, moves);
				wonAnnounced = false;
				cout << "New game started." << endl;
				print_status(board, score, moves);
			}
			else
			{
				cout << "New game cancelled." << endl;
			}
		}
		else if (cmd == 'h')
		{
			print_help();
		}
		else if (cmd == 'e')
		{
			cout << "Goodbye!" << endl;
			break;
		}
		else
		{
			cout << "Invalid command '" << cmd << "'. Type h for help." << endl;
		}
	}

	return 0;
}
