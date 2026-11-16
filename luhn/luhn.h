#ifndef LUHN_H
#define LUHN_H

#include <string>

const int CARD_LENGTH = 16;

// True only if the text is exactly 16 characters and every one is a digit 0-9.
bool isValidFormat(const std::string &text);

// Turns one digit's position into its Luhn value.
// doubleIt = true means double the digit and subtract 9 if it goes over 9.
int luhnDigitValue(char digit, bool doubleIt);

// Adds up the Luhn values, starting from the rightmost digit.
// Takes a const reference so the original input is never changed.
int luhnSum(const std::string &digits);

// True when the Luhn sum is divisible by 10.
bool checkLuhn(const std::string &digits);

#endif
