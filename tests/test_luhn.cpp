// Automated checks for the Luhn functions (handout Part B tests).
// Build from the top project folder:
//   g++ -std=c++17 -Wall -Wextra -pedantic tests/test_luhn.cpp luhn/luhn.cpp -o test_luhn
#include <iostream>
#include <string>
#include "../luhn/luhn.h"
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

int main()
{
	check("4532015112830366: format ok, sum 50, passes",
	      isValidFormat("4532015112830366") && luhnSum("4532015112830366") == 50 && checkLuhn("4532015112830366"));
	check("4532015112830367: format ok, sum 51, fails",
	      isValidFormat("4532015112830367") && luhnSum("4532015112830367") == 51 && !checkLuhn("4532015112830367"));
	check("0000000000000018: format ok, leading zeros kept, passes",
	      isValidFormat("0000000000000018") && checkLuhn("0000000000000018"));
	check("453201511283036 (15 digits): rejected", !isValidFormat("453201511283036"));
	check("45320151128303666 (17 digits): rejected", !isValidFormat("45320151128303666"));
	check("453201511283036X (non-digit): rejected", !isValidFormat("453201511283036X"));
	check("4532 015112830366 (internal space): rejected", !isValidFormat("4532 015112830366"));
	check("4532-0151-1283-0366 (punctuation): rejected", !isValidFormat("4532-0151-1283-0366"));
	check("empty input: rejected", !isValidFormat(""));

	string original = "4532015112830366";
	string copy = original;
	checkLuhn(copy);
	check("input is not modified by checkLuhn", copy == original);

	cout << endl << passed << " passed, " << failed << " failed." << endl;
	return failed;
}
