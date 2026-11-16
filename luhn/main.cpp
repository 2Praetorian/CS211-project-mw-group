#include <iostream>
#include <string>
#include "luhn.h"
using namespace std;

// Removes spaces/tabs/carriage returns from the start and end only.
// Spaces inside the number are kept so the format check can reject them.
string trimEnds(const string &line)
{
	size_t start = line.find_first_not_of(" \t\r");
	if (start == string::npos)
		return "";
	size_t end = line.find_last_not_of(" \t\r");
	return line.substr(start, end - start + 1);
}

int main()
{
	cout << "Luhn checksum checker" << endl;
	cout << "Enter a 16-digit number to check, or q to quit." << endl;
	cout << "(Passing only means the digits are consistent. It does not mean a card is real or usable.)" << endl;

	string line;
	while (true)
	{
		cout << endl << "Number (or q to quit): ";
		if (!getline(cin, line))
		{
			cout << endl << "End of input. Goodbye!" << endl;
			break;
		}

		string input = trimEnds(line);

		if (input == "q" || input == "Q")
		{
			cout << "Goodbye!" << endl;
			break;
		}

		if (!isValidFormat(input))
		{
			cout << "Invalid format: enter exactly 16 digits (0-9) with no spaces, letters, or symbols." << endl;
			continue;
		}

		int sum = luhnSum(input);
		if (checkLuhn(input))
			cout << input << " PASSES the Luhn checksum (sum = " << sum << ", divisible by 10)." << endl;
		else
			cout << input << " FAILS the Luhn checksum (sum = " << sum << ", not divisible by 10)." << endl;
	}

	return 0;
}
