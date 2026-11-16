#include "luhn.h"

using namespace std;

bool isValidFormat(const string &text)
{
	if (text.length() != CARD_LENGTH)
		return false;

	for (char ch : text)
	{
		if (ch < '0' || ch > '9')
			return false;
	}
	return true;
}

int luhnDigitValue(char digit, bool doubleIt)
{
	int value = digit - '0';
	if (doubleIt)
	{
		value = value * 2;
		if (value > 9)
			value = value - 9;   // same as adding the two digits (e.g. 16 -> 1 + 6 = 7)
	}
	return value;
}

int luhnSum(const string &digits)
{
	int sum = 0;
	bool doubleIt = false;   // the rightmost digit is not doubled

	for (int i = (int)digits.length() - 1; i >= 0; i--)
	{
		sum += luhnDigitValue(digits[i], doubleIt);
		doubleIt = !doubleIt;   // every second digit going left gets doubled
	}
	return sum;
}

bool checkLuhn(const string &digits)
{
	return luhnSum(digits) % 10 == 0;
}
