# Luhn Checker

This is the second program. It's separate from 2048 and has its own main.

## What it does
You type in a 16 digit number and it tells you if it passes the Luhn checksum. It keeps asking until you type q to quit.

## How it works
- The number is read as a string so leading zeros don't get lost.
- `isValidFormat` checks that it's exactly 16 characters and all digits. If not, it tells you the format is wrong and lets you try again.
- `luhnSum` starts at the last digit and doubles every second digit going left. If a doubled number is over 9, it subtracts 9. Then it adds everything up.
- `checkLuhn` says it passes if the sum is divisible by 10.

## Build and run (from the top project folder)
```
g++ -std=c++17 -Wall -Wextra -pedantic luhn/main.cpp luhn/luhn.cpp -o luhn_app
./luhn_app
```
